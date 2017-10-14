#ifndef __TAG_CLOSE_INLINE_FUNCTIONS_HEADER_UNCLUDED_
#define __TAG_CLOSE_INLINE_FUNCTIONS_HEADER_UNCLUDED_

#include "tagClose.h"

namespace fmi {
namespace oop {

inline unsigned TagClose::Find(const char*) const {
	return 0;
}

inline unsigned TagClose::Erase(const char*) {
	return 0;
}

//тези тагове нямат съдържание и не може да имат
inline void TagClose::Within(std::ostream&, unsigned) const {
	return;
}

inline void TagClose::RoadToWithin(std::ostream&, const char*) const {
	return;
}

inline bool TagClose::Add(Tag*, const char*) {
	return false;
}

inline bool TagClose::Create(Tag*, const char*) {
	return false;
}

} //oop
} //fmi

#endif //__TAG_CLOSE_INLINE_FUNCTIONS_HEADER_UNCLUDED_