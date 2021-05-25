/********************************************************************/
/*																	*/
/*	Name: 		Roy Yablonka										*/
/*	Reviewer:	Shlomi												*/
/* 	Title:		WS4_FUNC Test File 									*/
/*																	*/
/********************************************************************/

#include <stdio.h>	/* printf */
#include <string.h>	/* to check against my functions */
#include <stdlib.h>	/* system */
#include "ws4_func.h"


/********************************************************************/
/*	 																*/
/*				Function Declarations								*/
/* 																	*/
/********************************************************************/

void TestIfAAndTPrinter();
void TestSwitchAAndTPrinter();
void TestLutAAndTPrinter();

/********************************************************************/
/*	 																*/
/*				Main Function										*/
/* 																	*/
/********************************************************************/

int main()
{
	system("stty -icanon -echo");
	TestIfAAndTPrinter();
	TestSwitchAAndTPrinter();
	TestLutAAndTPrinter();
	system("stty icanon echo");
	
	return (0);
}

/********************************************************************/
/*	 																*/
/*				Function Definitions								*/
/* 																	*/
/********************************************************************/

void TestIfAAndTPrinter()
{
	printf("IfAAndTPrinter -> \n");
	IfAAndTPrinter();
	printf("\n");
}

void TestSwitchAAndTPrinter()
{
	printf("SwitchAAndTPrinter -> \n");
	SwitchAAndTPrinter();
	printf("\n");
}

void TestLutAAndTPrinter()
{
	printf("LutAAndTPrinter -> \n");
	LutAAndTPrinter();
	printf("\n");
}

