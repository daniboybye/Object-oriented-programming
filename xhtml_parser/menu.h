#ifndef __MENU_HEADER_UNCLUDED_
#define __MENU_HEADER_UNCLUDED_

#include "xhtmlFile.h"

namespace fmi{
namespace oop{

class Menu {
public:
	Menu();
	~Menu();
	void operator()();//меню за потребителя

private:
	static const unsigned short menuOptions =11;
	static const unsigned short MAX_SIZE_STR_OPTIONS = 16;
	static const unsigned short MAX_SIZE_USER_OPTION = 512;
	static const char options[menuOptions][MAX_SIZE_STR_OPTIONS];

	char * userOption;
	XHTMLFile * file;
	bool repeat;

	//отваряме файла
	//при фeйл програмата приключва
	void OpenFile(const char*);
	//опции към вече отвореният файл
	void OpenFileMenu();
	void Save();
	void SaveAs(const char*);
	void CreateOption(const char*);
	void AddOption(const char*);
	void ExitFileOption();
	char* CreateValueFromStr(const char*);
	void Exit() { this->repeat = false; }
	//void OpenNewFile(const char*);

	Menu(const Menu&);
	void operator=(const Menu&);
};

} //oop
} //fmi

#endif //__MENU_HEADER_UNCLUDED_