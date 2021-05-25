#include <cstdio>

#include "polygon.hpp"
#include "point.h"

int main()
{
	Polygon polygon(5);
	Polygon polygon2(5);

	Point p(3,4);
	Point p2(1,6);

	polygon.Add(p);
	polygon2.Add(p2);

	printf("polygon1==polygon2 -> %d\n", polygon.IsEqual(polygon2));

	polygon.Print();
	printf("\n");
	polygon2.Print();
}
