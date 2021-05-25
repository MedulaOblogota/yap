#include <dlfcn.h>
#include <stdio.h>

#include "a.h"
#include "so.h"

typedef void (*simple_func)();
/*simple_func * simple;*/

int main()
{
	void *handle;
	void (*simple)();
	handle = dlopen("./libso2.so", RTLD_LAZY);

	Foo();
	Bar1();

	if (handle)
	{
		simple = dlsym(handle, "Bar2");
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
