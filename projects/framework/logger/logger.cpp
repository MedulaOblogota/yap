#include <iostream>
#include <fstream>
#include <pthread.h>
#include <cstdlib>
#include <sstream>
#include <unistd.h>
#include <ctime>

#include "logger.hpp"
#include "shared_ptr.hpp"


Logger::Logger(Severity initialSeverity, SharedPtr<std::ostream> os)
  : m_severity(initialSeverity), m_curr_output(os), m_queue(), m_thread_flag(1)
{
  // m_mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(&m_mutex, NULL);
  pthread_create(&m_thread, NULL, LoggingFunc, this);
}

Logger::~Logger()
{
  // FlushMessages(m_queue.size());
  // printf("queue size = %lu\n", m_queue.size());
  m_thread_flag = 0;
  pthread_join(m_thread, NULL);
  // m_curr_output->flush();
}

const char * Logger::GetCurrentSeverity()
{
  return GetSeverityName(m_severity);
}

std::queue<std::string> Logger::GetQueue()
{
  return m_queue;
}

void *Logger::LoggingFunc(void *arg)
{
  Logger *logger = static_cast<Logger *>(arg);

  while (logger->m_thread_flag)
  {
    sleep(1);

    pthread_mutex_lock(&logger->m_mutex);

    size_t queue_size = logger->m_queue.size();

    pthread_mutex_unlock (&logger->m_mutex);

    logger->FlushMessages(queue_size);
    // logger->m_curr_output->flush();

  }

  pthread_mutex_lock(&logger->m_mutex);

    size_t queue_size = logger->m_queue.size();

    pthread_mutex_unlock (&logger->m_mutex);

    logger->FlushMessages(queue_size);
    // logger->m_curr_output->flush();

  return NULL;
}

void Logger::Log(Severity msgSeverity, const char *msg)
{
  std::stringstream ss;

  if (msgSeverity >= m_severity)
  {
    time_t current = time(0);
    pthread_mutex_lock (&m_mutex);

    // printf("logging\n");

    ss << GetSeverityName(msgSeverity) << " | " << asctime(gmtime(&current)) << ": " << msg << "\n";

    m_queue.push(ss.str());

    // std::cout << m_queue.front();
    pthread_mutex_unlock (&m_mutex);
  }


}

void Logger::Log(Severity msgSeverity,const std::string &msg)
{
  std::stringstream ss;
  time_t current = time(0);

  if (msgSeverity >= m_severity)
  {
    pthread_mutex_lock (&m_mutex);

  // printf("logging\n");

    ss << GetSeverityName(msgSeverity) << " | " << asctime(gmtime(&current)) << ": " << msg << "\n";
  // ss << GetSeverityName(msgSeverity) << " | " <<  __DATE__ << " | " << __TIME__ << ": " << msg << "\n";

    m_queue.push(ss.str());
    pthread_mutex_unlock (&m_mutex);
  }

  // std::cout << m_queue.front();
}

void Logger::SetOutputSeverity(Severity outputSeverity)
{
  m_severity = outputSeverity;
}

void Logger::SetOutput(SharedPtr<std::ostream> os)
{
  m_thread_flag = 0;
  pthread_join(m_thread, NULL);

  m_curr_output = os;
  m_thread_flag = 1;
  pthread_create(&m_thread, NULL, Logger::LoggingFunc, this);
}

void Logger::FlushMessages(std::size_t queue_size)
{
  for (std::size_t i = 0; i < queue_size; ++i)
  {
    std::string last_msg = m_queue.front();
    *m_curr_output << last_msg << std::endl;
    // *m_curr_output << "\n";
// std::cout << last_msg << " lastmsg\n";

    m_queue.pop();
  }
}

void Logger::AddSeverity()
{
  switch (m_severity)
  {
    case (DEBUG):
      m_severity = INFO;
      break;
    case (INFO):
      m_severity = WARNING;
      break;
    case (WARNING):
      m_severity = ERROR;
      break;
    default:
      break;
  }
}

void Logger::ReduceSeverity()
{
  switch (m_severity)
  {
    case (INFO):
      m_severity = DEBUG;
      break;
    case (WARNING):
      m_severity = INFO;
      break;
    case (ERROR):
      m_severity = WARNING;
      break;
    default:
      break;
  }
}
const char *Logger::GetSeverityName(Severity sev_)
{
	const char *ERROR_NAME = "ERROR  ";
	const char *WARNING_NAME = "WARNING";
	const char *INFO_NAME = "INFO   ";
	const char *DEBUG_NAME = "DEBUG  ";

  switch (sev_)
	{
	case (DEBUG):
	{
		return (DEBUG_NAME);
	}
	case (INFO):
	{
		return (INFO_NAME);
	}
	case (WARNING):
	{
		return (WARNING_NAME);
	}
	case (ERROR):
	{
		return (ERROR_NAME);
	}
	}
	return (0);
}

int Logger::GetFlag()
{
	return m_thread_flag;
}
