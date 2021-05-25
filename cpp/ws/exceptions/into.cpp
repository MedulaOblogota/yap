#include <iostream>
#include <cstdlib>
#include <typeinfo>

using namespace std;

class Try
{
public:
	Try()	: m_int(3) { std::cout << "Try Ctor" << std::endl; }
	~Try()	{ std::cout << "Try Dtor" << std::endl; }

private:
	int m_int;
};

struct BadDog: public runtime_error
{
   BadDog(const string& s_ = "this is a bad dog")
       : runtime_error(s_){}
};

void Fifi(){ throw bad_cast(); cerr << "Fifi() after throw" << endl;}
void Foo()
{
	Try tr;
	Fifi();
	cerr << "Foo() after Fifi()" << endl;
}
void Bar(){Foo(); cerr << "Bar() after Foo()" << endl;}

int main()
{
   try
   {
       Bar();
   }
   catch(BadDog& b)
   {
	   cerr << "Bad dog exception: " << b.what(); exit(3);
   }
   catch(bad_alloc)
   {
	   cerr <<"Out of memory! exiting."; exit(2);
   }
   // catch(bad_cast)
   // {
	//    cerr << "bad cast."; exit(5);
   // }

   // catch(exception& r)
   // {
   //     cerr << "unknown exception: " << r.what(); exit(4);
   // }
   return (0);
}
