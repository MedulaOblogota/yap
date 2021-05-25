/********************************************************************/
/*																	*/
/*	Name: 		Roy Yablonka										*/
/*	Reviewer:	Eliav 												*/
/*	Version:	Sent												*/
/* 	Title:		WS2_STRING Test File 								*/
/*																	*/
/********************************************************************/

#include <stdio.h>
#include <string.h>	/* to check against my functions */
#include <strings.h>
#include <stdlib.h>	
#include "ws2_string.h"

/********************************************************************/
/*	 																*/
/*				Function Declarations								*/
/* 																	*/
/********************************************************************/
void TestStrLen();
void TestStrCmp();
void TestStrCpy();
void TestStrNCpy();
void TestStrCaseCmp(); 
void TestStrChr();
void TestStrDup();
void TestStrCat();
void TestStrNCat();
void TestStrStr();
void TestStrSpn();
void TestStrTok();

/********************************************************************/
/*	 																*/
/*				Main Function										*/
/* 																	*/
/********************************************************************/

int main() 
{
	TestStrLen();
	TestStrCmp();
	TestStrCpy();
	TestStrNCpy();
	TestStrCaseCmp(); 
	TestStrChr();
	TestStrDup(); 
	TestStrCat();
	TestStrNCat();
	TestStrStr();
	TestStrSpn(); 
	TestStrTok(); 
	return(1);
}

/********************************************************************/
/*	 																*/
/*				Function Definitions								*/
/* 																	*/
/********************************************************************/

void TestStrLen()
{
	char str1[] = "HelloWorld";
	char str2[] = "a";
	char str3[] = "";
	
	printf("StrLen -> ");
	
	if (strlen(str1) != StrLen(str1))
		printf("1. %s DOESNT WORK\n", str1);
	if (strlen(str2) != StrLen(str2))
                printf("2. %s DOESNT WORK\n", str2);
	if (strlen(str3) != StrLen(str3))
                printf("3. %s DOESNT WORK\n", str3);
                
	printf("\n");
}
void TestStrCmp()
{
	char str1[] = "Hello";
	char str2[] = "man";
	char str3[] = "MaN";
	char str4[] = "";
	char str5[] = "Hellooo";
	
	printf("StrCmp -> ");
	
	if (StrCmp(str1,str2) != strcmp(str1,str2))
		printf("1. %s with %s DOESNT WORK\n", str1, str2); 
	if (StrCmp(str1,str3) != strcmp(str1,str3))
        printf("2. %s with %s DOESNT WORK\n", str1, str3); 
	if (StrCmp(str1,str4) != strcmp(str1,str4))
        printf("3. %s with %s DOESNT WORK\n", str1, str4); 
	if (StrCmp(str1,str5) != strcmp(str1,str5))
        printf("4. %s with %s DOESNT WORK\n", str1, str5); 
	if (StrCmp(str3,str2) != strcmp(str3,str2))
        printf("5. %s with %s DOESNT WORK\n", str3, str2); 
	if (StrCmp(str4,str5) != strcmp(str4,str5))
        printf("6. %s with %s DOESNT WORK\n", str4, str5); 
	if (StrCmp(str4,str3) != strcmp(str4,str3))
        printf("7. %s with %s DOESNT WORK\n", str4, str3); 
                
	printf("\n");
}

void TestStrCpy() 
{
	char str1[] = "HelloWorld";
	char str2[] = "";
	char str3[20];
	
	printf("StrCpy -> ");
	
	if (0 != StrCmp(StrCpy(str3, str1), strcpy(str3, str1)))
		printf("1. %s DOESNT WORK\n", str3);
	if (0 != StrCmp(StrCpy(str3, str2), strcpy(str3, str2)))
        printf("2. %s DOESNT WORK\n", str2);
        
	printf("\n");
}

