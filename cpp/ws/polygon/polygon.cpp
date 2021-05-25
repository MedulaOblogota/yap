#include <iostream>
#include <cstdio>

#include "polygon.hpp"

Polygon::Polygon(size_t numPoints)
	: m_points(new Point[numPoints]), m_numPoints(numPoints)
{
	std::cout << "in Polygon Constructor" << std::endl;
}

Polygon::~Polygon()
{
	delete[] m_points;
}

Polygon::Polygon(const Polygon &other_)
	:	m_numPoints(other_.m_numPoints)
{
	size_t i = 0;

	for (i = 0; i < m_numPoints; ++i)
	{
		m_points[i] = other_.m_points[i];
	}
}

Polygon& Polygon::operator=(const Polygon& other_)
{
	size_t i = 0;

	m_numPoints = other_.m_numPoints;

	for (i = 0; i < m_numPoints; ++i)
	{
		m_points[i] = other_.m_points[i];
	}
}

void Polygon::Add(const Point &p)
{
	Point *new_m_points = new Point[m_numPoints + 1];
	size_t i = 0;

	for (i = 0; i < m_numPoints; ++i)
	{
		new_m_points[i] = m_points[i];
	}

	new_m_points[m_numPoints] = p;

	delete m_points;

	m_points = new_m_points;
	++m_numPoints;
}

bool Polygon::IsEqual(const Polygon& other_) const
{
	size_t i = 0;

	if (other_.m_numPoints != m_numPoints)
	{
		return false;
	}

	for (i = 0; i < m_numPoints; ++i)
	{
		if ((m_points[i].GetX() != other_.m_points[i].GetX()) || ((m_points[i].GetY() != other_.m_points[i].GetY())))
		{
			return false;
		}
	}

	return true;
}

void Polygon::Print() const
{
	size_t i = 0;

	for (i = 0; i < m_numPoints; ++i)
	{
		printf("point %lu: ", i);
		m_points[i].Print('(', ')');
	}
}
