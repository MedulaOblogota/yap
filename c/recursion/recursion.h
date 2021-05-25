
#ifndef RECU_OL70 /*header guard*/
#define RECU_OL70
/**************************************************************
* The functions in this file handle a Calculator.
*
*
* Written by: OL-70
* Last update: 10:40 , 17.07.2019
***************************************************************/
#include <stddef.h>
#include "sllist.h"

size_t Fibunacci(size_t index);

size_t FibunacciR(size_t index);

size_t StrLenR(const char *str);

int StrCmpR(const char *s1, const char *s2);

char *StrCpyR(char *dest, const char *src);

char *StrCatR(char *dest, const char *src);

char *StrStrR(const char *haystack, const char *needle);

sll_node_t *SLLFlipR(sll_node_t *node);

#endif /*RECU_OL70*/
