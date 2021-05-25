#include <cstdlib>    //random
#include <fstream>    //ofstream
#include <iostream>   //std::cout
#include <ctime>      //srand

#include "surpriser.hpp"

Surpriser* Surpriser::GetRandomSurprise()
{
  srand(time(NULL));
  int random = rand() % 3;
  Surpriser* lut[3] = {new First, new Second, new Third};

  return lut[random];
}

// void Surpriser::SurpriseMe()
// { }

void First::SurpriseMe()
{
  std::cout << "Surprise!" << std::endl;
}

void Second::SurpriseMe()
{
  system("echo -e '\\a'");
}

void Third::SurpriseMe()
{
  std::ofstream fs;
  fs.open("nothing_here.txt");
  fs.close();
}
