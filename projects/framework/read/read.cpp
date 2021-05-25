#include <fstream>

#include "logger.hpp"
#include "singleton.hpp"
#include "read.hpp"


Logger* Reader::read_logger = Singleton<Logger>::GetInstance();

Reader::Reader(char *buffer_, std::size_t offset, struct sockaddr_in client_addr, int socket_fd)
    :   IOFile(buffer_, offset, client_addr, socket_fd)
{
    read_logger->Log(Logger::WARNING, "Reader -> opening file");
}

Reader::~Reader()
{
    read_logger->Log(Logger::INFO, "Reader -> closing file");
}

bool Reader::operator()()
{
    socklen_t len = sizeof(struct sockaddr);
    m_file.open(m_ds_buffer.GetFile());

		bool ret = m_file.good();
		read_logger->Log(Logger::DEBUG, "Reader -> checking to see if it works");
		if (ret)
		{
            read_logger->Log(Logger::INFO, "Reader -> succesfully received buffer");
            m_file.read(m_buffer + m_offset, 4096);
    	// m_file >> (m_buffer + m_offset);
		}
        else
        {
            read_logger->Log(Logger::INFO, "Reader -> failed to receive buffer");
        }

         sendto(m_socket_fd, (const char *)m_buffer, 4106,
                MSG_CONFIRM, (const struct sockaddr *)&m_client_addr,
                len);

    m_file.close();

    return ret;
}


SharedPtr<Command> Create(serv_arg_t *arg)
{
    // std::cout << "\n\nRead: IN Create" << std::endl;
  return SharedPtr<Command>(new Reader(arg->buffer, 10, arg->address, arg->fd));
}

char GetKey()
{
    return 0;
}
