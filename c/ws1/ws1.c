/*************************************************************************

name: 		Roy Yablonka
reviewer:
title: 		WS1
version:	sent

*************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "ws1.h"

/* accepts int and returns a flipped digits int */
int Flip(int num) 
{
	int newnum = 0;
	while (0 != num) {
		newnum = newnum * 10 + (num % 10);
		num = num / 10;
	}
	if (num >= 0)
		return (newnum);
	else return (-1*newnum); 
}

char *HelloWorld() 
{
	char hello[]= {0x22, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x57, 
			0x6f, 0x72, 0x6c, 0x64, 0x21, 0x22, 0x00 };
	return (hello);
}

float Power(int num) 
{
	float newnum = 1.0;
	int i = 0;
	if (num >= 0)
	{
		for (i = 0; i < num; i++) 
		{
			newnum = newnum * 10;
		}
		return (newnum);
	}
	else 
	{
		num = (-1) * num;
		for (i = 0; i < num; i++ )
		{
			newnum = newnum / 10.0;
		}
		return (newnum);
	{
}

void Swap(int *a, int *b) 
{
	int c=*a;
	*a=*b;
	*b=c;
}

