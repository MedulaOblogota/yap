/*########
Structs 
#######*/
typedef struct test_report{
	char *report_title;		/*/ Name of report object - for display */
	int  codes[100]; 		/*/ Codes of errors (relevant for tests that need distinction between different error codes) */
	char *causers[100];		/*/ Causers of errors (usually - name of function that was tested and failed) */
	char *messages[100];		/*/ Messages of errors (message in messages[n] is relevant to code in codes[n] and is made by causers[n]) */
	char *used[100];
	int amount;			/*/ Amount of errors reported into this report */
	int is_clear;			/*/ Boolean - TRUE if amount==0, FALSE otherwise */
} REPORT ;

#define TESTFAIL  1			/*/ Error code for tests with 1 error type */
#define TESTERROR 2
REPORT * ReportStart(REPORT *rprt, char * title) ;
REPORT * ReportWrite(REPORT *rprt, int code, char *file, int line, const char * message, const char * causer, const char * used);
void ReportPrint(REPORT * rprt);
void ReportClose(REPORT * rprt);
