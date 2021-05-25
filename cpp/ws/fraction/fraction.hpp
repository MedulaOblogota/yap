#ifndef Fraction_OL70 /*header guard*/
#define Fraction_OL70

/*******************************************************************************
* The functions in this file handle a Fraction
* structure. It will be denoted as Fraction.
*
*
* Written by: Roy Yablonka, OL-70
* Last update: 18:00 , 15.10.2019
*******************************************************************************/
#include <iostream>

namespace ilrd
{
struct Fraction;

std::ostream& operator<<(std::ostream& os_, const Fraction& fraction_);

Fraction operator+(const Fraction& first, const Fraction& other_);
Fraction operator-(const Fraction& first, const Fraction& other_);

bool operator==(const Fraction& first, const Fraction& other_);

struct Fraction
{
public:
	Fraction(int numerator_ = 0, int denominator_ = 1); //non explicit on purpose
	~Fraction();

	// generated assignment operator and copy ctor are perfect
	
	int GetNumerator() const;
	int GetDenominator() const;
	void SetNumerator(int numerator_);
	void SetDenominator(int denominator_);

	bool IsUndefined() const;

	size_t GetCounter() const;

	Fraction& operator+=(const Fraction& other_);
	Fraction& operator-=(const Fraction& other_);

	void Print() const;


	inline Fraction operator+() const;
	inline Fraction operator-() const;

	Fraction& operator++();
	Fraction& operator--();

	Fraction operator++(int);
	Fraction operator--(int);

	int ToInt() const;
	double ToDouble() const;

	static const Fraction ZERO;
	static const Fraction HALF;
	static const Fraction ONE;

private:
	int numerator;
	int denominator;

	static size_t f_cntr;
};

inline Fraction Fraction::operator+() const
{
	return (*this);
}

inline Fraction Fraction::operator-() const
{
	return (Fraction(-numerator, denominator));
}

}//namespace ilrd
#endif /*Fraction_OL70*/
