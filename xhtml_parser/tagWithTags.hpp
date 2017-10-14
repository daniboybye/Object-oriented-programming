#ifndef __TAG_WITH_TAGS_INLINE_FUNCTIONS_HEADER_UNCLUDED_
#define __TAG_WITH_TAGS_INLINE_FUNCTIONS_HEADER_UNCLUDED_

#include "tagWithTags.h"

namespace fmi {
namespace oop {

inline unsigned TagWithTags::GetTagsCount() const {
	return this->tagsCount;
}

inline unsigned TagWithTags::GetValueCount() const {
	return this->valueCount;
}

//inline Tag** TagWithTags::GetTags() const {
//	return this->tags;
//}

} //oop
} //fmi

#endif //__TAG_WITH_TAGS_INLINE_FUNCTIONS_HEADER_UNCLUDED_