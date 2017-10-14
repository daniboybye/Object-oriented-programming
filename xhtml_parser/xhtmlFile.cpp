#include "xhtmlFile.h"
#include "functions.hpp"
#include "factoryOnTags.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>

namespace fmi{
namespace oop{

const char XHTMLFile::validation[]="!DOCTYPE";

const char XHTMLFile::fileExtension[]="xhtml";

XHTMLFile::XHTMLFile()
: name(nullptr)
, firstLine(nullptr)
, tag(nullptr)
{}

void XHTMLFile::operator()(const char * name) {
	if (name == nullptr || str2InEnd1(name, XHTMLFile::fileExtension)==false) {
		throw std::invalid_argument("File's extension is not xhtml!");
	}

	std::ifstream file(name, std::ios::in);
	if (file.good() && file.is_open() == false) {
		file.close();
		throw std::ios_base::failure("File is not open or not good!");
	}

	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);

	this->ReadFile(file);
}

XHTMLFile::~XHTMLFile() {
	delete[] this->name;
	delete[] this->firstLine;
	delete this->tag;
}

void XHTMLFile::ReadFile(std::ifstream & file) {
	file.seekg(0, std::ios::end);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);
	
	//искам да чета на веднъж, но символите в файла са по-малко от размера му
	char * fileStr = new char[size + 1];
	
	//memset(fileStr, 0, size + 1);
	//file.read(fileStr, size);

	for (unsigned long long i = 0; i < size; ++i) {
		file.read(fileStr + i, sizeof(char));
		if (file.eof()) {
			*(fileStr + i) = '\0';
			//std::cout << size << "\t" << i << std::endl;
			break;
		}
		else if (file.fail()) {
			delete[] fileStr;
			file.close();
			throw  std::ios_base::failure("Reading file is fail!");
		}
	}
	
		/*std::cout << file.good();
		std::cout << file.fail();
		std::cout << file.eof();
		fileStr[size] = '\0';*/
		//std::cout << fileStr;

	/*if (file.good() == false) {
		delete[] fileStr;
		file.close();
		throw  std::ios_base::failure("Reading file is fail!");
	}*/
	
	file.close();

	this->CreateTree(fileStr);

	delete[] fileStr;
}

void XHTMLFile::Save() const {
	this->SaveFile(this->name);
}

void XHTMLFile::SaveAs(const char * fileName) const {
	if (fileName == nullptr || str2InEnd1(fileName, XHTMLFile::fileExtension) == false) {
		std::cout << "File's ectension is not xhtml!" << std::endl;
		return;
	}

	this->SaveFile(fileName);
}

void XHTMLFile::SaveFile(const char * fileName) const {
	std::ofstream file(fileName, std::ios::out);
	if (file.good() && file.is_open() == false) {
		file.close();
		throw std::ios_base::failure("Problem with save!");
	}

	this->Print(file);

	file.close();
}

void XHTMLFile::Print(std::ostream & os) const {
	os << "<" << this->firstLine << ">" << "\n";
	this->tag->Print(os);
	os << "\n";

}

void XHTMLFile::ReadFirstLine(char *& fileStr,unsigned long & count) {
	skipEmptySpace((const char*&)fileStr, count);

	if (*fileStr != '<') {
		throw "Invalid xhtml document!";
	}
	fileStr++;//за да пескоча скобата
	count++;

	if (str1InBeg2(XHTMLFile::validation, fileStr) == false) {
		throw "Invalid xhtml document!";
	}

	unsigned len = 0;
	fileStr += strlen(XHTMLFile::validation);
	len += strlen(XHTMLFile::validation);

	while (*fileStr) {
		if (*fileStr == '>') {
			break;
		}

		fileStr++;
		len++;
	}

	this->firstLine = new char[len + 1];
	mystrcpy(this->firstLine, len, (fileStr - len));
	count += len;

	fileStr++;
	count++;//да пескоча втората скоба
}

void XHTMLFile::CreateTree(char *& fileStr) {
	unsigned long count = 0;
	this->ReadFirstLine(fileStr,count);

	Tag * tag;
	tag = FactoryOnTags::CreateTag((const char*&)fileStr, count);
	if (tag == nullptr) {
		throw "Invalid xhtml file!";
	}

	this->tag=tag;

	fileStr -= count;
}

} //oop
} //fmi