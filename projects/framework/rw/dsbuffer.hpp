#ifndef RD70_DSBUFFER
#define RD70_DSBUFFER

#include <stdio.h>
#include <iostream>

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

class DsBuffer
{
public:
    explicit DsBuffer(char *buffer) : m_buffer(buffer) { GetFilename(); }
    bool IsWriter() { return (*m_buffer == 1); }
    char *GetFile() { return m_filename; }

private:
    char *m_buffer;
    char m_filename[23];

    void GetFilename()
    {
        int  indx = m_buffer[16];
        char *runner;
        runner = m_buffer + 5;
        static unsigned int uid = *(unsigned int *)(runner);

        sprintf(m_filename,"%d%d.txt",ntohl(uid),indx);
    }
};

#endif //RD70_DSBUFFER
