/*******************************************************************

Name: 		Roy Yablonka
Reviewer:	
Version:	Sent
Title:		WS2_STRING Header File
*******************************************************************/

#ifndef OL70_WS2_STRING
#define OL70_WS2_STRING

#include <stddef.h> /* size_t */

/* returns size of String */
size_t StrLen(const char *str);

/* copies n chars from src to dest string */
char *StrNCpy(char *dest, const char *src, size_t n);

/* copies source string to dest */
char *StrCpy(char *dest, const char *source);

/* compares first string to second (case sensitive) and returns the ASCII difference of first char-difference if exists */
int StrCmp(const char *first, const char *second);

/* compares s1 string to s2 (case insensitive) and returns the ASCII difference of first char-difference if exists as int */
int StrCaseCmp(const char *s1, const char *s2);

/* returns pointer to first occurance of char c in String str */
char *StrChr(const char *str, int c);

/* returns a duplication of src Sring */ 
/* NOT WORKING */
char *StrDup(const char *src);

/* concatonates src String to end of dest String 
returns pointer to new dest String */
char *StrCat(char *dest, const char *src);

/* concatonates first N chars of src String to dest String */
 char *StrNCat(char *dest, const char *src, size_t n); 

/* locates and returns substring needle in haystack String */
char *StrStr(const char *haystack, const char *needle);

/* returns length of substring in str1 built out of chars in String str2 */
size_t StrSpn(const char *str1, const char *str2);

/* returns tokens of Str str defined by string delim */
char *StrTok(char *str, const char *delim);

#endif



