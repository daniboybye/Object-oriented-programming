#include "property.h"
#include "functions.hpp"
#include <cstring>
#include <iostream>

namespace fmi {
namespace oop  {

Property::Property(const char * str) {
	unsigned long count = 0;
	this->Init(str,count);
}

Property::Property(const char *& str, unsigned long & count) {
	this->Init(str, count);
}

Property::Property(const Property & other) {
	this->CopyFrom(other);
}

Property& Property::operator=(const Property & other) {
	if (this != &other) {
		this->Clean();
		this->CopyFrom(other);
	}

	return *this;
}

void Property::CopyFrom(const Property & other) {
	this->name = new char[strlen(other.name) + 1];
	strcpy(this->name, other.name);

	this->value = new char[strlen(other.value) + 1];
	strcpy(this->value, other.value);
}

Property::~Property() {
	this->Clean();
}

void Property::Clean() {
	delete[] this->name;
	delete[] this->value;
}

std::ostream& operator<<(std::ostream & os, const Property & propert) {
	os << propert.GetName() << "=";
	if (propert.GetQuote()){
		os << "\"";
	}
	else {
		os << "'";
	} 
	os << propert.GetValue();
	if (propert.GetQuote()){
		os << "\"";
	}
	else {
		os << "'";
	}
	return os;
}

void Property::Init(const char *& str,unsigned long & count) {
	if (str == nullptr) {
		throw std::invalid_argument("Property's name is not null!");
	}

	this->CreateName(str, count);
	this->CreateValue(str, count);
}

void Property::CreateName(const char *& str, unsigned long & count) {
	unsigned long begPos = count;
	while (*str != '\0' && *str != '=') {
		count++;
		str++;
	}

	if (*str != '=') {
		std::cout << "Unexpected char <" << (*str) << ">, expected one of: =" << std::endl;
		throw std::invalid_argument("Invalid porperty!");
	}

	this->name = new char[count - begPos + 1];
	mystrcpy(this->name, count - begPos, str - count + begPos);

	str++;//прескачам равното
	count++;
}

void Property::CreateValue(const char *& str, unsigned long & count) {
	skipEmptySpace(str,count);

	if (*str != '"' && *str != '\'') {
		std::cout << "Unexpected char <" << (*str) << ">, expected one of: \" '" << std::endl;
		throw std::invalid_argument("Invalid porperty!");
	}
	else if (*str == '"') {
		this->dounleOrSingleQuote = true;
	}
	else {
		this->dounleOrSingleQuote = false;
	}


	str++;//да прескоча първата кавичка
	count++;
	unsigned begPos = count;

	if (this->dounleOrSingleQuote) {
		while (*str != '\0' && *str != '"') {
			str++;
			count++;
		}
	}
	else {
		while (*str != '\0' && *str != '\'') {
			str++;
			count++;
		}
	}

	if (*str != '\'' &&  *str != '"') {
		std::cout << "Unexpected char <" << (*str) << ">, expected one of: =" << std::endl;
		throw std::invalid_argument("Invalid porperty!");
	}
	

	this->value = new char[count - begPos + 1];
	mystrcpy(this->value, count - begPos, str - count + begPos);

	str++;//да прескоча втората кавичка
	count++;
}

} //oop
} //fmi 