#include "reduceseverity.hpp"
#include "logger.hpp"
#include "singleton.hpp"

// Logger* ReduceSeverity::reduce_severity_logger = Singleton<Logger>::GetInstance();

bool ReduceSeverity::operator()()
{
		Logger *rLogger = Singleton<Logger>::GetInstance();
    std::cout << "reached reduceseverity" << std::endl;
    rLogger->ReduceSeverity();
    char *curr_severity = const_cast<char *>(rLogger->GetCurrentSeverity());
    rLogger->Log(Logger::ERROR, "Logger Severity reduced to " + std::string(curr_severity));

    return true;
}

// void ReduceSeverity::operator()()
// {
//     reduce_severity_logger->ReduceSeverity();
// }
