#include <iostream>	//cout
#include <string>	//string

#include "factory.hpp"
#include "shapes.hpp"

using namespace ilrd;
typedef Shape* (*LineCreator)(Composite&);

std::vector<Shape *> shapes_vector;

void DrawFunc()
{
  int size = shapes_vector.size();
  std::cout << size << std::endl;
  for(int i = 0; i < size; ++i)
  {
    Shape *sh = shapes_vector[i];
    sh->Draw();
  }
}

int main(int argc, char** argv)
{
  std::string str1("Line");
  Point p1(500,500);
  Line *line = new Line(p1, 50, COLOR_WHITE, 500);
  Circle *circle = new Circle(p1, 0, COLOR_RED, 250);
  // Composite *composite = new Composite(p1, 0, COLOR_RED);
  // composite->AddShape(line);
  // composite->AddShape(circle);

  Factory<Shape *, std::string, Shape *, Shape* (*)(Shape *)> factory;

  // factory.add("Circle", Line::Create);
  factory.add("Line", Line::Create);
  factory.add("Circle", Circle::Create);

  Shape *shape = factory.create("Circle", (Shape *)circle);
  Shape *shape2 = factory.create("Line", (Shape *)line);
  shapes_vector.push_back(shape2);
  shapes_vector.push_back(shape);

  DrawInit(argc, argv, 1000, 1000, DrawFunc);
   //DrawSetTimerFunc(TimerFunction, 100);
   DrawMainLoop();

   return 0;
}
