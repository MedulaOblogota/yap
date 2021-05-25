#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#include "recursion.h"
#include "tests.h"
#include "sllist.h"

#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"


void TestStrLenR();
void TestStrCmpR();
void TestStrCpyR();
void TestStrCatR();
void TestStrStrR();
void TestSLLFlipR();

int main()
{
    clock_t beginning = clock();

    beginning = clock();
    printf("iterative Fibunacci(10): %lu\n", Fibunacci(10));
    printf("time difference for iterative Fibunacci is %f\n", (double)(clock() - beginning)/CLOCKS_PER_SEC);

    beginning = clock();
    printf("recursive Fibunacci(10): %lu\n", FibunacciR(10));
    printf("time difference for recursive Fibunacci is %f\n", (double)(clock() - beginning)/CLOCKS_PER_SEC);

/*
    beginning = clock();
    WrapperCompareSizet("StrLenR", StrLenR(str), strlen(str));
    printf("time difference for StrLenR is %f\n", (double)(clock() - beginning)/CLOCKS_PER_SEC);

    beginning = clock();
    WrapperCompareInt("StrCmpR", StrCmpR(str1, str2), strcmp(str1, str2));
    printf("time difference for StrCmpR is %f\n", (double)(clock() - beginning)/CLOCKS_PER_SEC);

    beginning = clock();
    WrapperCompareStringsWithStrLen("StrCpyR", StrCpyR(str3r, str1), strcpy(str3, str1));
    printf("time difference for StrCmpR is %f\n", (double)(clock() - beginning)/CLOCKS_PER_SEC);

    WrapperCompareStringsWithStrLen("StrCpyR", StrCpyR(str4r, str1), strcpy(str4, str1));
    WrapperCompareStringsWithStrLen("StrCpyR", StrCpyR(str5r, str1), strcpy(str5, str1));
*/

    /*StrCatR(destr, srcr);*/
/*    WrapperCompareStringsWithStrLen("StrCatR", StrCatR(destr, srcr), strcat(dest, src));
    printf("time difference for StrCatR is %f\n", (double)(clock() - beginning)/CLOCKS_PER_SEC);
*/
	TestStrLenR();
	TestStrCmpR();
	TestStrCpyR();
	TestStrCatR();
	TestStrStrR();
    TestSLLFlipR();

    return (0);

}

static sll_node_t *CreateList(size_t amount_of_items)
{
    size_t value = 1;
    sll_node_t *head = SLLCreateNode((void *)value, NULL);
    sll_node_t *node = head;
    sll_node_t *new_node = NULL;

    while (amount_of_items - 1 > 0)
    {
        ++value;
        new_node = SLLCreateNode((void *)value, NULL);
        node->next = new_node;
        node = new_node;
        --amount_of_items;
    }

    return (head);
}

static void PrintIntList(sll_node_t *node)
{
    while (NULL != node)
    {
        printf("current address: %lu\ncurrent data: %lu\nnext address: %lu\n\n", (size_t)node, (size_t)node->data, (size_t)node->next);
        node = node->next;
    }
}

void TestStrLenR()
{
	clock_t beginning = clock();
	char str1[10];
	char str2[10];
	char str3[15];
	size_t size = 0;

	strcpy(str1, "");
	strcpy(str2, "hello");
	strcpy(str3, "wassup my man?");

	beginning = clock();
	size = StrLenR(str1);
	printf("time difference for StrLenR is %f\n", (double)(clock() - beginning)/CLOCKS_PER_SEC);

	WrapperCompareSizet("StrLenR", size, strlen(str1));
	WrapperCompareSizet("StrLenR", StrLenR(str2), strlen(str2));
	WrapperCompareSizet("StrLenR", StrLenR(str3), strlen(str3));
}

