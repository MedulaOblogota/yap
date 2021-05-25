#include <dlfcn.h>
#include <stdio.h>

#include "so1.h"

typedef void (*simple_func)();
/*simple_func * simple;*/

int main(int argc, char *argv[])
{
	void *handle;
	void (*simple)();
	handle = dlopen(argv[1], RTLD_LAZY);

	/*
	Foo();
	Bla();
	*/

	if (argc < 3)
	{
		printf("not enough parameters! exiting\n");
	}
	
	if (handle)
	{
		simple = dlsym(handle, argv[2]);
		if (simple)
		{
			printf("found function\n");
			(*simple)();
		}
		else
		{
			printf("couldnt find function\n");
		}
		dlclose(handle);
	}
	else
	{
		printf("error with oppening DLL\n");
	}
}
