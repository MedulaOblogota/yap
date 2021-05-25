/********************************************************************/
/*																	*/
/*	Name: 		Roy Yablonka										*/
/*	Reviewer:	 													*/
/*	Version:														*/
/* 	Title:		WS3_ARR Test File 									*/
/*																	*/
/********************************************************************/

#include <stdio.h>
#include <string.h>	
#include <stdlib.h>	
#include <ctype.h>	/* tolow */
#include <assert.h>
#include "ws3_arr.h"

/********************************************************************/
/*	 																*/
/*				Function Declarations								*/
/* 																	*/
/********************************************************************/

void TestSoldiers();
void TestBuildStructure();
void TestPrintDataTypes();

/********************************************************************/
/*	 																*/
/*				Main Function										*/
/* 																	*/
/********************************************************************/

int main(int argc, char *argv[], char **envp) 
{
	(void)(argc);
	(void)(argv);
	TestSoldiers();
	TestBuildStructure(envp);
	TestPrintDataTypes();
	return(1);
}

/********************************************************************/
/*	 																*/
/*				Function Definitions								*/
/* 																	*/
/********************************************************************/

void TestSoldiers()
{
	int length = 9;
	int works = 1;
	
		
	printf("Soldiers -> ");
	
	if (Soldiers(length) != 2)
	{
		printf("DIDNT WORK FOR LENGTH=%d\n", length);
		works = 0;
	}
	
	length = 16;
	if (Soldiers(length) != 0)
	{
		printf("DIDNT WORK FOR LENGTH=%d\n", length);
		works = 0;
	}
	
	length = 1;
	if (Soldiers(length) != 0)
	{
		printf("DIDNT WORK FOR LENGTH=%d\n", length);
		works = 0;
	}
	
	length = 100;
	if (Soldiers(length) != 72)
	{
		printf("DIDNT WORK FOR LENGTH=%d\n", length);
		works = 0;
	}
	
	if (works == 1)
	{
		printf("All Works\n");
	}
	else 
	{
		printf("Something is wrong\n");
	}
}
/*
void TestBuildStructure(char **envp)
{
	size_t i;
	int works = 1;
	char **structure;
	char *base;
	
	structure = CreateEnvStruct(envp);
	
	printf("BuildStructure -> ");
	
	while (*structure)
	{
		base = *structure;
		for (i = 0; i < strlen(*structure); i++)
		{
			if (**structure != tolower(**envp)) 
			{
				printf("DIDNT WORK FOR %s", base);
				works = 0;
			}
		}
		++structure;
		++envp;	
	}
	
	if (works == 1)
		printf("All Works\n");
	else 
		printf("Something is wrong\n");
} */

void TestBuildStructure(char **envp)
{
	size_t i;
	int works = 1;
	char **structure;
	char **structure_runner;
	char **envp_runner;
	
	structure = CreateEnvStruct(envp);
	
	assert(NULL != structure);
	
	structure_runner = structure;
	envp_runner = envp;
	
	printf("BuildStructure -> ");
	
	while (*structure_runner)
	{
		if (0 != strcasecmp(*structure_runner, *envp_runner))
		{
			printf("DIDNT WORK FOR %s", *structure_runner);
		}
		++structure_runner;
		++envp_runner;	
	}
	
	structure_runner = structure;
	envp_runner = envp;
	
	while (*structure_runner)
	{
		free(*structure_runner);
		++structure_runner;
	}
	
	free(structure);
	/*structure_runner = structure;
	envp_runner = envp;*/
	
	
	
	if (works == 1)
		printf("All Works\n");
	else 
		printf("Something is wrong\n");
} 


void TestPrintDataTypes()
{
	PrintDataTypes();
}
