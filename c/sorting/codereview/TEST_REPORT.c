#include <stdlib.h> /* calloc*/
#include <stdio.h> /* printf */
#include <string.h> /* strcpy, strcmp*/
#include "TEST_REPORT.h"


#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

/*ReportStart()-
Initializes Report Struct object. 
Takes: Declared Report Struct object, title for report object
Returns: Pointer to passed Report Struct object. */
REPORT * ReportStart(REPORT *rprt, char * title) 
{
	int i = 0;
	
	for (; 100 > i; ++i)
	{
		rprt->codes[i] = 0;
		rprt->messages[i] = (char *) calloc (1000, sizeof(char));		
		rprt->causers[i]  = (char *) calloc (1000, sizeof(char));
		rprt->used[i]	  = (char *) calloc (1000, sizeof(char));
		if(NULL == rprt->messages[i] || NULL == rprt->causers[i] || NULL == rprt->used[i])
		{
			free(rprt);
			return NULL;
		}		
	}
	
	rprt->report_title = (char *) calloc (100, sizeof(char));
	if(NULL == rprt->report_title)
	{
		free(rprt);
		return NULL;
	}
	
	rprt->is_clear = 1;
	rprt->amount = 0;
	strcpy(rprt->report_title, title);
	
	return rprt;
}
	
/*ReportError()-
Writes new error-entry to Report Struct object. 
Takes: Declared Report Struct object, error code, error message, error source name
Returns: Pointer to passed Report Struct object.*/

REPORT * ReportWrite(REPORT *rprt, int code, char *file, int line, const char * message, const char * causer, const char * used)
{
	int index = rprt->amount;
	
	rprt->codes[index] = code;
	strcpy(rprt->messages[index], message);
	strcpy(rprt->used[index], used);
	sprintf(rprt->causers[index], "%s [%s : %d]",causer, file, line);
	rprt->amount += 1;
	
	return rprt;
}

/*ReportPrint()-
Display Report on screen.
Takes: Declared and Initialized Report Struct object
Returns: - */

void ReportPrint(REPORT * rprt)	
{
	size_t i = 0;
	size_t report_length = rprt->amount;		
	
	printf( "|>|>|>|>| ERROR REPORT: %s \n"
		"|>|>|>|>| TOTAL ERRORS: %d \n", rprt->report_title, rprt->amount);
	
	printf("===========================================================\n");
	for(; report_length > i; ++i)
	{
		printf(KCYN"|Error Code|"KRED" %d "KCYN"|From|"KRED" %s "KCYN"|Using|"KRED" %s\n"
		       KGRN"|Message|"KNRM" %s\n"
		       "*****\n",
		       rprt->codes[i], rprt->causers[i], rprt->used[i], rprt->messages[i]);
	}
	

}

/*ReportClose(REPORT *ptr)-
Free memory allocated to report strings
Takes: Declared and Initialized Report Struct object
Returns: - */
void ReportClose(REPORT * rprt)
{	
	int i = 0;
	free(rprt->report_title);
	
	for (; 100 > i; ++i)
	{
		free(rprt->messages[i]);
		free(rprt->causers[i]);	
		free(rprt->used[i]);
	}	
}



