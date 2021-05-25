#ifndef RD70_EXITCLASS
#define RD70_EXITCLASS

#include "logger.hpp"
#include "command.hpp"

class ExitClass: public Command
{
public:
	// static void Exit();
	bool operator()();

private:
	static Logger *exit_logger;
};

#endif //RD70_EXITCLASS
