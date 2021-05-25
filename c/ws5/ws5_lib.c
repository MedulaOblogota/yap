/*******************************************************************

Name: 		Roy Yablonka
Reviewer:	Or Ben-Lulu
Version:	Approved
Title:		WS5_LIB Functions File
*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "ws5_lib.h"

/*******************************************************************
						FUNCTION DEFINITIONS
*******************************************************************/
			
int Check(const char *input_str, const char *check_str);

int PrependCheck(const char *input_str, const char *check_str);

int AlwaysTrueCheck(const char *input_str, const char *check_str);

working RemoveImplement(const char *filename, const char *data);

working CountImplement(const char *filename, const char *data);

working ExitImplement(const char *filename, const char *data);

working PrependImplement(const char *filename, const char *data);

working AlwaysTrueImplement(const char *filename, const char *data);

/*******************************************************************
						CHECKING FUNCTIONS
*******************************************************************/

/* 	checks whether inputted string is equal to string in array slot */
int Check(const char *input_str, const char *check_str)
{
	assert (NULL != input_str);
	assert (NULL != check_str);
	
	if (0 == strcmp(input_str, check_str))
		return (1);
	else 
		return (0);
}

/* 	checks whether first char of inputted string is equal to string in array 
	slot*/
int PrependCheck(const char *input_str, const char *check_str)
{
	
	assert (NULL != input_str);
	assert (NULL != check_str);
	
	if (input_str[0] == *check_str)
	{
		return(1);
	}
	else
		return(0);
}

/*	empty function in case user inputted regular string (without a flag) */
int AlwaysTrueCheck(const char *input_str, const char *check_str)		
{
	(void)(input_str);
	(void)(check_str);
	return(1);
}

/*******************************************************************
						IMPLEMENTING FUNCTIONS
*******************************************************************/

/* implements removing the file listed under filename */
working RemoveImplement(const char *filename, const char *data)	
{
	int status = remove(filename);
	(void)(data);
	
	assert (NULL != filename);
	assert (NULL != data);
	
	if (status == 0)
	{
		return (yes);
	} 
	else
	{
		return (no);
	}
}

/* implements counting and inserting amount of lines into log file */
working CountImplement(const char *filename, const char *data)
{
	FILE *file = fopen(filename, "r+");
	char str[30] = {0};
	char ch = 'a';
	int line_counter = 0;
	
	(void)(data);
	
	if (NULL == file)
	{
		return no;
	}
	
	fseek(file, 0, SEEK_SET);

	while ((ch = fgetc(file)) != EOF)
	{
		if (ch == '\n')
		{
			++line_counter;
		}
	}
	
	sprintf(str, "*** there are %d lines above ***", line_counter);
	AlwaysTrueImplement(filename, str);

	fclose(file);

	return (yes);
	
}

/* implements exiting the program (empty function) */
working ExitImplement(const char *filename, const char *data)
{
	(void)(filename);
	(void)(data);
	
	return (yes);
}

/* implements inputting the string listed under data at beginning of file */
working PrependImplement(const char *filename, const char *data)
{
	FILE *log_file = fopen(filename, "r");
	FILE *temp_file = fopen("temp.txt", "w+");
	char ch;
	char *newdata = NULL;
	
	assert(NULL != data);
	
	if (NULL == log_file)
	{
		log_file = fopen(filename, "a");
	}
	
	if (temp_file == NULL)
	{
		return (no);
	}
	
	newdata = (char *)data + 1;		/* 	as newdata string must begin after < 											sign 	*/
	fseek(log_file, 0, SEEK_SET);
	fseek(temp_file, 0, SEEK_SET);
	
	while ((ch = fgetc(log_file)) != EOF)
	{
		fputc(ch, temp_file);
	}
	
	log_file = fopen(filename, "w");
	fseek(log_file, 0, SEEK_SET);
	AlwaysTrueImplement(filename, newdata);
	
	fseek(log_file, 0, SEEK_END);
	fseek(temp_file, 0, SEEK_SET);
	
	while ((ch = fgetc(temp_file)) != EOF)
	{
		fputc(ch, log_file);
	}
	
	fclose(log_file);
	fclose(temp_file);
	
	remove("temp.txt");
	
	return (yes);
}

/* implements receiving default input from user in order to input it to file */
working AlwaysTrueImplement(const char *filename, const char *data)
{
	FILE *file = fopen(filename, "a");
	
	assert (NULL != data);
	
	if (NULL == file)
	{
		return no;
	}
	
	fseek(file, 0, SEEK_END);
	
	fwrite(data, 1, strlen(data), file);
	fwrite("\n", 1, 1, file);
	
	fclose(file);
	
	return (yes);
}
