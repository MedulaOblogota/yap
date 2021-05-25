#include <iostream>

class Base
{
public:
	Base(int x_):
	 	initial(x_)
	{}
	// virtual void SetPosition() = 0;
protected:
	int getInitial() { return initial; }
private:
	int initial;
};

class Derived: public Base
{
public:
	Derived(int x_ = 0, int y_ = 0):
		x(x_), y(y_), Base(x_)
	{}
	void SetPosition(int x_, int y_)
	{
		x = x_;
		y = y_;
	}

	void Print()
	{
		std::cout << "x = " << x << ". y = " << y << "initial = " << Base::getInitial() << std::endl;
	}

private:
	int x;
	int y;
};

int main()
{
	Derived derived(3,4);

	derived.SetPosition(5,5);

	derived.Print();
}
