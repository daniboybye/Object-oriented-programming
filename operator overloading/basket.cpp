#include "basket.hpp"
#include <iostream>
#include <fstream>
#include <cassert>

Basket::Basket(const char *owner)
: owner(owner)
, eggs()
{}

void Basket::GetReport() const 
{
	std::ofstream file("report_" + owner + ".txt", std::ios::out);

	if ( (file.is_open() && file.good()) == false) 
	{
		file.close();
		throw std::ios_base::failure("Report file is fail or not open!");
		return;
	}

	file << *this;
	file.close();
}

void Basket::SetOwner(const char *name) 
{
	if (name == nullptr)
		throw std::invalid_argument("Owner's name is not to be null!");
	
	owner = name;
}

void Basket::check(const int pos) const
{
	if(pos >= int( GetEggsCount() ))
		throw std::out_of_range("This basket is small!");

	if (pos < 0)
		throw std::out_of_range("Basket size is positiv");
}

const Egg& Basket::operator[](const int pos) const 
{
	check(pos);
	return eggs[pos];
}

Egg& Basket::operator[](const int pos)
{
	check(pos);
	return eggs[pos];
}

Basket& Basket::operator+=(const Basket &other) 
{
	/* 
		не бих го написал така,
		но искам да демонстрирам
		извикването на двете версии на оператор[]
	*/

	const unsigned size = GetEggsCount();
	eggs.resize(size + other.GetEggsCount(),"");

	for (unsigned i = 0; i < other.GetEggsCount(); ++i)
		(*this)[size + i] = other[i];

	return *this;
}

Basket& Basket::operator*=(const int number)
{
	for (unsigned i = 0; i < GetEggsCount(); ++i)
		eggs[i] *= number;
	//(*this)[i] може да използваме нашият оператор

	return *this;
}

//неефективна версия, но кратка O(N^2)
Basket& Basket::operator%=(const Basket &other) 
{
	if (this == &other)//Защо??
	{
		eggs.clear();
		return *this;
	}

	for (unsigned i = 0; i < other.GetEggsCount(); ++i)
		DeleteEggs(other.eggs[i]);

	return *this;
}

std::ostream& operator<<(std::ostream &os, const Basket &basket)
{
	os << basket.GetOwner() << std::endl;

	os << "Eggs:" << std::endl;

	for (unsigned i = 0; i < basket.GetEggsCount(); ++i)
		os << '\t' << basket[i] << std::endl;

	return os;
}