void TestStrCmpR()
{
	char str1[] = "hello";
	char str2[] = "hello";

	char str3[] = "hell";
	char str4[] = "hello buddy";
	char str5[] = "wassup";
	clock_t beginning = clock();

	int comp = StrCmpR(str1, str2);

	printf("time difference for StrCmpR is %f\n", (double)(clock() - beginning)/CLOCKS_PER_SEC);

	WrapperCompareInt("StrCmpR", comp, strcmp(str1, str2));
	WrapperCompareInt("StrCmpR", StrCmpR(str1, str3), strcmp(str1, str3));
	WrapperCompareInt("StrCmpR", StrCmpR(str1, str4), strcmp(str1, str4));
	WrapperCompareInt("StrCmpR", StrCmpR(str1, str5), strcmp(str1, str5));
}

void TestStrCpyR()
{
	char str1[] = "hello";

    char str3[3];
    char str4[5];
    char str5[8];

    char str3r[3];
    char str4r[5];
    char str5r[8];
	clock_t beginning = clock();
	char *res = StrCpyR(str3r, str1);

	printf("time difference for StrCpyR is %f\n", (double)(clock() - beginning)/CLOCKS_PER_SEC);
    WrapperCompareStringsWithStrLen("StrCpyR", res, strcpy(str3, str1));


    WrapperCompareStringsWithStrLen("StrCpyR", StrCpyR(str4r, str1), strcpy(str4, str1));
    WrapperCompareStringsWithStrLen("StrCpyR", StrCpyR(str5r, str1), strcpy(str5, str1));

}

void TestStrCatR()
{
	char dest1r[9];
    char src1r[] = "man";
    char dest1[9];
    char src1[] = "man";

	char dest2r[9];
	char src2r[] = "";
	char dest2[9];
	char src2[] = "";

	char *res = NULL;

	clock_t beginning = clock();

	StrCpyR(dest1r, "hello");
	StrCpyR(dest1, "hello");

	StrCpyR(dest2r, "hello");
	StrCpyR(dest2, "hello");

	beginning = clock();
	res = StrCatR(dest1r, src1r);
	printf("time difference for StrCatR is %f\n", (double)(clock() - beginning)/CLOCKS_PER_SEC);

	strcat(dest1, src1);

	StrCatR(dest2r, src2r);
	strcat(dest2, src2);


	WrapperCompareStringsWithStrLen("StrCatR", res, dest1);
	WrapperCompareStringsWithStrLen("StrCatR", dest2r, dest2);

	StrCpyR(dest1r, "");
	StrCpyR(dest1, "");

	StrCatR(dest1r, src1r);
	strcat(dest1, src1);

	WrapperCompareStringsWithStrLen("StrCatR", dest1r, dest1);
	/*printf("length of destr is %lu\n", strlen(destr));*/

}

void TestStrStrR()
{
	char haystack1[] = "hello man manny";
	char needle1[] = "ello";

	char needle2[] = "man";
	char needle3[] = "manny";
	char needle4[] = "mannyy";

	char * res1r = NULL;
	char * res2r = StrStrR(haystack1, needle2);
	char * res3r = StrStrR(haystack1, needle3);
	char * res4r = StrStrR(haystack1, needle4);

	char * res1 = strstr(haystack1, needle1);
	char * res2 = strstr(haystack1, needle2);
	char * res3 = strstr(haystack1, needle3);
	char * res4 = strstr(haystack1, needle4);

	clock_t beginning = clock();
	res1r = StrStrR(haystack1, needle1);
	printf("time difference for StrStrR is %f\n", (double)(clock() - beginning)/CLOCKS_PER_SEC);

	WrapperCompareStringsWithStrLen("StrStrR", res1r, res1);
	WrapperCompareStringsWithStrLen("StrStrR", res2r, res2);
	WrapperCompareStringsWithStrLen("StrStrR", res3r, res3);
	WrapperCompareStringsWithStrLen("StrStrR", res4r, res4);

}

void TestSLLFlipR()
{
    sll_node_t *node = CreateList(5);

    printf("before: \n");
    PrintIntList(node);

    printf("after:\n");
    PrintIntList(SLLFlipR(node));

}
