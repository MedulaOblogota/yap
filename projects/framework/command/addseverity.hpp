#ifndef RD70_ADDSEVERITY
#define RD70_ADDSEVERITY

#include "logger.hpp"
#include "singleton.hpp"
#include "command.hpp"

class AddSeverity:public Command
{
public:
	explicit AddSeverity() : Command() {}
    bool operator()();

private:
    static Logger *add_severity_logger;
};

#endif //RD70_ADDSEVERITY
