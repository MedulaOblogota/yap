/*******************************************************************

Name: 		Roy Yablonka
Reviewer:	Shlomi Daniel
Title:		WS6_BIT Header File
*******************************************************************/

#ifndef OL70_WS6_BIT /*header gaurd*/
#define OL70_WS6_BIT

/* returns x*(2^y) without arithmetic operations */
long Pow2(unsigned int x, int y);

/* Returns 1 if num is Power of Two, 0 otherwise. Uses Loop */
int IsPowOf2Loop(unsigned int num);

/* Returns 1 if num is Power of Two, 0 otherwise */
int IsPowOf2(unsigned int num);

/* Adds 1 to num without arithmetic operations */
unsigned int Add1(unsigned int num);

/* receives array of unsigned ints and prints only those with 3 bits */
void ThreeBitsOn(unsigned int arr[], size_t size);

/* returns a mirrored bit unsigned char in relation to src */
unsigned char ByteMirrorLoop(unsigned char src);

/* returns a mirrored bit unsigned char in relation to src using LUT */
unsigned char ByteMirror(unsigned char src);

/* returns 1 if bits indexed 2 and 6 are set, 0 otherwise */
int Is2And6(unsigned char num);

/* returns 1 if bits indexed 2 or 6 are set, 0 otherwise */
int Is2Or6(unsigned char num);

/* swaps bits 3 & 5 in num */
unsigned char Swap3And5(unsigned char num);

/* returns lowest number that is divisable by 16 in relation to num */
unsigned int DivisableBy16(unsigned int num);

/* swaps two unsigned ints without using a temp var */
void Swap(unsigned int *a, unsigned int *b);

/* counts amount of set bits present in num using Loop*/
size_t CountBitsLoop(int num);

/* counts amount of set bits present in num using Hamming Weight*/
size_t CountBits(int num);

/* prints bits of float datatype */
void FloatToBits(float num);

#endif /* WS6_BIT */
