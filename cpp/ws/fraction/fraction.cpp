#include <iostream>

#include "fraction.hpp"

namespace ilrd
{

const Fraction Fraction::ZERO(0,1);
const Fraction Fraction::HALF(1,2);
const Fraction Fraction::ONE(1,1);

size_t Fraction::f_cntr = -3;		//as 3 Fractions were made above as consts

static void SortFraction(Fraction &fraction)
{
	if ((fraction.GetNumerator() < 0) && (fraction.GetDenominator() < 0))
	{
		fraction.SetNumerator(-fraction.GetNumerator());
		fraction.SetDenominator(-fraction.GetDenominator());
	}
}

Fraction::Fraction(int numerator_, int denominator_)
	: numerator(numerator_), denominator(denominator_)
{
	++f_cntr;
}

Fraction::~Fraction()
{
	--f_cntr;
}

bool Fraction::IsUndefined() const
{
	return (0 == denominator);
}

size_t Fraction::GetCounter() const
{
	return f_cntr;
}

Fraction& Fraction::operator+=(const Fraction& other_)
{
	numerator = numerator * other_.denominator + other_.numerator * denominator;
	denominator = other_.denominator * denominator;

	return (*this);
}

Fraction& Fraction::operator-=(const Fraction& other_)
{
	return (*this += -other_);
}

Fraction operator+(const Fraction& first, const Fraction& other_)
{
	Fraction ret(first);

	return (ret += other_);
}

Fraction operator-(const Fraction& first, const Fraction& other_)
{
	Fraction ret(first);

	return (ret -=other_);
}

Fraction& Fraction::operator++()
{
	*this = *this + 1;

	return (*this);
}

Fraction& Fraction::operator--()
{
	*this = *this - 1;

	return (*this);
}

Fraction Fraction::operator++(int)
{
	Fraction tmp = *this;

	*this = *this + 1;

	return (tmp);
}

Fraction Fraction::operator--(int)
{
	Fraction tmp = *this;

	*this = *this - 1;

	return (tmp);
}

void Fraction::Print() const
{
	std::cout << numerator << "/" << denominator << std::endl;
}

bool operator==(const Fraction& first, const Fraction& other_)
{
	return ((first-other_).GetNumerator() == 0);
}

int Fraction::GetNumerator() const
{
	return numerator;
}

int Fraction::GetDenominator() const
{
	return denominator;
}

void Fraction::SetNumerator(int numerator_)
{
	numerator = numerator_;
}

void Fraction::SetDenominator(int denominator_)
{
	denominator = denominator_;
}

int Fraction::ToInt() const
{
	return (numerator/ denominator);
}

double Fraction::ToDouble() const
{
	return ((double)numerator/denominator);
}

std::ostream& operator<<(std::ostream& os_, const Fraction& fraction_)
{
	return os_ << fraction_.GetNumerator() << "/" << fraction_.GetDenominator();
}
}
