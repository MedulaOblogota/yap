#include <iostream>//std
#include <cstdio>//printf
#include <ctime>//rand

#include "glut_utils.h"//DrawSet funcs
// #include "point.hpp"//Point
#include "shapes.hpp"//Shape

using namespace ilrd;

std::vector<Shape *> g_shapes;
double width, height;
float l = 500;
double rad;
double x, y;
Point p1;


double xCircle = 500;
double yCircle = 400;
double rCircle = 200;
int drawCircle = 1;

Circle *circle1 = new Circle(Point(xCircle,yCircle), 20, COLOR_RED, rCircle);
Square *sqaure1 = new Square(Point(xCircle,yCircle), 0, COLOR_WHITE, 100);

Circle circle2(Point(500,500), 0, COLOR_WHITE, 300);

Composite composite2(p1, 20, COLOR_YELLOW);

void BuildComposite()
{
  float angle = 40;
  Point rev(10, 3);
  int input;

  Composite *composite = new Composite(p1, 20, COLOR_YELLOW);

  std::cout << "For Composite, Enter your shape darling" << std::endl
  << "1. Line" << std::endl
  << "2. Square" << std::endl
  << "3. Rectangle" << std::endl
  << "4. Circle" << std::endl
  << "5. Return to main Menu" << std::endl;

  std::cin >> input;

  while (input != 5)
  {
    std::cout << "x: ";
    std::cin >> x;

    std::cout << "y: ";
    std::cin >> y;

    p1 = Point(x,y);

    std::cout <<"angle: ";
    std::cin >> angle;

    switch (input)
    {
      case 1:
      {
        std::cout << "line length: ";
        std::cin >> l;
        Line *line = new Line(p1, angle, COLOR_WHITE, l);
        composite->AddShape(line);
        break;
      }

      case 2:
      {
        std::cout << "side length: ";
        std::cin >> width;
        Square *square = new Square(p1, angle, COLOR_WHITE, width);
        composite->AddShape(square);
        break;
      }

      case 3:
      {
        std::cout << "side length: ";
        std::cin >> width;
        std::cout << "height length: ";
        std::cin >> height;
        Rectangle *rectangle = new Rectangle(p1, angle, COLOR_RED, width, height);
        composite->AddShape(rectangle);
        break;
      }

      case 4:
      {
        std::cout << "radius: ";
        std::cin >> rad;
        Circle *circle = new Circle(p1, angle, COLOR_RED, rad);
        composite->AddShape(circle);
        break;
      }

      default:
          break;
    }

    std::cout << "For Composite, Enter your shape darling" << std::endl
    << "1. Line" << std::endl
    << "2. Square" << std::endl
    << "3. Rectangle" << std::endl
    << "4. Circle" << std::endl
    << "5. Return to main Menu" << std::endl;

    std::cin >> input;
  }

  g_shapes.push_back(composite);
}

static void UserInput()
{
  int input = 0;
  float angle = 40;
  Point rev(10, 3);

  std::cout << "Enter your shape buddy" << std::endl
  << "1. Line" << std::endl
  << "2. Square" << std::endl
  << "3. Rectangle" << std::endl
  << "4. Circle" << std::endl
  << "5. Composite of Shapes" << std::endl
  << "6. Exit" << std::endl;

  std::cin >> input;

  while (input != 6)
  {
    if (input != 5)
    {
      std::cout << "x: ";
      std::cin >> x;

      std::cout << "y: ";
      std::cin >> y;

      p1 = Point(x,y);

      std::cout <<"angle: ";
      std::cin >> angle;
    }

    switch (input)
    {
      case 1:
      {
        std::cout << "line length: ";
        std::cin >> l;
        Line *line = new Line(p1, angle, COLOR_WHITE, l);
        g_shapes.push_back(line);
        break;
      }

      case 2:
      {
        std::cout << "side length: ";
        std::cin >> width;
        Square *square = new Square(p1, angle, COLOR_WHITE, width);
        g_shapes.push_back(square);
        break;
      }

      case 3:
      {
        std::cout << "side length: ";
        std::cin >> width;
        std::cout << "height length: ";
        std::cin >> height;
        Rectangle *rectangle = new Rectangle(p1, angle, COLOR_RED, width, height);
        g_shapes.push_back(rectangle);
        break;
      }

      case 4:
      {
        std::cout << "radius: ";
        std::cin >> rad;
        Circle *circle = new Circle(p1, angle, COLOR_RED, rad);
        g_shapes.push_back(circle);
        break;
      }

      case 5:
      {
        BuildComposite();
        break;

      }
      default:
        break;
    }

    std::cout << "Enter your shape buddy" << std::endl
    << "1. Line" << std::endl
    << "2. Square" << std::endl
    << "3. Rectangle" << std::endl
    << "4. Circle" << std::endl
    << "5. Composite of Shapes" << std::endl
    << "6. Exit" << std::endl;

    std::cin >> input;
  }
}

