#ifndef RD70_SHAPES
#define RD70_SHAPES

/*
COMPILE WITH:
gp ../shapes.cpp ../main.cpp ../../point/points.cpp -Wl,-rpath=. ../lib/libglut_utils.so ../lib/libpoint.a -I ../include/

AT ./SRC dir
*/

#include <cstdlib>//size_t
#include <iostream>//std
#include <vector>//vector
#include <typeinfo>//typeinfo

#include "glut_utils.h"

#include "point.hpp"//Point

using namespace ilrd;

typedef COLORS Color;
const double PI = 3.14;

class Shape;
class Line;
class Composite;

std::ostream& operator<<(std::ostream& os_, const Shape& shape_);

// std::ostream& operator<<(std::ostream& os_, const Color& color_);
// std::istream& operator>>(std::istream& in, Shape& shape_);
std::istream& operator>>(std::istream& in_, Line& line_);
std::istream& operator>>(std::istream& in_, Composite& composite_);

class Shape
{
public:
	explicit Shape(const Point& pos = Point(0,0), const double angle = 0, const Color color = COLOR_WHITE);
	Shape(const Shape&);
	virtual ~Shape() {};

	virtual void Draw() = 0;
	virtual void ToStream(std::ostream&)const=0;

	// virtual std::string OutputToString(std::ostream& os_)const {};

	void SetPosition(const Point& point_);
	Point GetPosition()const;

	void SetAngle(const double angle_);
	double GetAngle() const;

	void SetColor(const Color color);
	Color GetColor() const;

	void Revolve(const Point& point_, const double angle_);

	// friend std::ostream& operator<<(std::ostream& os_, const Shape& shape_);

protected:
	Point m_pos;
	double m_angle;
	Color m_color;

	Shape& operator=(const Shape& shape_);
};

class Line: public Shape
{
public:
	explicit Line();
	Line(const Point& pos, const double angle, const Color color, const double length);

	void Draw();

	double GetLength()const;
	void SetLength(double length);

	// static Shape* Create(std::istream& );

	void ToStream(std::ostream&)const;

	// friend std::istream& operator>>(std::istream& in_, const Line& line_);
	// std::string OutputToString(std::ostream& os_)const;

private:
	double m_length;
};

class Circle: public Shape
{
public:
	explicit Circle();
	Circle(const Point& pos, const double angle, const Color color, const double radius);

	void Draw();

	void SetRadius(const double radius);
	double GetRadius() const;

	static Shape* Create(std::istream& );

	// std::string OutputToString(std::ostream& os_)const;

private:
	double m_radius;
};

class Square: public Shape
{
public:
	explicit Square();
	Square(const Point& pos, const double angle, const Color color, const double width);
	double GetWidth() const;

	void Draw();

	static Shape* Create(std::istream& );

	// std::string OutputToString(std::ostream& os_)const;

private:
	double m_width;
};

class Rectangle: public Square
{
public:
	explicit Rectangle();
	Rectangle(const Point& pos, const double angle, const Color color, const double width, double hight);

	void Draw();

	static Shape* Create(std::istream& );

	// std::string OutputToString(std::ostream& os_) const;

private:
	size_t m_height;
};

class Composite: public Shape
{
public:
	Composite(const Point& pos, const double angle, const Color color);
	Composite();
	Composite(const Composite&);
	~Composite();

	void AddShape(Shape *shape);

	std::vector<Shape*> GetShapes();

	void Draw();

	void SetPosition(const Point& pos);

	void Revolve(const Point& point_, const double angle_);

	// static Shape* Create(std::istream& );

	void ToStream(std::ostream&)const;

	// std::string OutputToString(std::ostream& os_)const;

public:
	std::vector<Shape*> shapes;
};

int KeyboardFunction(unsigned char key, int x, int y);
int MouseFunction(int button, int state, int x, int y);
int MotionFunction(int x, int y);
int TimerFunction();

#endif //RD70_SHAPES
