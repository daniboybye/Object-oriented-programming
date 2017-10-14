#ifndef __XHTML_FILE_INLINE_FUNCTIONS_HEADER_
#define __XHTML_FILE_INLINE_FUNCTIONS_HEADER_

#include "xhtmlFile.h" 

namespace fmi {
namespace oop {

inline const char* XHTMLFile::GetFileExtension() {
	return XHTMLFile::fileExtension;
}

inline Tag* const XHTMLFile::GetTag() const {
	return this->tag;
}

} //oop
} //fmi

#endif //__XHTML_FILE_INLINE_FUNCTIONS_HEADER_