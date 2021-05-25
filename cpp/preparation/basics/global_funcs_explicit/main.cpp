#include <dlfcn.h>
#include <stdio.h>
#include <iostream>


int main()
{
	void *handle;
	void (*void_arg)();
	void (*int_arg)(int);
	void (*char_arg)(char);
	handle = dlopen("./libso.so", RTLD_LAZY);

	if (handle)
	{
		void_arg = reinterpret_cast<void(*)()>(dlsym(handle, "_Z3Foov"));
		if (void_arg)
		{
			std::cout << "found function" << std::endl;
			(*void_arg)();
		}
		else
		{
			std::cout << "couldnt find function" << std::endl;
		}
		dlclose(handle);
	}
	else
	{
		std::cout << "error" << std::endl;
	}


	return 0;
}
