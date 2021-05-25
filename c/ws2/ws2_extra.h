/*******************************************************************

Name: 		Roy Yablonka
Reviewer:	
Version:	Sent
Title:		WS2_EXTRA Header File
*******************************************************************/

#ifndef OL70_WS2_EXTRA
#define OL70_WS2_EXTRA

/* checks if String str is palindrome */
int IsPalindrome(const char *str);

/* Function that assists SevenBoom function */
/* swaps between 2 ints by referance */
void swap(int *x, int *y);

/* Function that assists SevenBoom function */
/*checks if int num has 7 in one of it's digits */
int HasSevenAsDigit(int num);

/* receives two ints first & seconds and prints all numbers in between */
/* with the rule of printing BOOM instead of numbers that divide by 7  */
/* or have 7 in one of their digits */
void SevenBoom(int first, int second);

/* swaps between two pointers to int */
void SwapPointer(int **first, int **second);

/* adds two large numbers represented as Strings and returns the result as String */
char *Addition(char *num1, char* num2);

/* removes spaces from beginning and start of String and changes several spaces in between words to a single space char */
void RmSpaces(char *str);

#endif
