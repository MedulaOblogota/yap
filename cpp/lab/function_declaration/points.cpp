#include <iostream>
#include <math.h>


#include "point.h"

Point Point::AdjustBy(const Point *point)
{
	this->x += point->x;
	this->y += point->y;

	return (*(this));
}

Point Point::AdjustBy(int dx, int dy)
{
	this->x += dx;
	this->y += dy;

	return (*(this));
}

float Point::Length() const
{
	return (sqrt(x*x + y*y));
}

void Point::Print(char open, char close) const
{
	std::cout << open << this->x << "," << this->y << close << std::endl;
}

void Point::Print(ParenthesesType parentheses) const
{
	if (parentheses == ROUND)
	{
		Print('(', ')');
	}
	else if (parentheses == SQUARE)
	{
		Print('[', ']');
	}
	else if (parentheses == CURLY)
	{
		Print('{', '}');
	}
	else
	{
		Print('<', '>');
	}
}

Point Add(Point first, Point second)
{
	Point point;
	point.x = first.x + second.x;
	point.y = first.y + second.y;

	return point;
}

int main()
{
	Point first;
	Point second;
	Point third;

	int max;

	std::cout << "input max value" << std::endl;

	std::cin >> max;

	first.x = 3;
	first.y = 4;

	while ((first.x % max != first.x) || first.x < 0)
	{
		std::cout<<"input first dots x value"<<std::endl;
		std::cin >> first.x;
	}
	while ((first.y % max != first.y) || first.y < 0)
	{
		std::cout<<"input first dots y value"<<std::endl;
		std::cin >> first.y;
	}

	second.x = 6;
	second.y = 8;

	first.Print('(', ')');
	second.Print('(', ')');

	first.AdjustBy(&second);

	first.Print(Point::SQUARE);

	std::cout << "seconds length=" << second.Length() << std::endl;

	third = Add(first, second);

	std::cout << "add for both points. x=" << third.x << ". y=" << third.y << std::endl;

	first = first.AdjustBy(&third).AdjustBy(&third).AdjustBy(&second);

	std::cout << "did first.AdjustBy(3, 3).AdjustBy(1,1).AdjustBy(second)" << std::endl;

	first.Print(Point::SQUARE);

	return 0;
}
