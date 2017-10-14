#ifndef __FACTORY_HEADER_UNCLUDED_
#define __FACTORY_HEADER_UNCLUDED_

#include "tag.h"
#include "tagWithTags.h"

namespace fmi {
namespace oop {

class FactoryOnTags {
public:
	static Tag* CreateTag(const char*&, unsigned long&);
	static Tag* CreateTag(const char*);

private:
	static Tag* CreateTagWithTags(const char*&, unsigned long&,unsigned&);
	static Tag* CreateTagCloseWithProperties(const char*&, unsigned long&, unsigned&);
	static Tag* CreateTagWithTagAndProperties(const char*&, unsigned long&, unsigned&);
	static Tag* CreateTagClose(const char*&, unsigned long&, unsigned&);
	static void CreateTagValue(const char*&, unsigned long&, TagWithTags*);

	FactoryOnTags();
};

} //oop
} //fmi

#endif //__FACTORY_HEADER_UNCLUDED_