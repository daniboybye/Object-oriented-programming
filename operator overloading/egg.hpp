#pragma once

#ifndef _EGG_HEADER_INCLUDED_
#define _EGG_HEADER_INCLUDED_

#include <iostream>
#include <string>

class Egg 
{
public:
	Egg(const char *name,const unsigned size = 1);
	Egg(const Egg&) = default ;
	Egg& operator= (const Egg&) = default;
	~Egg() = default;


	/*
	�� ���� �� � ���� �������,
	������ �� ����� �� ������� ������������ ������� �� �����������.
	(������� �������� �� ���� ��������� � this, egg >> cin ?!)

	��� ������� ��������� ���� �������,
	���������� �� �� ����������� ����� �����,
	������ �� �� �������� friend
	*/
	friend std::istream& operator>>(std::istream&, Egg&);

	Egg& operator*=(const unsigned number);
	Egg& operator+=(const int number);
	
	/*
	int x = 3;
	x-- = 4;
	==>  �� �� ���������

	�� ������� ��
	int x = 3;
	--x = 4;

	�� ������ ������ ���������
	*/

	Egg& operator++();
	const Egg operator++(int);

	Egg& operator--();
	const Egg operator--(int);

	unsigned GetSize() const;
	const std::string& GetName() const;

	operator unsigned() const;

private:
	std::string name;
	unsigned size;
};

std::ostream& operator<<(std::ostream&, const Egg&);

inline Egg::operator unsigned() const
{
	return size;
}

inline unsigned Egg::GetSize() const
{
	return size;
}

inline const std::string& Egg::GetName() const
{
	return name;
}

inline bool operator==(const Egg &lhs, const unsigned &rhs)
{
	return lhs.GetSize() == rhs;
}

inline bool operator==(const Egg &lhs, const std::string &rhs)
{
	return lhs.GetName() == rhs;
}

inline bool operator==(const Egg &lhs, const char* rhs)
{
	return rhs && lhs.GetName() == rhs;
}

inline bool operator==(const Egg &lhs, const Egg &rhs)
{
	return lhs.GetSize() == rhs.GetSize()
		&& lhs.GetName() == rhs.GetName();
}

inline bool operator>(const Egg &lhs, const Egg &rhs)
{
	return lhs.GetSize() > rhs.GetSize();
}

//���������� ��� ����������� �� ���������
inline bool operator!=(const Egg &lhs, const Egg &rhs) 
{
	return !(lhs == rhs);
}

inline bool operator>=(const Egg &lhs, const Egg &rhs) 
{
	return (lhs > rhs) || (lhs == rhs);
}

inline bool operator<=(const Egg &lhs, const Egg &rhs) 
{
	return !(lhs > rhs);
}

inline bool operator< (const Egg &lhs, const Egg &rhs) 
{
	return !(lhs >= rhs);
}

//���������� ��� ��������+=
inline const Egg operator+(const Egg &lhs, const int rhs)
{
	Egg temp(lhs);
	return temp += rhs;
}

inline const Egg operator+(const int lhs, const Egg &rhs)
{
	return rhs + lhs;
}

#endif //_EGG_HEADER_INCLUDED_