#include <unistd.h>
#include <dlfcn.h>

#include "loader.hpp"
#include "factory.hpp"
#include "singleton.hpp"
#include "logger.hpp"

typedef SharedPtr<Command> (*cmd_func_create_t)(serv_arg_t*);
typedef char (*cmd_func_key_t)();

// Factory<SharedPtr<Command>, char, serv_arg_t*>& Loader::m_command_factory;

void Loader::LoadFile(std::string filename)
{
		Logger *loadLogger = Singleton<Logger>::GetInstance();
    // void *handle_read = dlopen("/home/roy/git/roy-yablonka/projects/framework/libread.so", RTLD_LAZY);
    // void *handle_write = dlopen("/home/roy/git/roy-yablonka/projects/framework/libwrite.so", RTLD_LAZY);

    // std::cout << "filename - " << filename << std::endl;
    Factory<SharedPtr<Command>, char, serv_arg_t*> *command_factory = Singleton<Factory<SharedPtr<Command>, char, serv_arg_t*> >::GetInstance();

    // void *handle = dlopen(("/home/student/roy-yablonka/projects/bin/lib/" + filename).c_str(), RTLD_LAZY);

		void *handle = dlopen(("/home/roy/roy-yablonka/projects/bin/lib/" + filename).c_str(), RTLD_LAZY);

    // std::cout << std::endl << std::endl <<"this is the file!" <<std::endl << std::endl;

    if (handle == NULL)
    {
				loadLogger->Log(Logger::ERROR, "failed to open " + filename);
        printf("bad handle\n");
        perror("handle");
    }
    else
    {
			loadLogger->Log(Logger::DEBUG, "succesfully opened file " + filename);
        // printf("success with handles\n");
    }

    cmd_func_create_t creator = reinterpret_cast<cmd_func_create_t>(dlsym(handle, "Create"));

    if (NULL == creator)
    {
        printf("failed with creator func\n");
				loadLogger->Log(Logger::ERROR, "failed to open create function in " + filename);
    }
    else
    {
			loadLogger->Log(Logger::DEBUG, "opened create function in " + filename);
        // printf("success with creator func!\n");
    }

    cmd_func_key_t key_reader = reinterpret_cast<cmd_func_key_t>(dlsym(handle, "GetKey"));

    if ((NULL == key_reader))
    {
        printf("failed with key_reader func\n");
				loadLogger->Log(Logger::ERROR, "failed to open key-reading function in " + filename);
        exit(EXIT_FAILURE);
    }
    else
    {
			loadLogger->Log(Logger::ERROR, "successfuly opened key-reading function in " + filename);
        // printf("success with key_reader func!\n");
    }

    // SharedPtr<Command> ret_val = creator(&sa);
    char ret_key = key_reader();

    // Loader::m_command_factory;

    command_factory->add(ret_key, creator);
		loadLogger->Log(Logger::DEBUG, "added create function to factory");

    // command_factory.add(1, WriteFunc);

    // dlclose(handle_read);
    // dlclose(handle_write);


    // dlclose(handle);

}
