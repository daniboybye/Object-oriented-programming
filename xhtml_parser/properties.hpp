#ifndef __PROPERTIES_INLINE_FUNCTIONS_HEADER_
#define __PROPERTIES_INLINE_FUNCTIONS_HEADER_

#include "properties.h"

namespace fmi {
namespace oop {

inline unsigned Properties::GetPropertiesCount() const {
	return this->count;
}

} //oop
} //fmi

#endif // __PROPERTIES_INLINE_FUNCTIONS_HEADER_