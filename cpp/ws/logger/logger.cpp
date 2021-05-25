#include <iostream>
#include <fstream>

#include "logger.hpp"

Logger::Logger(Severity initialSeverity)
  : severity(initialSeverity), curr_output(&std::cerr)
{

}

void Logger::Log(Severity msgSeverity, const char *msg)
{
  std::ofstream garbage("/dev/null");
  std::ostream *lut[] = {&garbage, curr_output};
  std::string enum_lut[] = {"DEBUG", "INFO", "WARNING", "ERROR"};

  *lut[msgSeverity >= severity] << enum_lut[msgSeverity] << " - " << msg << std::endl;
}

void Logger::Log(Severity msgSeverity,const std::string &msg)
{
  std::ofstream garbage("/dev/null");
  std::ostream *lut[] = {&garbage, curr_output};
  std::string enum_lut[] = {"DEBUG", "INFO", "WARNING", "ERROR"};

  *lut[msgSeverity >= severity] << enum_lut[msgSeverity] << " - " << msg << std::endl;
}

void Logger::SetOutputSeverity(Severity outputSeverity)
{
  severity = outputSeverity;
}

void Logger::SetOutput(std::ostream &output)
{
  curr_output = &output;
}
