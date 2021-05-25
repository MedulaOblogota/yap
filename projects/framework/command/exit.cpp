#include <cstdlib>
#include "exit.hpp"
#include "logger.hpp"
#include "singleton.hpp"

Logger* ExitClass::exit_logger = Singleton<Logger>::GetInstance();

bool ExitClass::operator()()
{
	// ExitClass::exit_logger->Log(Logger::ERROR, "Exited from Server");
	//ExitClass::exit_logger->~Logger();
	exit(0);
}
