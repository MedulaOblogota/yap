#include <stdio.h>
#include <stdlib.h>

void Foo(int *ap, int *bp)
{
	int a;
	int b;
	a = ++*ap;
	b = ++*bp;
	printf("in function: a=%d. b=%d.\n", a, b);
}
int main() 
{	
	/* SECTION 2 */
	
	/*
	long c = 0;
	printf("c + 5 = %li\n", c + 5);
	printf("after this, c = %li\n", c);
	printf("(short *)c + 5 = %hi\n", (short *)c + 5);
	printf("after this, c = %li\n", c);
	printf("++*(long **)&c = %li\n", ++*(long **)&c);
	printf("after this, c = %li\n", c);
	printf("after all this, c = %li\n", c); */
	
	/* SECTION 3 */
	
	/*
	int i=1;
	float f=2.0;
	printf("i - f = %f\n", i - f);
	printf("after this i=%d. f=%f\n", i, f);
	printf("(float)i + f = %f\n", (float)i + f);
	printf("after this i=%d. f=%f\n", i, f);
	printf("*(float *)&i + f = %f\n", *(float *)&i + f);
	printf("after all this i=%d. f=%f\n", i, f);
	*/
	
	/* SECTION 4 */
	double d = 5;
	float f = 8/6;
	int i = 12;
	unsigned int ui = 2;
	printf("f=%f", f);
	i = d / f + i*(ui - i)+((float *)&d - &f);
	printf("i=%d\n", i);
	
	return (1);
}
