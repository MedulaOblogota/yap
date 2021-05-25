#include <stdio.h>

#include "calc.h"

#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"

void Wrapper(char *str, double result, int err)
{
    int num = 0;
    double actual_result = Calculate(str, &num);

    if (actual_result == result)
    {
        printf(GRN"GREAT SUCCESS with result for %s!!!\n"RESET, str);
    }
    else
    {
        printf(RED"YOU... DISSAPOINT MEwith result for %s!\n"RESET, str);
    }
    printf("your result is %lf. correct result is %lf\n", actual_result, result);

    if (err == num)
    {
        printf(GRN"GREAT SUCCESS with error for %s!!!\n"RESET, str);
    }
    else
    {
        printf(RED"YOU... DISSAPOINT ME with error for %s!\n"RESET, str);
    }
    printf("your result is %d. correct result is %d\n", num, err);
}

int main()
{
    char str1[] = "+8 *(78*(-2)/(-6) +3 ^(2^1^5^3)+ (-3)* 1) - 3 ";
    double result1 = 253;
    int err1 = 0;

    char str2[] = "(7+8/(2^3^4^2 +7   * 3) + 4*{2-4} -8 * (-2) ) +3";
    double result2 = 18;
    int err2 = 0;

    char str3[] = "{[9+(2-4)^3]}";
    double result3 = 1;
    int err3 = 0;

    char str4[] = "(2+ a) / 6";
    double result4 = 0;
    int err4 = -2;

    char str5[] = "5+ (9-8)/0";
    double result5 = 0;
    int err5 = -4;

    char str6[] = "9+ (6/2 - 8))";
    double result6 = 0;
    int err6 = -2;  /*could be -3 also */

    char str7[] = "9+ ((6/2 - 8)";
    double result7 = 0;
    int err7 = -3;

    char str8[] = "6+ [8+ {2/5} + (3-3))";
    double result8 = 0;
    int err8 = -2;

    char str9[] = ")6+2";
    double result9 = 0;
    int err9 = -2;

    char str10[] = "90 @ 3 & 7";
    double result10 = 0;
    int err10 = -2;

    /*
    char str1[] = "-8 *(78/-2 +3 ^(2^1^5^3)+ 3*(1)) - 3";
    double result1 = 213;else
    {
        return (0);
    }
    int err1 = 0;


    int num = 0;

    printf("%f\n", Calculate(str, &num));
    printf("error is %d\n", num);*/
	printf("1.\n");
    Wrapper(str1, result1, err1);
	printf("2.\n");
    Wrapper(str2, result2, err2);
	printf("3.\n");
    Wrapper(str3, result3, err3);
	printf("4.\n");
    Wrapper(str4, result4, err4);
	printf("5.\n");
    Wrapper(str5, result5, err5);
	printf("6.\n");
    Wrapper(str6, result6, err6);
	printf("7.\n");
    Wrapper(str7, result7, err7);
	printf("8.\n");
    Wrapper(str8, result8, err8);
	printf("9.\n");
    Wrapper(str9, result9, err9);
	printf("10.\n");
    Wrapper(str10, result10, err10);

    return (0);
}
