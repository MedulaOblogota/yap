/*******************************************************************

Name: 		Roy Yablonka
Reviewer:	Shlomi
Version:	Fixed
Title:		WS4_FUNC Functions File
*******************************************************************/

#include <stdlib.h>	/* malloc, free */
#include <stdio.h>	/* printf */
#include <assert.h>	/* assert */
#include <string.h>	/* strlen */
#include <ctype.h> 	/* to_lower */
#include "ws4_func.h"

#define ESC 27

void APressed();

void TPressed();

void NullPressed();



static void (*ascii_lut[256])() =
{
	NullPressed, NullPressed, NullPressed, NullPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed,
	NullPressed, NullPressed, NullPressed, NullPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed,
	NullPressed, NullPressed, NullPressed, NullPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed,
	NullPressed, NullPressed, NullPressed, NullPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed,
	NullPressed, NullPressed, NullPressed, NullPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed,
	NullPressed, NullPressed, NullPressed, NullPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed,
	NullPressed, NullPressed, NullPressed, NullPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed,
	APressed,    NullPressed, NullPressed, NullPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed,
	NullPressed, NullPressed, NullPressed, NullPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed,
	NullPressed, NullPressed, NullPressed, TPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed,
	NullPressed, NullPressed, NullPressed, NullPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed,
	APressed,    NullPressed, NullPressed, NullPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed,
	NullPressed, NullPressed, NullPressed, NullPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed,
	NullPressed, NullPressed, NullPressed, TPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed,
	NullPressed, NullPressed, NullPressed, NullPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed,
	NullPressed, NullPressed, NullPressed, NullPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed,
	NullPressed, NullPressed, NullPressed, NullPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed,
	NullPressed, NullPressed, NullPressed, NullPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed,
	NullPressed, NullPressed, NullPressed, NullPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed,
	NullPressed, NullPressed, NullPressed, NullPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed,
	NullPressed, NullPressed, NullPressed, NullPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed,
	NullPressed, NullPressed, NullPressed, NullPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed,
	NullPressed, NullPressed, NullPressed, NullPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed,
	NullPressed, NullPressed, NullPressed, NullPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed,
	NullPressed, NullPressed, NullPressed, NullPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed,
	NullPressed, NullPressed, NullPressed, NullPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed,
	NullPressed, NullPressed, NullPressed, NullPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed,
	NullPressed, NullPressed, NullPressed, NullPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed,
	NullPressed, NullPressed, NullPressed, NullPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed,
	NullPressed, NullPressed, NullPressed, NullPressed, 
	NullPressed, NullPressed, NullPressed, NullPressed
	};
	
/**************************************************************************/
/* Uses IF to print according to user input */
void IfAAndTPrinter()
{
	char input = 'b';
	printf("Enter Char:\n");
	scanf("%c", &input);
	while (input != 27)
	{
		if (input == 'A' || input == 'a')
		{
			printf("A pressed\n");
		} 
		else if (input == 'T' || input == 't')
		{
			printf("T pressed\n");
		}
		printf("Enter Char:\n");
		scanf(" %c", &input);
	}
}

/**************************************************************************/
/* Uses SWITCH to print according to user input */
void SwitchAAndTPrinter()
{
	char input = 'b';
	while (input != 27)
	{
		printf("Enter Char:\n");
		scanf(" %c", &input);
		switch (input)
		{
			case 'T':
			
			case 't':
				printf("T pressed\n");
				break;
			
			case 'A':
			
			case 'a':
				printf("A pressed\n");
				break;
			
			default:
				break;
		}
	}
}

/**************************************************************************/

/* HELPER FUNCTION FOR LutAAndTPrinter */
/* prints "A Pressed" in case a or A is pressed. */
void APressed()
{
	printf("A Pressed\n");
}

/* HELPER FUNCTION FOR LutAAndTPrinter */
/* prints "T Pressed" in case t or T is pressed. */
void TPressed()
{
	printf("T Pressed\n");
}

/* HELPER FUNCTION FOR LutAAndTPrinter */
/* void function in case ESC is pressed. */
void NullPressed()
{
	
}
/* Uses LUT to print according to user input */
void LutAAndTPrinter()
{
	char input = 'b';
	
	printf("Enter Char:\n");
	scanf(" %c", &input);
	
	while (input != ESC)
	{
		(*ascii_lut[(int)input - 1])();
		
		printf("Enter Char:\n");
		scanf(" %c", &input);
	}		
	
}


