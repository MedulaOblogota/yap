#include "addseverity.hpp"
#include "logger.hpp"
#include "singleton.hpp"
// #include "singleton.hpp"

// Logger* AddSeverity::add_severity_logger = Singleton<Logger>::GetInstance();

bool AddSeverity::operator()()
{
	Logger *aLogger = Singleton<Logger>::GetInstance();
    std::cout << "reached addseverity. current severity is " << aLogger->GetCurrentSeverity() << std::endl;

		if (aLogger != NULL)
		{
			std::cout << "not NULL!" << std::endl;
		}
    aLogger->AddSeverity();
    char *curr_severity = const_cast<char *>(aLogger->GetCurrentSeverity());
    aLogger->Log(Logger::ERROR, "Logger Severity Level increased to " + std::string(curr_severity));
		// aLogger->Log(Logger::ERROR, "Logger Severity Level incremented");

    return true;
}
