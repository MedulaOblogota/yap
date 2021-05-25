#include <math.h>//cos
#include <cstdio>//printf
#include "point.hpp"//Point
#include "glut_utils.h"//draw
#include "shapes.hpp"

Shape::Shape(const Point& pos, const double angle, const Color color)
  : m_pos(pos), m_angle(angle), m_color(color)
{}

Shape::Shape(const Shape& shape)
  : m_pos(shape.m_pos), m_angle(shape.m_angle), m_color(shape.m_color)
{}

void Shape::SetPosition(const Point& point_)
{
  m_pos = point_;
}

Point Shape::GetPosition() const
{
  return m_pos;
}

void Shape::SetAngle(const double angle_)
{
  m_angle = angle_;
}

double Shape::GetAngle() const
{
  return m_angle;
}

void Shape::SetColor(const Color color)
{
  m_color = color;
}

Color Shape::GetColor() const
{
  return m_color;
}

void Shape::Revolve(const Point& point_, const double angle_)
{
  m_pos.Revolve(point_, angle_);
}

Line::Line(const Point& pos, const double angle, const Color color, const double length)
  : Shape(pos, angle, color), m_length(length)
{}

void Line::Draw()
{
  double x1_g = GetPosition().GetX();
  double y1_g = GetPosition().GetY();

  double x2_g = m_length * cos(GetAngle() * PI / 180) + x1_g;
  double y2_g = m_length * sin(GetAngle() * PI / 180) + y1_g;

  DrawPolygon(GetColor(), 2, int(x1_g), int(y1_g), int(x2_g), int(y2_g));
}

Shape* Line::Create(Shape *line)
{
  // Point p1(500,500);
  // double angle = 45;
  // size_t l = 500;
  //
  // Line *line = new Line(p1, angle, COLOR_WHITE, l);

  return new Line(*(Line *)line);
}

Circle::Circle(const Point& pos, const double angle, const Color color, const double radius)
  : Shape(pos, angle, color), m_radius(radius)
{}

void Circle::Draw()
{
  double r_g = m_radius;
  double center_x = GetPosition().GetX();
  double center_y = GetPosition().GetY();

  DrawCircle(GetColor(), center_x, center_y, r_g);
}

void Circle::SetRadius(const double radius)
{
  m_radius = radius;
}

double Circle::GetRadius() const
{
  return m_radius;
}

Shape* Circle::Create(Shape *circle)
{
  // Point p1(500,500);
  // double angle = 45;
  // size_t l = 500;
  //
  // Line *line = new Line(p1, angle, COLOR_WHITE, l);

  return new Circle(*(Circle *)circle);
}

Square::Square(const Point& pos, const double angle, const Color color, const double width)
  : Shape(pos, angle, color), m_width(width)
{}

void Square::Draw()
{
  double g_XbL = GetPosition().GetX();
  double g_YbL = GetPosition().GetY();
  double g_XbR = g_XbL + m_width*cos(GetAngle() * PI/ 180);
  double g_YbR = g_YbL + m_width*sin(GetAngle() * PI/ 180);
  double g_XtL = g_XbL - m_width*cos(PI/2 - GetAngle()  * PI/ 180);
  double g_YtL = g_YbL + m_width*sin(PI/2 - GetAngle()  * PI/ 180);
  double g_XtR = g_XbR - m_width*cos(PI/2 - GetAngle()  * PI/ 180);
  double g_YtR = g_YbR + m_width*sin(PI/2 - GetAngle()  * PI/ 180);

  DrawPolygon(GetColor(), 4, (int)g_XbL, (int)g_YbL,
                          (int)g_XbR, (int)g_YbR,
                          (int)g_XtR, (int)g_YtR,
                          (int)g_XtL, (int)g_YtL);

}

double Square::GetWidth() const
{
  return m_width;
}

Shape* Square::Create(Square &square)
{
  // Point p1(500,500);
  // double angle = 45;
  // size_t l = 500;
  //
  // Line *line = new Line(p1, angle, COLOR_WHITE, l);

  return new Square(square);
}

Rectangle::Rectangle(const Point& pos, const double angle, const Color color, const double width, double height)
  : Square(pos, angle, color, width), m_height(height)
{}

void Rectangle::Draw()
{
  double g_XbL = GetPosition().GetX();
  double g_YbL = GetPosition().GetY();
  double g_XbR = g_XbL + GetWidth()*cos(GetAngle()  * PI/ 180);
  double g_YbR = g_YbL + GetWidth()*sin(GetAngle()  * PI/ 180);
  double g_XtL = g_XbL - m_height*cos(PI/2 - GetAngle() * PI/ 180);
  double g_YtL = g_YbL + m_height*sin(PI/2 - GetAngle() * PI/ 180);
  double g_XtR = g_XbR - m_height*cos(PI/2 - GetAngle() * PI/ 180);
  double g_YtR = g_YbR + m_height*sin(PI/2 - GetAngle() * PI/ 180);

  DrawPolygon(GetColor(), 4, (int)g_XbL, (int)g_YbL,
                          (int)g_XbR, (int)g_YbR,
                          (int)g_XtR, (int)g_YtR,
                          (int)g_XtL, (int)g_YtL);
}

Shape* Rectangle::Create(Rectangle &rectangle)
{
  // Point p1(500,500);
  // double angle = 45;
  // size_t l = 500;
  //
  // Line *line = new Line(p1, angle, COLOR_WHITE, l);

  return new Rectangle(rectangle);
}

Composite::Composite(const Point& pos, const double angle, const Color color)
  : Shape(pos, angle, color), shapes()
{}

Composite::Composite(const Composite& composite)
  : Shape(composite.m_pos, composite.m_angle, composite.m_color), shapes()
{
  size_t size = composite.shapes.size();
  for (size_t i = 0; i < size; ++i)
  {
    // Shape *shape = new Shape(composite.shapes.at(i));
    // shapes.push_back(shape);
    // Shape *sh = new Shape(*(composite.shapes.at(i)));
    // AddShape(sh);
    // AddShape((composite.shapes.at(i)));
  }
}

Composite::~Composite()
{
  size_t size = shapes.size();
  size_t i = 0;

  for (i = 0; i < size; ++i)
  {
    delete shapes.at(i);
  }
}

void Composite::AddShape(Shape *shape)
{
  Point shapePos = shape->GetPosition();

  shapePos += GetPosition();
  shape->SetPosition(shapePos);
  shapes.push_back(shape);
}

void Composite::SetPosition(const Point& new_point)
{
  Point original_point = GetPosition();
  Point diff = new_point - original_point;
  Shape::SetPosition(new_point);
  size_t vector_size = shapes.size();
  size_t i = 0;

  for(i = 0; i < vector_size; ++i)
  {
      Point curr_poss = shapes.at(i)->GetPosition();
      shapes.at(i)->SetPosition(curr_poss + diff);
  }
}

void Composite::Draw()
{
  size_t size = shapes.size();
  size_t i = 0;

  for (i = 0; i < size; ++i)
  {
    Shape *shape = shapes.at(i);
    shape->Draw();
  }
}

void Composite::Revolve(const Point& pivot, const double angle)
{
    size_t vector_size = shapes.size();
    size_t i = 0;

    for(i = 0; i < vector_size; ++i)
    {
        shapes.at(i)->Revolve(pivot, angle);
    }
}


Shape* Composite::Create(Composite& composite)
{
  return new Composite(composite);
}
