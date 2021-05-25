#include "factory_sync.hpp"
#include "logger.hpp"
#include "singleton.hpp"
#include "addseverity.hpp"
#include "reduceseverity.hpp"
#include "exit.hpp"
// #include "write.hpp"
// #include "read.hpp"
#include "command.hpp"

// Logger *fac_logger = Singleton<Logger>::GetInstance();

SharedPtr<Command> Increment(void *do_nothing)
{
	(void)do_nothing;
    // fac_logger->AddSeverity();
    return SharedPtr<Command>(new AddSeverity);
}

SharedPtr<Command> Decrement(void *ignore)
{
	(void)ignore;
    // fac_logger->ReduceSeverity();
	return SharedPtr<Command>(new ReduceSeverity);
}

SharedPtr<Command> Exit(void *flag)
{
    *(int *)flag = 0;
	return SharedPtr<Command>(new ExitClass);
}

void AcceptInput()
{
     Factory<SharedPtr<Command>, std::string, void *> factory;
     int exit_flag = 1;
     std::string input;

    factory.add("+", Increment);
    factory.add("-", Decrement);
    factory.add("exit", Exit);

    std::cout << "input command: ";
    std::cin >> input;
    // while (exit_flag)
    // {
        (*factory.create(input, &exit_flag))();

        // std::cout << "input command: ";
        // std::cin >> input;
    // }
}
