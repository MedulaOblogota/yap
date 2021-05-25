#ifndef RD70_LOGGER
#define RD70_LOGGER

#include <iosfwd>
#include <queue>          // std::queue
#include <pthread.h>
#include <cstddef>
#include <iostream>

#include "shared_ptr.hpp"

class Logger
{
public:
  enum Severity { DEBUG, INFO, WARNING, ERROR };

  explicit Logger(Severity initialSeverity = WARNING, SharedPtr<std::ostream> output =
                    SharedPtr<std::ostream>(new std::ostream(std::cout.rdbuf() ) ) );

  ~Logger();

  void Log(Severity msgSeverity, const char *msg);
  void Log(Severity msgSeverity, const std::string &msg);

  void SetOutputSeverity(Severity outputSeverity);
  void SetOutput(SharedPtr<std::ostream>);

  void AddSeverity();
  void ReduceSeverity();

  const char *GetCurrentSeverity();

	int GetFlag();

  std::queue<std::string> GetQueue();

private:
  Severity m_severity;
  SharedPtr<std::ostream> m_curr_output;
  std::queue<std::string> m_queue;

  int m_thread_flag;
  pthread_t m_thread;
  pthread_mutex_t m_mutex;

  static const std::size_t FLUSH_AMOUNT = 10;

  static void *LoggingFunc(void *arg);
  void FlushMessages(std::size_t);
  const char* GetSeverityName(Severity sev_);
};

#endif //RD70_LOGGER
