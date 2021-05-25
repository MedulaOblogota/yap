#include "udp.hpp"

int UdpServer::CreateSocket()
{
    int sockfd =  socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0)
    {
        perror("socket creation failed");
        return -1;
    }

    return sockfd;
}

void UdpServer::FillServerInfo()
{
    bzero(&m_servaddr, sizeof(m_servaddr));

    m_servaddr.sin_family    = AF_INET; /* IPv4 */
    m_servaddr.sin_addr.s_addr = INADDR_ANY;
    m_servaddr.sin_port = htons(m_port);
}


UdpServer::UdpServer(int port_, char *buffer)
{
    m_port = port_;
    m_socket = CreateSocket();
    m_buffer = buffer;

    memset(&m_servaddr, 0, sizeof(m_servaddr));
    memset(&m_cliaddr, 0, sizeof(m_cliaddr));

    FillServerInfo();

    if ( bind(m_socket, (const struct sockaddr *)&m_servaddr,
            sizeof(m_servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

// void UdpServer::GetFilename()
// {
//     unsigned int uid = *(unsigned int *)(m_buffer + 5);

//     unsigned int index = *(unsigned int *)(m_buffer + 16);

//     sprintf(m_filename, "%d%d.txt", ntohl(uid), index);
// }

std::size_t UdpServer::Receive() const
{
    socklen_t len = sizeof(struct sockaddr);
    std::size_t n = recvfrom(m_socket, (char *)m_buffer, BUFFER_SIZE,
                    MSG_WAITALL, ( struct sockaddr *) &m_cliaddr,
                    &len);
    m_buffer[n] = '\0';

    printf("%s\n", m_buffer);

    return n;
}


void UdpServer::Send()
{
    sendto(m_socket, (const char *)m_buffer, BUFFER_SIZE,  
            MSG_CONFIRM, (const struct sockaddr *) &m_cliaddr, 
                sizeof(struct sockaddr)); 
    
    // printf("%s\n", m_buffer);
}
// void UdpServer::Write()
// {
//     socklen_t len = sizeof(struct sockaddr);
//     std::size_t n = recvfrom(m_socket, (char *)m_buffer, BUFFER_SIZE,
//                     MSG_WAITALL, ( struct sockaddr *) &m_cliaddr,
//                     &len);
//     m_buffer[n] = '\0';
// }
// std::size_t UdpServer::Write()
// {
//     socklen_t len = sizeof(struct sockaddr);
//     std::size_t n = recvfrom(m_socket, (char *)m_buffer, BUFFER_SIZE,
//                     MSG_WAITALL, ( struct sockaddr *) &m_cliaddr,
//                     &len);

//     m_buffer[n] = '\0';

//     GetFilename();

//     fptr = fopen(m_filename, "w+");
//     fwrite(m_buffer + 17, BUFFER_SIZE, 1, fptr);

//     fclose(fptr);

//     return n;    
// }

// bool UdpServer::Read() const 
// {
//     GetFilename();

//     fptr = fopen(m_filename, "r");

//     fread(m_buffer+10, BUFFER_SIZE, 1, fptr);


// }