#include <fstream>

#include "logger.hpp"
#include "singleton.hpp"

#include "write.hpp"
#include "udp_manager.hpp"


Logger* Writer::write_logger = Singleton<Logger>::GetInstance();

Writer::Writer(char *buffer_, std::size_t offset, struct sockaddr_in client_addr, int socket_fd)
    :   IOFile(buffer_, offset, client_addr, socket_fd)
{
    write_logger->Log(Logger::INFO, "Writer -> opening file");
}

Writer::~Writer()
{
    write_logger->Log(Logger::INFO, "Writer -> closing file");
}

bool Writer::operator()()
{
    socklen_t len = sizeof(struct sockaddr);
        m_file.open(m_ds_buffer.GetFile());
		bool ret = m_file.good();

        // (void)buff_size_;

		if (ret)
		{
            write_logger->Log(Logger::INFO, "Writer -> succesfully received buffer");
    	    m_file.write(( m_buffer + m_offset), 4096);
		}
        else
        {
            write_logger->Log(Logger::INFO, "Writer -> failed to receive buffer");
        }

    sendto(m_socket_fd, (const char *)m_buffer, 10,
                MSG_CONFIRM, (const struct sockaddr *)&m_client_addr,
                len);
    m_file.close();
    return ret;
}

SharedPtr<Command> Create(serv_arg_t *arg)
{
    // std::cout << "\n\nWrite: IN Create" << std::endl;
  return SharedPtr<Command>(new Writer(arg->buffer, 17, arg->address, arg->fd));
}

char GetKey()
{
    return 1;
}