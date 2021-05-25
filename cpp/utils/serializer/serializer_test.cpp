#include <iostream>
#include <fstream>
#include <boost/shared_ptr.hpp>
#include <vector>

#include "shapes2.hpp"

#include "serializer.hpp"

std::vector<Shape *> shapes_vector;

void DrawFunc()
{
  int size = shapes_vector.size();
  std::cout << "size is " << size << std::endl;
  for(int i = 0; i < size; ++i)
  {
    Shape *sh = &(*shapes_vector[i]);
    sh->Draw();
  }
}

int main()
{
  Deserializer<Shape> ds;
  boost::shared_ptr<Shape> line2;
  boost::shared_ptr<Shape> comp2;
  Line line(Point(50,50), 0, COLOR_WHITE, 500);
  Line line3(Point(6,5), 10, COLOR_MAGENTA, 400);
  std::ofstream myfile;
  myfile.open ("example.txt");
  ds.Serialize(myfile, line);

  Composite composite(Point(0,0), 0, COLOR_WHITE);
  composite.AddShape(&line);
  composite.AddShape(&line3);
  // ds.Serialize(myfile, composite);

  myfile.close();
	std::ifstream inputfile("example.txt");

	if (inputfile.is_open())
	{
		ds.Add<Line>();
    // ds.Add<Composite>();
		line2 = ds.Deserialize(inputfile);
		shapes_vector.push_back(&(*line2));
    // comp2 = ds.Deserialize(inputfile);
	}
	else
	{
		std::cout << "baaaad" << std::endl;
	}

  std::cout << (*line2).GetPosition().GetX() << std::endl;



	DrawInit(0, NULL, 1000, 1000, DrawFunc);
	 //DrawSetTimerFunc(TimerFunction, 100);
	 DrawMainLoop();


}
