#include "tag.h"
#include "functions.hpp"
#include <cstring>

namespace fmi {
namespace oop {

Tag::Tag(const char * name) {
	if (name == nullptr) {
		throw std::invalid_argument("Name never be null!");
	}

	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

Tag::Tag(const char * name,const unsigned & len) {
	if (name == nullptr) {
		throw std::invalid_argument("Name never be null!");
	}

	this->name = new char[len + 1];
	mystrcpy(this->name, len, name);
}

Tag::~Tag() {
	delete[] this->name;
}

} //oop
} //fmi