#pragma once

#ifndef _BASKET_HEADER_INCLUDED_
#define _BASKET_HEADER_INCLUDED_ 

#include "egg.hpp"
#include <vector>

class Basket 
{
	public:       
		Basket(const char*);
		Basket(const Basket&) = default;
		Basket& operator= (const Basket&) = default;
		~Basket() = default;

		const std::string& GetOwner() const;
		unsigned GetEggsCount() const;
		void GetReport() const;

		void SetOwner(const char*);
		void AddEgg(const char*,const unsigned);
		void AddEgg(const Egg&);

		void DeleteEggs(const char *name);
		void DeleteEggs(const Egg& egg);
		void DeleteEggs(const std::string& name);
		void DeleteEggs(const unsigned size);

		const Egg& operator[](const int) const;
		Egg& operator[](const int);
		
		Basket& operator+=(const Basket&);
		Basket& operator+=(const Egg&);
		Basket& operator*=(const int);
		Basket& operator%=(const Basket&);

	private:    
		std::string owner;
		std::vector<Egg> eggs;

		/*типът Т трябва да има реализиран
		оператор== със class Egg */
		template<typename T>
		void DeleteEggsTemplate(T value)
		{
			for (unsigned i = 1; i <= eggs.size(); ++i)
			{
				if (eggs[i-1] == value)
				{
					--i;
					std::swap(eggs.back(), eggs[i]);
					eggs.pop_back();
				}
			}
		}

		void check(const int pos) const;
};

std::ostream& operator<<(std::ostream&, const Basket&);

inline const Basket operator+(const Basket &lhs, const Basket &rhs) 
{
	Basket temp(lhs);
	return temp += rhs;
}

inline const Basket operator*(const Basket& other, const int number) 
{	
	Basket temp(other);
	return temp *= number;
}

inline Basket operator*(const int number, const Basket &basket) 
{
	return basket * number;
}

inline const Basket operator%(const Basket &lhs, const Basket &rhs)
{
	Basket temp(lhs);
	return temp %= rhs;
}

inline const std::string& Basket::GetOwner() const 
{
	return owner;
}

inline unsigned Basket::GetEggsCount() const 
{
	return eggs.size();
}

inline void Basket::AddEgg(const char *name, const unsigned size)
{
	eggs.emplace_back(name, size);
}

inline void Basket::AddEgg(const Egg &egg)
{
	eggs.push_back(egg);
}

inline Basket& Basket::operator+=(const Egg &egg)
{
	AddEgg(egg);
	return *this;
}

inline const Basket operator+(const Basket& basket, const Egg &egg)
{
	Basket temp(basket);
	return temp += egg;
}

inline void Basket::DeleteEggs(const char *name)
{
	DeleteEggsTemplate(name);
}

inline void Basket::DeleteEggs(const Egg& egg)
{
	DeleteEggsTemplate(egg);
}

inline void Basket::DeleteEggs(const unsigned size)
{
	DeleteEggsTemplate(size);
}

inline void Basket::DeleteEggs(const std::string& name)
{
	DeleteEggsTemplate(name);
}

#endif //_BASKET_HEADER_INCLUDED_