void TestStrNCpy()
{
	
	char str1[] = "HelloWorld";
    char str2[] = "";
    char str3[20]; 
    
    printf("StrNCpy -> ");
    
    if (0 != StrCmp(StrNCpy(str3, str1, 0), strncpy(str3, str1, 0)))
		printf("1. %s and %s and 0 DOESNT WORK\n", str3, str1);
	if (0 != StrCmp(StrNCpy(str3, str2, 0), strncpy(str3, str2, 0)))
        printf("2. %s and %s and 0 DOESNT WORK\n", str3, str2);
	if (0 != StrCmp(StrNCpy(str3, str2, 4), strncpy(str3, str2, 4)))
		printf("3. %s and %s and 4 DOESNT WORK\n", str3, str2);
	if (0 != StrCmp(StrNCpy(str3, str1, 12), strncpy(str3, str1, 12)))
        printf("4. %s and %s and 12 DOESNT WORK\n", str3, str1);
            
    printf("\n"); 
}

void TestStrCaseCmp()
{
	char str1[] = "hEllO";
	char str2[] = "helLo";
	char str3[] = "";
	char str4[] = "hello Buddy";
	
	printf("StrCaseCmp -> ");
	
	
	if (StrCaseCmp(str1, str2) != strcasecmp(str1,str2))
		printf("1. %s and %s DOESNT WORK\n", str1, str2);
	if (StrCaseCmp(str1, str3) != strcasecmp(str1,str3))
		printf("2. %s and %s DOESNT WORK\n", str1, str3);
	if (StrCaseCmp(str1, str4) != strcasecmp(str1,str4))
		printf("3. %s and %s DOESNT WORK\n", str1, str4);
	if (StrCaseCmp(str4, str2) != strcasecmp(str4,str2))
		printf("4. %s and %s DOESNT WORK\n", str4, str2);
		
	printf("\n");
}

void TestStrChr()
{
	char str1[] = "hello";
	char str2[] = "";
	char c1 = 'e';
	char c2 = 'd';
	
	printf("StrChr -> ");

	if ((StrChr(str1, c1) != NULL) && (strchr(str1, c1) != NULL))
		if  (0 != StrCmp(StrChr(str1, c1), strchr(str1, c1)))
			printf("1. %s and %c DOESNT WORK\n", str1, c1);
	if ((StrChr(str1, c2) != NULL) && (strchr(str1, c2) != NULL))
		if  (0 != StrCmp(StrChr(str1, c2), strchr(str1, c2)))
			printf("2. %s and %c DOESNT WORK\n", str1, c2);
	if ((StrChr(str2, c1) != NULL) && (strchr(str2, c1) != NULL))
		if  (0 != StrCmp(StrChr(str2, c1), strchr(str2, c1)))
			printf("3. %s and %c DOESNT WORK\n", str2, c1); 
		
	printf("\n");
	
}


void TestStrDup()
{
	char str1[] = "hello";
	char str2[] = "";
	char str3[] = "a";
	
	printf("StrDup -> ");
	
	if (0 != StrCmp(StrDup(str1), strdup(str1)))
		printf("1. %s DOESNT WORK\n", str1);
	if (0 != StrCmp(StrDup(str2), strdup(str2)))
		printf("2. %s DOESNT WORK\n", str2);
	if (0 != StrCmp(StrDup(str3), strdup(str3)))
		printf("3. %s DOESNT WORK\n", str3);
		
	printf("\n");
} 


void TestStrCat()
{
	char str1[]="hello";
	char str2[]="man";
	char str3[] = "man";
	char str4[]="";
	char str5[] = "";
	char str6[] = "";
	
	printf("StrCat -> ");
	
	if (0 != StrCmp(StrCat(str2, str1), strcat(str2, str1)))
		printf("1. %s and %s DOESNT WORK\n", str2, str1);
	if (0 != StrCmp(StrCat(str3, str4), strcat(str3, str4)))
		printf("2. %s and %s DOESNT WORK\n", str3, str4);
	if (0 != StrCmp(StrCat(str5, str6), strcat(str5, str6)))
		printf("3. %s and %s DOESNT WORK\n", str5, str6);

	printf("\n");
}

