#include <cstdio>
#include <iostream>

#include "fraction.hpp"
#include "tests.h"

using namespace ilrd;
// using namespace std;

int main()
{
	Fraction r1, r2(1,2);
	// std::cout << "counter = " << r2.GetCounter() << std::endl;
	// printf("counter = %lu\n", r2.GetCounter());

	WrapperCompareInt("static counter of objects", r1.GetCounter() == 2, 1);
	// std::cout << "counter = " << r1.GetCounter() << std::endl;

	if (true)
	{
		Fraction r3;
		WrapperCompareInt("static counter of objects", r1.GetCounter() == 3, 1);
	}
	WrapperCompareInt("static counter of objects", r1.GetCounter() == 2, 1);

	Fraction fraction1(3,4);
	Fraction fraction2(10,1);
	Fraction fraction3(1,0);
	Fraction fraction4;
	Fraction fraction5(1,2);
	Fraction fraction1equal(3,4);
	// fraction1.AddToSelf(fraction2);
	// printf("counter = %d\n", fraction1.GetCounter());

	WrapperCompareInt("IsUndefined", fraction3.IsUndefined(), 1);
	WrapperCompareInt("IsUndefined", fraction2.IsUndefined(), 0);

	WrapperCompareInt("Default Constructor", fraction4.GetNumerator(), 0);
	WrapperCompareInt("Default Constructor", fraction4.GetDenominator(), 1);

	WrapperCompareInt("IsEqual (between fractions)", fraction1 == fraction1equal, 1);
	WrapperCompareInt("IsEqual (between fractions)", fraction1 == fraction2, 0);
	WrapperCompareInt("IsEqual (between ints)", fraction2 == 10, 1);
	WrapperCompareInt("IsEqual (between ints)", fraction1 == 10, 0);

	// fraction1.Print();
	// fraction5.Print();
	// (fraction1+fraction5).Print();
	WrapperCompareInt("Addition (between fractions)", (fraction1 + fraction5) == Fraction(10,8), 1);
	WrapperCompareInt("Addition (between fraction and int)", (fraction1 + 2) == Fraction(11,4), 1);
	WrapperCompareInt("Substraction (between fractions)", (fraction1 - fraction5) == Fraction(2,8), 1);
	WrapperCompareInt("Substraction (between fractions)", (fraction1 - 2) == Fraction(-5,4), 1);

	WrapperCompareInt("Unary operator +", fraction1 == +fraction1, 1);
	WrapperCompareInt("Making Sure fraction1 is the same value as before...", fraction1 == Fraction(3,4), 1);
	WrapperCompareInt("Unary operator -", Fraction(-3, 4) == -fraction1, 1);


	WrapperCompareInt("Prefix Addition", ++fraction1 == Fraction(7,4), 1);
	WrapperCompareInt("Prefix Substraction", --fraction1 == Fraction(3,4), 1);

	WrapperCompareInt("Postfix Addition", fraction1++ == Fraction(3,4), 1);
	WrapperCompareInt("Postfix Substraction", fraction1-- == Fraction(7,4), 1);

	++fraction5;

	WrapperCompareInt("making sure Prefix Addition changes value", fraction5 == Fraction(3,2), 1);
	--fraction5;
	fraction5++;
	WrapperCompareInt("making sure Postfix Addition changes value", fraction5 == Fraction(3,2), 1);
	fraction5--;


	Fraction f1(1,2);
	// printf("counter = %d\n", f1.GetCounter());
	Fraction f2(3,4);

	WrapperCompareInt("+f1 + -(++f2) = -10/8", (+f1 + -(++f2)) == Fraction(-10,8), 1);
	WrapperCompareInt("making sure f1 didnt change", f1 == Fraction(1,2), 1);

	WrapperCompareInt("((1/2)++) - +((7/4)--) = -10/8", ((f1++) - +(f2--)) == Fraction(-10,8), 1);
	// fraction1 = (f1++) - +(f2--);
	// fraction1.Print();

	// printf("counter = %d\n", f1.GetCounter());

	std::cout << f1 << " + " << f2 << " = " << f1 + f2 << std::endl;

	std::cout << f1 << " + " << f2 << " = " << f1 + f2 << std::endl;

	f1+=f2;
	// std::cout << "f1+=f2 -> " << f1 << std::endl;
	WrapperCompareInt("+= operator for fraction", ((f1) == (Fraction(18, 8))), 1);
	f1-=f2;
	WrapperCompareInt("-= operator for fraction", ((f1) == (Fraction(48, 32))), 1);

	f1+=2;
	WrapperCompareInt("+= operator for int", ((f1) == (Fraction(48, 32) + 2)), 1);

	f1-=2;
	WrapperCompareInt("-= operator for int", ((f1) == (Fraction(48, 32))), 1);

	WrapperCompareInt("using ZERO const", (f1+Fraction::ZERO) == f1, 1);
	WrapperCompareInt("using ONE const", (f1+Fraction::ONE) == (f1+1), 1);
	WrapperCompareInt("using HALF const", (f1+Fraction::HALF) == (f1+Fraction(1,2)), 1);


	f1 + f2;
	f1 + 3;
	3 + f1;
	3.3 + f1;

	std::cout << "f1 = " << f1 << std::endl;

	std::cout << "3.3 + f1 = " << 3.3 + f1 << std::endl;

}
