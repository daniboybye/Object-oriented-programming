#include "tagWithTagsAndProperties.h"
#include "functions.hpp"
#include <iostream>

namespace fmi {
namespace oop {

TagWithTagsAndProperties::TagWithTagsAndProperties(const char * name)
:	TagWithTags(name)
{
	this->properties = new Properties;
}

TagWithTagsAndProperties::TagWithTagsAndProperties
			(const char * name, unsigned size)
: TagWithTags(name, size)
{
	this->properties = new Properties;
}

TagWithTagsAndProperties::~TagWithTagsAndProperties() {
	delete this->properties;
}

void TagWithTagsAndProperties::Print(std::ostream & os, unsigned tab) const {
	putTabs(os, tab);
	os << "<" << this->GetName();

	if (this->GetProperties()->GetPropertiesCount() != 0) {
		os << " ";
		os << *this->GetProperties();
	}
	os << ">\n";

	this->Within(os,tab+1);

	putTabs(os, tab);
	os << "</" << this->GetName() << ">";
}

bool TagWithTagsAndProperties::Add(Tag  * tag, const char * value) {
	if (this->properties->DoYouHaveThisValue(value)) {
		this->AddTag(tag);
		return true;
	}

	return this->TagWithTags::Add(tag,value);
}

} //oop
} //fmi

