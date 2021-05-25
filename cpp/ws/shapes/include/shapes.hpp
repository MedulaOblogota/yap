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

#include "point.hpp"//Point

using namespace ilrd;

typedef COLORS Color;
const double PI = 3.14;


class Shape
{
public:
	explicit Shape(const Point& pos = Point(0,0), const double angle = 0, const Color color = COLOR_WHITE);
	Shape(const Shape&);
	virtual ~Shape() {};

	virtual void Draw() = 0;

	void SetPosition(const Point& point_);
	Point GetPosition()const;

	void SetAngle(const double angle_);
	double GetAngle() const;

	void SetColor(const Color color);
	Color GetColor() const;

	void Revolve(const Point& point_, const double angle_);

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

	static Shape* Create(Shape*);

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

	static Shape* Create(Shape *);

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

	static Shape* Create(Square &);

private:
	double m_width;
};

class Rectangle: public Square
{
public:
	explicit Rectangle();
	Rectangle(const Point& pos, const double angle, const Color color, const double width, double hight);

	void Draw();

	static Shape* Create(Rectangle&);

private:
	size_t m_height;
};

class Composite: public Shape
{
public:
	Composite(const Point& pos, const double angle, const Color color);
	Composite(const Composite&);
	~Composite();

	void AddShape(Shape *shape);

	void Draw();

	void SetPosition(const Point& pos);

	void Revolve(const Point& point_, const double angle_);

	static Shape* Create(Composite&);

private:
	std::vector<Shape*> shapes;
};

int KeyboardFunction(unsigned char key, int x, int y);
int MouseFunction(int button, int state, int x, int y);
int MotionFunction(int x, int y);
int TimerFunction();

#endif //RD70_SHAPES
