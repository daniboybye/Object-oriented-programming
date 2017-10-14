#include "factoryOntags.h"
#include "tagWithTags.h"
#include "tagWithTagsAndProperties.h"
#include "tagClose.h"
#include "tagCloseWithProperties.h"
#include "functions.hpp"
#include <iostream>

namespace fmi {
namespace oop {

Tag* FactoryOnTags::CreateTag(const char *& fileStr, unsigned long & count) {
	if (fileStr == nullptr) {
		throw std::invalid_argument("Invalid argument in Factory!");
	}

	while (*fileStr != '\0' && *fileStr != '<'){
		fileStr++;
		count++;
	}

	if (*fileStr == '\0') {
		std::cout << "Comand is short!" << std::endl;
		return nullptr;
	}

	fileStr++;
	count++;
	//да проскоча '<';

	//следващата дума е името на тага
	unsigned len = 0;

	while (*fileStr != '\0') {
		if (*fileStr == '>') {
			return FactoryOnTags::CreateTagWithTags(fileStr, count,len);
		}

		else if (str1InBeg2(" />", fileStr)) {
			return FactoryOnTags::CreateTagClose(fileStr, count, len);
		}

		else if (*fileStr == ' ') {
			short flag = closeOrNot(fileStr);

			if (flag == 1) {
				return FactoryOnTags::CreateTagCloseWithProperties(fileStr, count, len);
			}

			else if (flag == -1) {
				return FactoryOnTags::CreateTagWithTagAndProperties(fileStr, count, len);
			}
		}

		fileStr++;
		count++;
		len++;
	}
}

Tag* FactoryOnTags::CreateTag(const char * fileStr) {
	unsigned long count;
	//формален аргумент за да използам готовата логика
	return FactoryOnTags::CreateTag(fileStr, count);
}

void FactoryOnTags::CreateTagValue
			(const char *& fileStr, unsigned long & count,TagWithTags * tag) {

	while (*fileStr != '\0') {
		skipEmptySpace((const char*&)fileStr, count);

		if (str1InBeg2("</", fileStr)) {
			fileStr += 2;
			count += 2;//3 за </
			if (str1InBeg2(tag->GetName(), fileStr) == false) {
				std::cout << "You haven't close tag " << tag->GetName() << " in on the right place" << std::endl;
				throw std::runtime_error("closing tags in the wrong order");
			}
			fileStr += 1 +strlen(tag->GetName());
			count += 1 + strlen(tag->GetName());
			return;
		}
		else if (*fileStr == '<') {
			Tag * newTag = FactoryOnTags::CreateTag(fileStr, count);
			if (newTag == nullptr) return;

			tag->AddTag(newTag);
		}
		else {
			unsigned len = 0;
			while (*fileStr != '\0' && *fileStr != '<') {
				fileStr++;
				len++;
			}

			tag->AddValue(fileStr - len, len);
			count += len;
		}
	}
}

Tag* FactoryOnTags::CreateTagCloseWithProperties
	(const char *& fileStr, unsigned long & count, unsigned & len) {

	TagCloseWithProperties * tag =
		new TagCloseWithProperties(fileStr - len, len);

	skipEmptySpace((const char*&)fileStr, count);
	while (str1InBeg2("/>", fileStr) == false) {
		tag->GetProperties()->AddProperty((const char*&)fileStr, count);
		skipEmptySpace((const char*&)fileStr, count);

		if (*fileStr == '\0') return tag;
	}

	fileStr += 2;//"/>"
	count += 2;

	return tag;
}

Tag* FactoryOnTags::CreateTagWithTagAndProperties
	(const char *& fileStr, unsigned long & count, unsigned & len) {

	TagWithTagsAndProperties * tag =
		new TagWithTagsAndProperties(fileStr - len, len);

	skipEmptySpace((const char*&)fileStr, count);
	while (*fileStr != '>') {
		tag->GetProperties()->AddProperty((const char*&)fileStr, count);
		skipEmptySpace((const char*&)fileStr, count);

		if (*fileStr == '\0') return tag;
	}

	fileStr++;//за скобата;
	count++;

	//добавям съдържание
	FactoryOnTags::CreateTagValue(fileStr, count,tag);

	return tag;
}


Tag* FactoryOnTags::CreateTagClose
			(const char *& fileStr,unsigned long & count, unsigned & len) {

	Tag * tag = new TagClose(fileStr - len, len);

	fileStr += 3;//за " />", по стандарт трябва да има празно място
	count += 3;

	return tag;
}

Tag* FactoryOnTags::CreateTagWithTags
			(const char *& fileStr, unsigned long & count, unsigned & len) {

	TagWithTags * tag = new TagWithTags(fileStr - len, len);

	fileStr++;//да прескоча счупената скоба
	count++;

	FactoryOnTags::CreateTagValue(fileStr, count, tag);

	return tag;
}

} //oop
} //fmi