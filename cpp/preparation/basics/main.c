#include <dlfcn.h>
#include <stdio.h>

#include "so1.hpp"

int main()
{
	void *handle;
	void (*void_arg)();
	void (*int_arg)(int);
	void (*char_arg)(char);
	handle = dlopen("./libso.so", RTLD_LAZY);

	if (handle)
	{
		void_arg = dlsym(handle, "Foo");
		if (void_arg)
		{
			printf("found function\n");
			(*void_arg)();
		}
		else
		{
			printf("couldnt find function");
		}
		dlclose(handle);
	}
	else
	{
		printf("error with opening DLL\n");
	}


	return 0;
}