// void DrawFunction()
// {
//   float l = 500;
//   float angle = 40;
//   Point rev(10, 3);
//   size_t i = 0;
//   size_t size = 0;
//
//   Line line(p1, angle, COLOR_WHITE, l);
//
//   g_shapes.push_back(&line);
//
//   Circle circle(p1, angle, COLOR_RED, 100);
//   g_shapes.push_back(&circle);
//
//   Square square(p1, angle, COLOR_WHITE, 40);
//   g_shapes.push_back(&square);
//   size = g_shapes.size();
//
//   for (i = 0; i < size; ++i)
//   {
//     Shape *shape = g_shapes.at(i);
//     shape->Draw();
//   }
// }

void DrawFunctionIO()
{
  size_t size = 0;

  size = g_shapes.size();

  for (size_t i = 0; i < size; ++i)
  {
    Shape *shape = g_shapes.at(i);
    shape->Draw();
  }
}

int MouseFunction(int button, int state, int x, int y)
{
    static double rad;
    printf("Mouse: %d,%d,%d,%d\n", button, state, x, y);

    if (state == 1 && button == MOUSE_WHEEL_UP)
    {
      rad = circle2.GetRadius();
      rad *= 1.1;
      circle2.SetRadius(rad);
      return 1;
    }
    if (state == 1 && button == MOUSE_WHEEL_DOWN)
    {
      rad = circle2.GetRadius();
      rad *= 0.9;
      circle2.SetRadius(rad);
      return 1;
    }

    if (button == MOUSE_LEFT)
    {
        drawCircle = state;
        return 1;
    }

    return 0;
}

int KeyboardFunction(unsigned char key, int x, int y)
{
    printf("Keyboard: %02x,%d,%d\n", key, x, y);

    if (key == 0x1b /* ESC */)
        return -1;

    return 0;
}

int MotionFunction(int x, int y)
{
    printf("Mouse: %d,%d\n", x, y);

    return 0;
}

int TimerFunction()
{
  std::srand(std::time(NULL));
  double rand_x = std::rand() % 1000;
  std::srand(std::time(NULL));
  double rand_y = std::rand() % 1000;

  // std::cout << "rand_x=" << rand_x << ". randy=" << rand_y << std::endl;
  static Point randPoint(rand_x,rand_y);
  composite2.Revolve(randPoint, 20);

  return 1;  /* draw */
}

int main()
{
  UserInput();

  composite2.AddShape(circle1);
  composite2.AddShape(sqaure1);
  g_shapes.push_back(&composite2);

  g_shapes.push_back(&circle2);

  DrawInit(0, NULL, 1000, 1000, DrawFunctionIO);

  DrawSetKeyboardFunc(KeyboardFunction);
  DrawSetMouseFunc(MouseFunction);
  DrawSetMotionFunc(MotionFunction);
  DrawSetTimerFunc(TimerFunction, 1000);

  DrawMainLoop();

  return 0;
}
