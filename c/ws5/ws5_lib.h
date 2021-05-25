/*******************************************************************

Name: 		Roy Yablonka
Reviewer:	Or Ben-Lulu
Title:		WS5_LIB Header File
*******************************************************************/

#ifndef OL70_WS4_LIB /*header gaurd*/
#define OL70_WS4_LIB

/* 	defined for implementing functions' return value */
typedef enum {no, yes} working;

/*	defined for array element */
struct element;

/* 	checks whether inputted string is equal to string in array slot */
int Check(const char *input_str, const char *check_str);

/* 	checks whether first char of inputted string is equal to string in array 
	slot*/
int PrependCheck(const char *input_str, const char *check_str);

/*	checks whether user inputted regular string */
int AlwaysTrueCheck(const char *input_str, const char *check_str);

/* implements removing the file listed under filename */
working RemoveImplement(const char *filename, const char *data);

/* implements counting and inserting amount of lines into log file */
working CountImplement(const char *filename, const char *data);

/* implements exiting the program */
working ExitImplement(const char *filename, const char *data);

/* implements inputting the string listed under data at beginning of file */
working PrependImplement(const char *filename, const char *data);

/* implements receiving default input from user in order to input it to file */
working AlwaysTrueImplement(const char *filename, const char *data);

#endif /* WS5_LIB */
