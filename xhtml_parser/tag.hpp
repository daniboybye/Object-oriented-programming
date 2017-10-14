#ifndef __TAG_INLINE_FUNTIONS_
#define __TAG_INLINE_FUNTIONS_

#include "tag.h"

namespace fmi {
namespace oop {

inline const char* Tag::GetName() const {
	return this->name;
}

} //oop
} //fmi

#endif //__TAG_INLINE_FUNTIONS_