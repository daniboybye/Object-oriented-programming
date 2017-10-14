#include "functions.hpp"
#include "property.h"
#include <cstring>

namespace fmi{
namespace oop{

bool str1InBeg2(const char * str1, const char * str2) {
	unsigned size = strlen(str1);

	if (size > strlen(str2)) {
		return false;
	}

	for (unsigned i = 0; i < size; ++i) {
		if (str1[i] != str2[i]) {
			return false;
		}
	}
	return true;
}

void mystrcpy(char * helpStr, const unsigned size, const char * str) {
	for (unsigned i = 0; i < size; ++i) {
		helpStr[i] = str[i];
	}
	helpStr[size] = '\0';
}

bool str2InEnd1(const char * str1, const char * str2) {
	unsigned size1 = strlen(str1);
	unsigned size2 = strlen(str2);

	if (size1 < size2) {
		return false;
	}

	for (unsigned i = 0; i < size2; ++i) {
		if (str1[size1 - i] != str2[size2 - i]) {
			return false;
		}
	}

	return true;
}

long readToSlash(const char * str) {
	long count = 0;

	while (*str) {
		if (*str == '/') {
			return count;
		}

		count++;
		str++;
	}

	return -1;
}

char* readToAngleBracket(const char * str) {
	unsigned count = 0;

	while (str[count] != '<') {
		if (str[count] == '\0') {
			return nullptr;
		}
		count++;
	}

	//предполага се че преди '<' има спайс чието преброяване използвам за '\0'
	char * value = new char[count];
	mystrcpy(value, count - 1, str);

	return value;
}

void skipEmptySpace(const char *& str, unsigned long & count) {
	while (*str != '\0' &&
		(*str == '\n' || *str == '\t' || *str == ' ' || *str == '\r')) {
		str++;
		count++;
	}
}

short closeOrNot(const char * str) {
	while (*str != '\0') {
		if (*str == '>') {
			return -1;
		}
		else if (str1InBeg2("/>", str)) {
			return 1;
		}

		str++;
	}

	return 0;
}

void putTabs(std::ostream & os, unsigned count) {
	for (unsigned i = 0; i < count; ++i) {
		os << "\t";
	}
}

} //oop
} //fmi