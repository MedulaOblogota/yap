#ifndef Polygon_OL70 /*header guard*/
#define Polygon_OL70

/*******************************************************************************
* The functions in this file handle a Polygon
* structure. It will be denoted as Polygon.
*
*
* Written by: Roy Yablonka, OL-70
* Last update: 17:00 , 15.10.2019
*******************************************************************************/

#include <cstddef>

#include "point.h"

struct Polygon
{
	explicit Polygon(size_t numPoints = 0);
	~Polygon();
	Polygon(const Polygon& other_);
	Polygon& operator=(const Polygon& other_);

	void Add(const Point &p);
	bool IsEqual(const Polygon& other_) const;
	void Print() const;

	size_t m_numPoints;
	Point *m_points;
};

#endif  /*Polygon_OL70*/
