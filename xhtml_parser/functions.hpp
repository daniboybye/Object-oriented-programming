#ifndef __MY_FUNCTIONS_HEADER_UNCLUDED_
#define __MY_FUNCTIONS_HEADER_UNCLUDED_

#include "property.h"
#include "tag.h"
#include <cassert>

namespace fmi{
namespace oop{

bool str1InBeg2(const char*, const char*);

void mystrcpy(char*, const unsigned, const char*);

long readToSlash(const char*);

bool str2InEnd1(const char*, const char*);

//извлича началото от стринг
//че те до '<' и игнорира интервала преди знака
char* readToAngleBracket(const char*);

void skipEmptySpace(const char*&, unsigned long&);

//дали ">"(-1) или "/>"(1) се среща първо в стринга
//ако стринга свърши връща 0
short closeOrNot(const char*);

void putTabs(std::ostream&, unsigned);

template<class T>
inline void deleteElementInArr(unsigned long pos, unsigned long size, T *& objArr) {
	assert(pos < size);

	T * newArr = new T[size - 1];
	bool flag = false;
	for (unsigned i = 0; i < size; ++i) {
		if (i == pos) {
			flag = true;
		}
		else if (flag) {
			newArr[i - 1] = objArr[i];
		}
		else {
			newArr[i] = objArr[i];
		}
	}
	delete[] objArr;
	objArr = newArr;
}

} //oop
} //fmi

#endif //__MY_FUNCTIONS_HEADER_UNCLUDED_