#ifndef __TAG_CLOSE_WITH_PROPERTIES_INLINE_FUNTIONS_HEADER_
#define __TAG_CLOSE_WITH_PROPERTIES_INLINE_FUNTIONS_HEADER_

#include "tagCloseWithProperties.h"

namespace fmi {
namespace oop {

inline Properties* TagCloseWithProperties::GetProperties() const {
	return this->properties;
}

}
}

#endif //__TAG_CLOSE_WITH_PROPERTIES_INLINE_FUNTIONS_HEADER_