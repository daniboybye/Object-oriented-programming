#ifndef __TAG_WITH_TAGS_AND_PROPERTIES_INLINE_FUNCTIONS_HEADER_
#define __TAG_WITH_TAGS_AND_PROPERTIES_INLINE_FUNCTIONS_HEADER_

#include "tagWithTagsAndProperties.h"

namespace fmi {
namespace oop {

inline Properties* TagWithTagsAndProperties::GetProperties() const {
	return this->properties;
}

} //oop
} //fmi

#endif //__TAG_WITH_TAGS_AND_PROPERTIES_INLINE_FUNCTIONS_HEADER_
