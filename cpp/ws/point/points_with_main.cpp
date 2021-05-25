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
		g_totalLength += length;
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

bool IsInRange(Point point, int max)
{

	if ((point.GetX() % max != point.GetX()) || point.GetX() < 0)
	{
		return 0;
	}
	if ((point.GetY() % max != point.GetY()) || point.GetY() < 0)
	{
		return 0;
	}

	return 1;
}

int main()
{
	int max;

	Point first(3,4);
	Point second(6,8);
	Point third(0,0);
	Point equal1(5,7);
	Point equal2(5,7);

	std::cout << "input max value" << std::endl;

	std::cin >> max;

	if (!IsInRange(first, max) || !IsInRange(second, max) || !IsInRange(equal1, max) || !IsInRange(equal2, max))
	{
		printf("your points are not in range, sorry!\n");
		return 1;
	}

	printf("first: ");
	first.Print(Point::ANGULAR);

	printf("second: ");
	second.Print('(', ')');

	first.AdjustBy(second);

	printf("first after adjustment: ");
	first.Print();

	std::cout << "seconds length=" << second.Length() << std::endl;

	// third = Add(first, second, max);

	// std::cout << "add for both points. x=" << third.GetX() << ". y=" << third.GetY() << std::endl;

	printf("second: ");
	second.Print();
	printf("third: ");
	third.Print();
	printf("first: ");
	first.Print(Point::SQUARE);
	std::cout << "did first.AdjustBy(3, 3).AdjustBy(second).AdjustBy(second)" << std::endl;
	first.AdjustBy(3,3).AdjustBy(second).AdjustBy(second);
	first.Print(Point::SQUARE);

	std::cout << "equal1 and equal are equal - " << equal1.IsEqual(equal2) << std::endl;

	std::cout << "length (should enter if)=" << first.Length() << std::endl;

	std::cout << "length (shouldnt enter if)=" << first.Length() << std::endl;

	std::cout << "point1 length=" << first.Length() << std::endl;
	std::cout << "point2 length=" << second.Length() << std::endl;
	std::cout << "point3 length=" << third.Length() << std::endl;
	std::cout << "equal1 length=" << equal1.Length() << std::endl;
	std::cout << "equal2 length=" << equal2.Length() << std::endl;
	std::cout << "g_totalLength=" << g_totalLength << std::endl;
	std::cout << "arithmetic lengths combined = " << first.Length() + second.Length() + third.Length() + equal1.Length() + equal2.Length() << std::endl;


	return 0;
}
