#ifndef __XHTML_FILE_HEADER_UNCLUDED_
#define __XHTML_FILE_HEADER_UNCLUDED_

#include <fstream>
#include "tagClose.h"
#include "tagCloseWithProperties.h"
#include "tagWithTags.h"
#include "tagWithTagsAndProperties.h"

namespace fmi{
namespace oop{

class XHTMLFile {
public:
	XHTMLFile();
	~XHTMLFile();

	void operator()(const char*);

	void Print(std::ostream&) const;
	void Save() const;
	void SaveAs(const char*) const;
	Tag* const GetTag() const;

	static const char* GetFileExtension();

private:
	static const char validation[];
	static const char fileExtension[];
	
	char * name;
	char * firstLine;
	//обикновенно първият ред е специфичен, а аз не покривам валюдациите му

	Tag * tag;//до колкото знам може да има само един главен таг
	

	void ReadFile(std::ifstream&);
	void CreateTree(char*&);
	void SaveFile(const char*) const;
	void ReadFirstLine(char*&,unsigned long&);


	XHTMLFile(const XHTMLFile&);
	void operator=(const XHTMLFile&);
};

} //oop
} //fmi

#include "xhtmlFile.hpp"

#endif //__FILE_HEADER_UNCLUDED_