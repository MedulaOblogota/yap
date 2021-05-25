#include <iostream>
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

class UdpServer
{
public:
    explicit UdpServer(int port_, char *buffer);
    std::size_t Receive() const;
    void Send();

    static const size_t BUFFER_SIZE = 4096;

private:
    int m_port;
    struct sockaddr_in m_cliaddr;
    struct sockaddr_in m_servaddr;
    int m_socket;
    char *m_buffer;
    // char m_filename[23];

    int CreateSocket();
    void SetStructs();
    void FillServerInfo();
    // void GetFilename();
};


