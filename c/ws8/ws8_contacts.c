#define VARSIZE(var) ((char *)(&var + 1) - (char *)(&var))
#define TYPESIZE(type) ((size_t)(1 + (type *)NULL))

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct DateOfBirth
{
	size_t day;
	size_t month;
	size_t year;
};

typedef struct Contact 
{
	char f_name[50];
	char l_name[50];
	struct DateOfBirth dob;
	size_t ID;
} contact_t;

/* function for QA */
static void PrintContact(contact_t contact)
{
	printf("%s %s. id %lu. dob: %lu/%lu/%lu\n", contact.f_name, contact.l_name, 
	contact.ID, contact.dob.day, contact.dob.month, contact.dob.year);	
}

int main()
{
	FILE *file = fopen("contacts.bin", "wb+");
	int i = 0;
	contact_t contacts[] = 
	{ 
		{"Alex", "Milligan", {4, 7, 1991}, 310203542},
		{"Adi", "Algrabli", {17, 10, 1988}, 301734596},
		{"Hadar", "Rosenman", {30, 9, 1981}, 43122191},
		{"Or", "Ben Lulu", {11, 9, 1997}, 208852152},
		{"Nir", "Shidlansik", {20, 10, 1987}, 200141505},
		{"Eliav", "Tubul", {30, 1, 1989}, 303155923},
		{"Shlomo", "Solomont", {12, 2, 1989}, 310984141},
		{"Shlomi", "Daniel", {13, 5, 1998}, 207354408},
		{"Adam", "Blau", {12, 9, 1984}, 39434352},
		{"Shachar", "Saar", {11, 5, 1991}, 203952932}
	};
	
	contact_t contacts_copy[10];

	if (NULL == file)
	{
		printf("oops! something went wrong!\n");
	}

	fwrite(contacts, sizeof(contacts[0]), 10, file); 
	fseek(file, 0, SEEK_SET);
	fread(contacts_copy, sizeof(contacts[0]), 10, file);
	
	/* loop for QA */
	for (i = 0; i < 10; ++i)
	{
		PrintContact(contacts_copy[i]);
	}
	
	fclose(file);

	return (0); 
}
