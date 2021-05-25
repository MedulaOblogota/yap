#include <iostream>
#include <fstream>
#include <sstream>

#include "logger.hpp"

int main()
{
  Logger logger = Logger(Logger::DEBUG);
  std::string str = "my man";
  logger.Log(Logger::ERROR, "wassup?");

  logger.Log(Logger::WARNING, str);

  logger.SetOutputSeverity(Logger::ERROR);

  logger.Log(Logger::INFO, "1. if it shows then baaaad");

  logger.Log(Logger::WARNING, "2. if it shows then baaaad");

  logger.Log(Logger::ERROR, "if it shows then GOOOOD");

  std::ofstream logfile;

  logfile.open("a.log");

  logger.SetOutput(logfile);

  logger.Log(Logger::ERROR, "if it shows then GOOOOD");

  std::ostringstream buffer;

  buffer.str("Test");
  logger.SetOutput(buffer);

  logger.Log(Logger::ERROR, "last! if it shows then GOOOOD");

}
