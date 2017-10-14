#ifndef __PROPERTY_INLINE_FUNCTIONS_HEADER_
#define __PROPERTY_INLINE_FUNCTIONS_HEADER_

#include "property.h"

namespace fmi {
namespace oop {

inline const char* Property::GetName() const {
	return this->name;
}

inline const char* Property::GetValue() const {
	return this->value;
}

inline bool Property::GetQuote() const {
	return this->dounleOrSingleQuote;
}

} //oop
} //fmi

#endif //__PROPERTY_INLINE_FUNCTIONS_HEADER_