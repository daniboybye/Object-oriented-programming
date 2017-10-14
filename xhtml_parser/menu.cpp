#include "menu.h"
#include "functions.hpp"
#include "factoryOnTags.h"
#include <iostream>
#include <cstring>
#include <cassert>

namespace fmi{
namespace oop{

const char Menu::options[Menu::menuOptions][Menu::MAX_SIZE_STR_OPTIONS] = 
{ "> open ", "> exit", "> print","> find ","> erase ", "> add #", "> within ",
									"> create ","> save", "> save as ","> close" };


Menu::Menu()
: userOption(nullptr)
, file(nullptr)
, repeat(true)
{}

Menu::~Menu() {
	delete[] this->userOption;
	delete this->file;
}

void Menu::operator()() {
	this->userOption = new char[Menu::MAX_SIZE_USER_OPTION];

	do {
		std::cout << "Please, enter \"> open \" or \"exit\": " << std::endl;

		std::cin.getline(this->userOption, UINT_MAX);
		if (!std::cin.good()) {
			std::cin.clear();
			std::cin.ignore(UINT_MAX);
			continue;
		}

		else if (str1InBeg2(Menu::options[0], this->userOption)) {
			this->OpenFile(this->userOption + strlen(Menu::options[0]));
		}

		else if (strcmp(Menu::options[1],this->userOption)==0) {
			this->Exit();
		}

		else {
			std::cout << "Invalid instuction!" << std::endl;
		}
	} while (this->repeat);
}

void Menu::OpenFile(const char * fileName) {
	if (fileName == nullptr) return;

	this->file = new XHTMLFile;

	try {
		this->file->operator()(fileName);
		std::cout << "Successfully opened " << fileName << std::endl<<std::endl;
	}
	catch (std::ios_base::failure & exseption) {
		std::cout << exseption.what() << std::endl << std::endl;
		delete this->file;
		this->file = nullptr;
		return;
	}
	catch (std::invalid_argument & exseption) {
		std::cout << exseption.what() << std::endl << std::endl;
		delete this->file;
		this->file = nullptr;
		return;
	}
	catch (const char *& exseption) {
		std::cout << exseption << std::endl << std::endl;
		delete this->file;
		this->file = nullptr;
		return;
	}
	catch (std::runtime_error & exseption) {
		std::cout << exseption.what() << std::endl << std::endl;
		delete this->file;
		this->file = nullptr;
		return;
	}

	this->OpenFileMenu();
}

void Menu::OpenFileMenu() {
	do {
		std::cout << "Please, enter \"> print\" \"> find\" \"> erase\" \n"
				  <<"\"> add\" \"> within\" \"> create\" "
				  <<"\"> save\" \"> save as\" \"> exit\":" << std::endl;

		std::cin.getline(this->userOption, UINT_MAX);
		if (std:: cin.good() == false) {
			std::cin.clear();
			std::cin.ignore(UINT_MAX);
		}

		else if (strcmp(this->userOption, Menu::options[1]) == 0) {
			this->ExitFileOption();
			this->Exit();
		}

		else if (strcmp(this->userOption, Menu::options[2]) == 0) {
			this->file->Print(std::cout);
		}

		else if (str1InBeg2(Menu::options[3], this->userOption)) {
			unsigned count = this->file->GetTag()->Find(this->userOption + strlen(Menu::options[3]));
			std::cout << "Find " << count << " element(s)" << std::endl;
		}

		else if (str1InBeg2(Menu::options[4], this->userOption)) {
			unsigned count = this->file->GetTag()->Erase(userOption + strlen(Menu::options[4]));
			std::cout << "Erased " << count << " element(s)" << std::endl;
		}

		else if (str1InBeg2(Menu::options[5], this->userOption)){

			//разбива стринга на value и tag
			this->AddOption(this->userOption + strlen(Menu::options[5]));
		}

		else if (str1InBeg2(Menu::options[6], this->userOption)) {
			this->file->GetTag()->RoadToWithin(std::cout, this->userOption + strlen(Menu::options[6]));
		}

		else if (str1InBeg2(Menu::options[7], this->userOption)) {

			//разбива на път и tag
			this->CreateOption(this->userOption + strlen(Menu::options[7]));
		}

		else if (strcmp(this->userOption, Menu::options[8]) == 0) {
			this->Save();
		}

		else if (str1InBeg2(Menu::options[9], this->userOption)) {
			this->SaveAs(this->userOption + strlen(Menu::options[9]));
		}

		else if (strcmp(Menu::options[11], this->userOption)==0) {
			this->ExitFileOption();
			delete this->file;
			this->file = nullptr;
			std::cout << "Successfully close" << std::endl << std::endl;
			this->operator()();
		}

		else {
			std::cout << "Invalid instuction!" << std::endl;
		}

		std::cout << std::endl;

	} while (this->repeat);
}

void Menu::Save() {
	try {
		this->file->Save();
		std::cout << "Saved" << std::endl;
	}
	catch (std::ios_base::failure & exseption) {
		std::cout << exseption.what() << std::endl;
	}
}

void Menu::SaveAs(const char * fileName) {
	try {
		this->file->SaveAs(fileName);
		std::cout << "Saved" << std::endl;
	}
	catch (std::ios_base::failure & exseption) {
		std::cout << exseption.what() << std::endl;
	}
}

void Menu::CreateOption(const char * userOption) {
	char * road = readToAngleBracket(userOption);
	if (road == nullptr) {
		std::cout << "Invalid option!" << std::endl;
		return;
	}

	Tag * tag = FactoryOnTags::CreateTag(userOption+strlen(road)+1);
	//излишното го прескачам във фунцията

	if (this->file->GetTag()->Create(tag, road)) {
		std::cout << "Create a new element!" << std::endl;
	}
	else {
		delete tag;
		std::cout << "Option create is bad!" << std::endl;
	}

	delete[] road;
}

void Menu::AddOption(const char * userOption) {
	char * value = readToAngleBracket(userOption);
	if (value == nullptr) {
		std::cout << "Invalid option!" << std::endl;
		return;
	}

	//трябва да се прочете таг
	Tag * tag = FactoryOnTags::CreateTag(userOption);
	if (tag == nullptr) return;

	bool flag = this->file->GetTag()->Add(tag, value);
	delete[] value;

	if (flag) {
		std::cout << "Add a new element!" << std::endl;
		return;
	}

	delete tag;
	std::cout << "Invalid #value!" << std::endl;
}

void Menu::ExitFileOption() {
	std::cout << "Do you want to save?" << std::endl;
	do {
		std::cin.getline(this->userOption, UINT_MAX);
		if (std::cin.good() == false) {
			std::cin.clear();
			std::cin.ignore(UINT_MAX);
			continue;
		}

		if (strcmp(this->userOption, "yes") == 0) {
			this->file->Save();
			return;
		}
		else if (strcmp(this->userOption, "no") == 0) {
			return;
		}
		else {
			std::cout << "Invalid instruction!" << std::endl;
		}
	} while (true);
}

//void Menu::OpenNewFile(const char * str) {
//	unsigned size = strlen(str);
//	char * fileName = new char[ size+ 1];
//	mystrcpy(fileName, size, str);
//	this->ExitFileOption();
//	delete this->file;
//	this->OpenFile(fileName);
//	delete[] fileName;
//	while (this->file==nullptr) {
//		std::cout << "Try again:" << std::endl;
//
//		std::cin.getline(this->userOption, UINT_MAX);
//		if (std::cin.good() == false) {
//			std::cin.clear();
//			std::cin.ignore(UINT_MAX);
//			continue;
//		}
//
//		this->OpenFile(this->userOption);
//	}
//}

} //oop
} //fmi