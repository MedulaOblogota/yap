#include <iosfwd>

class Logger
{
public:
  enum Severity { DEBUG, INFO, WARNING, ERROR };

  explicit Logger(Severity initialSeverity = WARNING);

  void Log(Severity msgSeverity, const char *msg);
  void Log(Severity msgSeverity, const std::string &msg);

  void SetOutputSeverity(Severity outputSeverity);
  void SetOutput(std::ostream &output);

private:
  Severity severity;
  std::ostream* curr_output;
};
