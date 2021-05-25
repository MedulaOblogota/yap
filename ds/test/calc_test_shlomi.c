#include <stdio.h>

#include "calc.h"

int main()
{
    int err = 0;
    double num = Calculate("2+3-9*2+1",&err);
    printf("-12 = %f & 0 = %d\n", num, err);
    num = Calculate("(((-2+3-(9*2))))",&err);
    printf("-17 = %f & 0 = %d\n", num, err);
    num = Calculate("1+(3-1)*2+5*4*(1-1)+((3-1)*2/3)",&err);
    printf("6.333 = %f & 0 = %d\n", num, err);
    num = Calculate("({3-1}*2/3)",&err);
    printf("1.333 = %f & 0 = %d\n", num, err);
    num = Calculate("1 *   (4 + 5)*3 +1*2+4/5*4",&err);
    printf("32.2 = %f & 0 = %d\n", num, err);
    num = Calculate("2^3^2^1",&err);
    printf("512 = %f & 0 = %d\n", num, err);
    num = Calculate("+1* 3 ^ 2 + 12  ^ 5- 3^1",&err);
    printf("248838 = %f & 0 = %d\n", num, err);
    num = Calculate("1*3^(0-2)+12^5-3^1",&err);
    printf("248829.111111 = %f & 0 = %d\n", num, err);

    Calculate("(@ [3-1]*2/3)",&err);
    printf("INPUT_ERR -2 = %d\n", err);

    Calculate("((3-1]*2/3)",&err);
    printf("BRAC_ERR -3 = %d\n", err);

    Calculate("([3-1]*2/0)",&err);
    printf("ARITHMETIC_ERR -4 = %d\n", err);

    return (0);
}
