#include "tagCloseWithProperties.h"
#include "functions.hpp"
#include <iostream>

namespace fmi {
namespace oop {

TagCloseWithProperties::TagCloseWithProperties(const char * name)
	: TagClose(name)
{
	this->properties = new Properties;
}

TagCloseWithProperties::TagCloseWithProperties
	(const char * name, unsigned size)
	: TagClose(name, size)
{
	this->properties = new Properties;
}

TagCloseWithProperties::~TagCloseWithProperties()
{
	delete this->properties;
}

void TagCloseWithProperties::Print(std::ostream & os, unsigned tab) const {
	putTabs(os, tab);
	os << *this;
}

std::ostream& operator<<(std::ostream & os, const TagCloseWithProperties & tag) {
	os << "<" << tag.GetName();

	if (tag.GetProperties()->GetPropertiesCount() != 0) {
		os << " ";
		os << *tag.GetProperties();
	}

	os << " />";

	return os;
}

} //oop
} //fmi