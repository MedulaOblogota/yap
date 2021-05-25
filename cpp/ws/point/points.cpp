#include <iostream>
#include <math.h>

#include "point.h"

Point::Point()
	: x(0), y(0)
{
	length = -1;
}

Point::Point(int x_, int y_)
	: x(x_ ), y(y_)
{
	length = -1;
}

int Point::GetX()
{
	return x;
}
int Point::GetY()
{
	return y;
}

Point &Point::AdjustBy(int dx, int dy)
{
	this->x += dx;
	this->y += dy;
	// g_totalLength -= length;
	this->length = -1;

	return (*(this));
}

Point &Point::AdjustBy(const Point &point)
{
	this->x += point.x;
	this->y += point.y;
	// g_totalLength -= length;
	this->length = -1;

	return (*(this));
}

float Point::Length() const
{
	if (length < 0)
	{
		std::cout << "calculating length" << std::endl;
		length = sqrt(x*x + y*y);
		// g_totalLength += length;
	}

	return (length);
}

void Point::Print(char open, char close) const
{
	std::cout << open << this->x << "," << this->y << close << std::endl;
}

void Point::Print(ParenthesesType parentheses) const
{
	char open_and_close[] = {'(', '[', '{', '<', ')', ']', '}', '>'};

	Print(open_and_close[parentheses], open_and_close[parentheses + 4]);
}

bool Point::IsEqual(const Point &point) const
{
	return (point.x == x && point.y == y);
}

Point Add(Point first, Point second, int max)
{
	Point point(first.GetX() + second.GetX(), first.GetY() + second.GetY());

	return point;
}