void TestStrNCat()
{
	char str1[]="hello";
	char str2[]="man";
	char str3[] = "man";
	char str4[]="";
	char str5[] = "";
	char str6[] = "";
	
	printf("StrNCat -> ");
	
	if (0 != StrCmp(StrNCat(str2, str1,3), strncat(str2, str1,3)))
		printf("1. %s and %s and 3 DOESNT WORK\n", str2, str1);
	if (0 != StrCmp(StrNCat(str3, str4,2), strncat(str3, str4,2)))
		printf("2. %s and %s and 2 DOESNT WORK\n", str3, str4);
	if (0 != StrCmp(StrNCat(str5, str6,7), strncat(str5, str6,7)))
		printf("3. %s and %s and 7 DOESNT WORK\n", str5, str6);
		
	printf("\n");
}

void TestStrStr() 
{
	char str1[] = "hello man man";
	char str2[] = "mann";
	char str3[] = "man";
	char str4[] = "hi my friend";
	char str5[] = "my";
	char str6[] = "Something";
	char str7[] = "";
	char str8[] = "y";
	
	
	printf("StrStr -> ");
	
	/*printf("StrStr for %s and %s is %s\n", str1, str2, StrStr(str1, str2));
	printf("strstr for %s and %s is %s\n", str1, str2, strstr(str1, str2));*/
	/*printf("StrStr(%s, %s) = %s\n", str6, str7, StrStr(str6, str7));*/
	if ((NULL != StrStr(str1, str2)) && (NULL != strstr(str1, str2)))
		if (0 != StrCmp(StrStr(str1, str2), strstr(str1, str2)))
			printf("1. %s and %s DOESNT WORK\n", str1, str2);
	if ((NULL != StrStr(str1, str3)) && (NULL != strstr(str1, str3)))
		if (0 != StrCmp(StrStr(str1, str3), strstr(str1, str3)))
			printf("2. %s and %s DOESNT WORK\n", str1, str2);
	if ((NULL != StrStr(str4, str5)) && (NULL != strstr(str4, str5)))
		if (0 != StrCmp(StrStr(str4, str5), strstr(str4, str5)))
			printf("3. %s and %s DOESNT WORK\n", str4, str5);
	if ((NULL != StrStr(str2, str3)) && (NULL != strstr(str2, str3)))
		if (0 != StrCmp(StrStr(str2, str3), strstr(str2, str3)))
			printf("4. %s and %s DOESNT WORK\n", str2, str3);
	if ((NULL != StrStr(str6, str7)) && (NULL != strstr(str6, str7)))
		if (0 != StrCmp(StrStr(str6, str7), strstr(str6, str7)))
			printf("5. %s and %s DOESNT WORK\n", str6, str7);
	if ((NULL != StrStr(str6, str8)) && (NULL != strstr(str6, str8)))
		if (StrStr(str6, str8) != strstr(str6, str8))
			printf("6. %s and %s DOESNT WORK\n", str6, str8);
		
	printf("\n");
}

void TestStrSpn() 
{
	char str1[] = "my man wassup?";
	char str2[] = "m yn";
	char str3[] = "";
	char str4[] = "this is my site";
	char str5[] = " ts.ith";
	char str6[] = "a.";
	char str7[] = "";
	printf("StrSpn -> ");

	if (StrSpn(str1, str2) != strspn(str1, str2))
		printf("1. %s and %s DOESNT WORK\n", str1, str2);
	if (StrSpn(str1, str3) != strspn(str1, str3))
		printf("2. %s and %s DOESNT WORK\n", str1, str3);
	if (StrSpn(str2, str3) != strspn(str2, str3))
		printf("3. %s and %s DOESNT WORK\n", str2, str3);
	if (StrSpn(str4, str5) != strspn(str4, str5))
		printf("4. %s and %s DOESNT WORK\n", str4, str5);
	if (StrSpn(str3, str6) != strspn(str3, str6))
		printf("5. %s and %s DOESNT WORK\n", str3, str6);
	if (StrSpn(str3, str7) != strspn(str3, str7))
		printf("6. %s and %s DOESNT WORK\n", str3, str7);
		
	printf("\n");
}

