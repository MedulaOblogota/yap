#ifndef RD70_REDUCESEVERITY
#define RD70_REDUCESEVERITY

#include "logger.hpp"
// #include "singleton.hpp"
#include "command.hpp"

class ReduceSeverity:public Command
{
public:
    bool operator()();
    // void operator()();

private:
    static Logger *reduce_severity_logger;
};

#endif //RD70_REDUCESEVERITY