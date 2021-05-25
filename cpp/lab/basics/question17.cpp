#include <iostream>

#include "counter.hpp"
#include "question13.hpp"

int main()
{
	float *f = new float(12.6);
	delete(f);

	f = new float[15];
	delete[] f;

	Counter *c1 = new Counter;
	X *x1 = new X;
	Y *y1 = new Y;
	X *xp = new X[10];

	delete y1;
	delete c1;
	delete x1;
	free (xp);

	int *ptr = (int *)malloc(1000 * sizeof(int));
	delete(ptr);
	int *ptr2 = new int[1000];
	free(ptr2);

	return 0;
}
