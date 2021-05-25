#include "surpriser.hpp"

int main()
{
  Surpriser *todaysSurprise = Surpriser::GetRandomSurprise();

  todaysSurprise->SurpriseMe();

  delete todaysSurprise;

  return 0;
}
