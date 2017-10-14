#include "tagClose.h"
#include "functions.hpp"
#include <cstring>
#include <iostream>

namespace fmi {
namespace oop {

TagClose::TagClose(const char * name)
	: Tag(name)
{}

TagClose::TagClose(const char * name, unsigned size)
	: Tag(name, size)
{}

TagClose::~TagClose()
{}

void TagClose::Print(std::ostream & os, unsigned tab) const {
	putTabs(os, tab);
	os << *this;
}

std::ostream& operator<<(std::ostream & os, const TagClose & tag) {
	os << "<" << tag.GetName() << " />";

	return os;
} 

} //oop
} //fmi