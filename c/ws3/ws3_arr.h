/*******************************************************************

Name: 		Roy Yablonka
Reviewer:	
Version:	
Title:		WS3_ARR Header File
*******************************************************************/

#ifndef OL70_WS3_ARR
#define OL70_WS3_ARR

/*	receives array of soldiers marked as 1. Each Soldiers will stab the soldier 	adjacent to him until one soldier survives. Functions returns index of the 		last soldier who survives. */  
size_t Soldiers(size_t length);

/*	returns size of envp variable */  
size_t SizeOfEnvp(char **envp);

/*	receives Linux enviromental parameters and returns their duplicate */
char **CreateEnvStruct(char **envp);

/* prints all datatypes in C and their size */
void PrintDataTypes();

#endif
