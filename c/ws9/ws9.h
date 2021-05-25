/*******************************************************************

Name: 		Roy Yablonka
Reviewer:	Shahar Saar
Title:		WS9 Header File
*******************************************************************/

#ifndef OL70_WS9
#define OL70_WS9

#include <stddef.h>

/* receives String with it's base and returns a decimal int */
int Atoi(char *str, int base);

/* receives an int in value and returns it's string version according to a 
	specific base. Will treat negative only in case int is decimal */
char *Itoa( int value, char *str, int base );

/* prints letters that exist in str1 & str2 but don't exist in str3 */
char *PrintLettersIn2Not3(const char *str1, const char *str2, const char *str3, char *result);

/* checks whether system is Little or Big Endian */
int IsLittleEndian();

void *MemSet(void *str, int c, size_t n);

void *MemCpy(void *dest, const void *src, size_t n);

void *MemMove(void *dest, const void *src, size_t n);

#endif



