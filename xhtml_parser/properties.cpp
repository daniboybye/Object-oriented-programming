#include "properties.h"

namespace fmi {
namespace oop {

Properties::Properties()
	: properties(nullptr)
	, count(0)
{}

Properties::Properties(const char * str)
	: Properties() {
	this->AddProperty(str);
}

Properties::Properties(const char ** str, unsigned count)
	: Properties() {
	for (unsigned i = 0; i < count; ++i) {
		this->AddProperty(str[i]);
	}
}

Properties::~Properties() {
	this->Clean();
}

Property& Properties::operator[](long pos) {
	if (pos < 0 || pos >= this->count) {
		throw std::out_of_range("Invalid position!");
	}

	return *this->properties[pos];
}

Property Properties::operator[](long pos) const {
	if (pos < 0 || pos >= this->count) {
		throw std::out_of_range("Invalid position!");
	}

	return *this->properties[pos];
}

void Properties::AddProperty(const char * str) {
	this->Resize();
	this->properties[this->count - 1] = new Property(str);
}

void Properties::AddProperty(const char *& str, unsigned long & count) {
	this->Resize();
	this->properties[this->count - 1] = new Property(str, count);
}

void Properties::Resize() {
	this->count++;
	Property ** newProperties = new Property*[this->count];

	for (unsigned i = 0; i < this->count - 1; ++i) {
		newProperties[i] = this->properties[i];
	}
	delete[] this->properties;
	this->properties = newProperties;
}

void Properties::Clean() {
	for (unsigned i = 0; i < this->count; ++i) {
		delete this->properties[i];
	}

	delete[] this->properties;
}

bool Properties::DoYouHaveThisValue(const char * value) const {
	for (unsigned i = 0; i < this->count; ++i) {
		if (strcmp(this->properties[i]->GetValue(), value) == 0) {
			return true;
		}
	}

	return false;
}

std::ostream& operator<<(std::ostream & os, const Properties & properties) {
	unsigned size = properties.GetPropertiesCount();
	for (unsigned i = 0; i < size; ++i) {
		os << properties[i];
		if (i != size - 1) {
			os << " ";
		}
	}

	return os;
}

} //oop
} //fmi