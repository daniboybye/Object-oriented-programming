#include "tagWithTags.h"
#include "functions.hpp"
#include <cstring>
#include <cassert>
#include <iostream>

namespace fmi {
namespace oop {

TagWithTags::TagWithTags(const char * name)
: Tag(name)
, tags(nullptr)
, tagsCount(0)
, value(nullptr)
, valueCount(0)
, tagOrValue(nullptr)
{}

TagWithTags::TagWithTags(const char * name, unsigned size)
: Tag(name, size)
, tags(nullptr)
, tagsCount(0)
, value(nullptr)
, valueCount(0)
, tagOrValue(nullptr)
{}

TagWithTags::~TagWithTags() {
	for (unsigned i = 0; i < this->tagsCount; ++i) {
		delete this->tags[i];
	}
	delete[] this->tags;

	for (unsigned i = 0; i < this->valueCount; ++i) {
		delete this->value[i];
	}
	delete[] this->value;

	delete[] this->tagOrValue;
}

bool TagWithTags::Create(Tag * tag, const char * road)
{
	if (tag == nullptr || road == nullptr) return false;

	if (strcmp(this->GetName(), road)==0) {
		this->AddTag(tag);
		return true;
	}

	long len = readToSlash(road);
	bool flag = false;

	if (len < 1) {
		return flag;
	}

	else if (str1InBeg2(this->GetName(), road)) {
		for (unsigned i = 0; i < this->tagsCount; ++i) {
			flag += this->tags[i]->Create(tag,road + len + 1);
		}
	}

	return flag;
}

void TagWithTags::Print(std::ostream & os, unsigned tab) const {
	putTabs(os, tab);
	os << "<" << this->GetName() << ">\n";

	this->Within(os, tab+1);

	putTabs(os, tab);
	os << "</" << this->GetName() << ">";
}

unsigned TagWithTags::Find(const char * tagName) const {
	unsigned count = 0;

	if (tagName == nullptr) return count;
	
	for (unsigned i = 0; i < this->tagsCount; ++i) {
		if (strcmp(tagName, this->tags[i]->GetName()) == 0) {
			count++;
			this->tags[i]->Print(std::cout);
			std::cout << std::endl;
		}

		count += this->tags[i]->Find(tagName);
	}

	return count;
}

unsigned TagWithTags::Erase(const char * road) {
	unsigned count = 0;

	if (road == nullptr) return count;

	long len = readToSlash(road);

	if (len < 1) {
		return count;
	}
	
	else if(str1InBeg2(this->GetName(),road)){
		long lenToNextSlash = readToSlash(road + len + 1);

		// ако няма повече наклонени черти ще пробвам да изтрия елемент
		if (lenToNextSlash < 0) {
			for (unsigned i = 1; i < this->tagsCount + 1; ++i) {
				//мога да трия от 0-лева позиция
				if (strcmp(this->tags[i-1]->GetName(),road+len+1) == 0) {
					this->DeleteTag(i-1);
					--i;
					count++;
				}
			}
		}
		//ако има продължавам 
		else {
			for (unsigned i = 0; i < this->tagsCount; ++i) {
				count += this->tags[i]->Erase(road + len + 1);
			}
		}
	}

	return count;
}

void TagWithTags::Within(std::ostream & os, unsigned tab) const {
	for (unsigned long  i = 0, countTags = 0, countValue = 0;
		i < this->tagsCount + this->valueCount; ++i) {


		if (this->tagOrValue[i]) {
			assert(countTags < this->tagsCount);

			this->tags[countTags]->Print(os,tab);
			countTags++;
		}
		else {
			assert(countValue < this->valueCount);

			putTabs(os, tab);
			os << this->value[countValue];
			countValue++;
		}

		os << "\n";
	}
}

void TagWithTags::RoadToWithin(std::ostream & os, const char * road) const {
	if (road == nullptr) return;

	long len = readToSlash(road);

	if (len == 0) {
		return;
	}

	if (len == -1) {
		if (strcmp(road, this->GetName()) == 0) {
				this->Within(os);
		}
	}
	else {
		char * currNameTag = new char[len+1];
		mystrcpy(currNameTag, len , road);

		if (strcmp(currNameTag, this->GetName()) == 0) {
			for (unsigned i = 0; i < this->tagsCount; ++i) {
				this->tags[i]->RoadToWithin(os, road + len +1);//+1 за да прескоча /
			}
		}

		delete[] currNameTag;
	}
}

bool TagWithTags::Add(Tag * tag, const char * value) {
	for (unsigned i = 0; i < this->tagsCount; ++i) {
		if (this->tags[i]->Add(tag, value)) {
			return true;
		}
	}

	return false;
}

const Tag* TagWithTags::operator[](long pos) const {
	if (pos < 0 || pos >= this->tagsCount) {
		throw std::out_of_range("Invalid position!");
	}

	return this->tags[pos];
}

void TagWithTags::Resize(bool newFlag) {
	unsigned long size = this->tagsCount + this->valueCount;
	bool * newTagOrValue = new bool[size];
	for (unsigned long i = 0; i < size-1; ++i) {
		newTagOrValue[i] = this->tagOrValue[i];
	}
	delete[] this->tagOrValue;
	this->tagOrValue = newTagOrValue;
	this->tagOrValue[size - 1] = newFlag;
}

void TagWithTags::AddTag(Tag * tag) {
	this->tagsCount++;
	this->Resize(true);

	Tag ** newTags = new Tag*[this->tagsCount];
	for (unsigned i = 0; i < this->tagsCount-1; ++i) {
		newTags[i] = this->tags[i];
	}
	delete[] this->tags;
	this->tags = newTags;

	this->tags[this->tagsCount - 1] = tag;
}

void TagWithTags::AddValue(const char * value) {
	this->AddValue(value, strlen(value));
}

void TagWithTags::AddValue(const char * value, unsigned size) {
	this->valueCount++;
	this->Resize(false);

	char ** newValue = new char*[this->valueCount];
	for (unsigned i = 0; i < this->valueCount - 1; ++i) {
		newValue[i] = this->value[i];
	}
	delete[] this->value;
	this->value = newValue;

	this->value[this->valueCount - 1] = new char[size + 1];
	mystrcpy(this->value[this->valueCount - 1], size, value);
}

void TagWithTags::DeleteTag(const unsigned & pos) {
	delete this->tags[pos];
	deleteElementInArr(pos, this->tagsCount, this->tags);
	//изчислчвам коя е позицията в фулевият масив която искам да премахна
	unsigned long posInBoolArr = 0;
	for (unsigned long i = 0, count = 0; i < this->tagsCount + this->valueCount; ++i) {
		if (this->tagOrValue[i]) {
			count++;
		}

		if (count == pos + 1) {
			posInBoolArr = i;
			break;
		}
	}

	deleteElementInArr(posInBoolArr, this->tagsCount + this->valueCount, this->tagOrValue);

	this->tagsCount--;
}

} //oop
} //fmi