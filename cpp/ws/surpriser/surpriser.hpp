#ifndef SURPRISER_OL70
#define SURPRISER_OL70

class Surpriser
{
public:
  static Surpriser* GetRandomSurprise();
  virtual void SurpriseMe()=0;
  virtual ~Surpriser() {};
};

class First: public Surpriser
{
public:
  void SurpriseMe();
};

class Second: public Surpriser
{
public:
  void SurpriseMe();
};

class Third: public Surpriser
{
public:
  void SurpriseMe();
};

#endif //SURPRISER_OL70