void TestStrTok()
{
	char Str1[] = "this. i.s - y.net - .website";
	char Str2[] = "$-^.";
	
	char str1[] = "this. i.s - y.net - .website";
	char str2[] = "$-^.";
	
	char Str4[] = "Hello. my - fri.end-";
	char Str5[] = ".l-";
	
	char str4[] = "Hello. my - fri.end-";
	char str5[] = ".l-";
	
	char Str7[] = "one-two-three";
	char Str8[] = "-";
	
	char str7[] = "one-two-three";
	char str8[] = "-";
	
	char *Str3 = StrTok(Str1, Str2);
	char *str3 = strtok(str1, str2);
	
	char *Str6 = StrTok(Str4, Str5);
	char *str6 = strtok(str4, str5);
	
	char *Str9 = StrTok(Str7, Str8);
	char *str9 = strtok(str7, str8);
	
	printf("StrTok -> ");
	
	printf("%s\n", StrTok(Str1, Str2));
	printf("%s\n", StrTok(NULL, Str2));
	printf("%s\n", StrTok(NULL, Str2));
	
	while (Str9 != NULL)
	{
		Str9 = StrTok(NULL, Str8);
		str9 = strtok(NULL, str8);
		
		if ((Str9 != NULL) && (str9 != NULL))
			if (strcmp(Str9, str9) != 0)
				printf("DIDNT WORK");
	}
	
	while (Str3 != NULL)
	{
		Str3 = StrTok(NULL, Str2);
		str3 = strtok(NULL, str2);
		
		if ((Str3 != NULL) && (str3 != NULL))
			if (strcmp(Str3, str3) != 0)
				printf("DIDNT WORK");
	}
	
	while (Str6 != NULL)
	{
		Str6 = StrTok(NULL, Str5);
		str6 = strtok(NULL, str5);
		
		if ((Str6 != NULL) && (str6 != NULL))
			if (strcmp(Str5, str5) != 0)
				printf("DIDNT WORK");
	}
	
	/*
	if (StrCmp(Str9, str9) != 0)
		printf("DIDNT WORK");
	
	Str9 = StrTok(NULL, Str8);
	str9 = strtok(NULL, str8);
	
	if (StrCmp(Str9, str9) != 0)
		printf("DIDNT WORK");
		
	Str9 = StrTok(NULL, Str8);
	str9 = strtok(NULL, str8);
		
	if (StrCmp(Str9, str9) != 0)
		printf("DIDNT WORK");
		
	Str9 = StrTok(NULL, Str8);
	str9 = strtok(NULL, str8);
		
	if (strcmp(Str9, str9) != 0)
		printf("DIDNT WORK");
		*/
		
		
		
		
		
		
	/*Str9 = StrTok(NULL, Str8);
	str9 = strtok(NULL, str8);
	
	if (StrCmp(Str9, str9) != 0)
		printf("DIDNT WORK"); */		
		
		
	/*int counter = 1;
	int counter2 = 1;
	int counter3 = 1;
	
	printf("StrTok -> \n");
	
	if (StrCmp(Str3, str3) != 0) 
	{
		printf("%d. DIDNT WORK\n", counter);
		++counter;
	}
	
	if (StrCmp(Str6, str6) != 0) 
	{
		printf("%d. DIDNT WORK\n", counter2);
		++counter2;
	}
	
	if (StrCmp(Str9, str9) != 0) 
	{
		printf("%d. DIDNT WORK\n", counter3);
		++counter3;
	}
	
	while ((str3 != NULL) && (Str3 != NULL))
	{
		Str3 = StrTok(NULL, Str2);
		str3 = strtok(NULL, str2);
		
		Str6 = StrTok(NULL, Str5);
		str6 = strtok(NULL, str5);
		
		Str9 = StrTok(NULL, Str8);
		str9 = strtok(NULL, str8);
		
		if ((Str3 != NULL) && (str3 != NULL))
			if ((StrCmp(Str3, str3) != 0)) 
			{
				printf("%d. DIDNT WORK\n", counter);
				++counter;
			}
			
		if ((Str6 != NULL) && (str6 != NULL))
			if ((StrCmp(Str6, str6) != 0)) 
			{
				printf("%d. DIDNT WORK\n", counter2);
				++counter2;
			}
		if ((Str9 != NULL) && (str9 != NULL))
			if ((StrCmp(Str9, str9) != 0)) 
			{
				printf("%d. DIDNT WORK\n", counter2);
				++counter2;
			}
	}*/
		
	
} 






















