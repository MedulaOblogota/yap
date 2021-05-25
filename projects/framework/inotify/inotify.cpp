#include <sys/inotify.h>
#include <sys/types.h>
#include <unistd.h>

#include "inotify.hpp"

Inotify::Inotify(std::string path)
    : m_path(path), m_fd(inotify_init()), m_filename()
{
    if (m_fd < 0)
    {
        perror("Inotify Initialization");
    }

    m_wd = inotify_add_watch(m_fd, m_path.c_str(), IN_CREATE | IN_DELETE | IN_MODIFY);

    std::cout << path << " is being watched..." << std::endl;
}

Inotify::~Inotify()
{
    inotify_rm_watch(m_fd, m_wd);
    close(m_fd);

    std::cout << "finished watching" << m_path << std::endl;
}

// std::vector<std::string> Inotify::WatchDirectory()
std::string Inotify::WatchDirectory()
{
    // std::cout << "in WatchDirectory. m_path is " << m_path << std::endl;
    const size_t EVENT_SIZE(sizeof(struct inotify_event));
    const size_t EVENT_BUF_LEN( 1024 * ( EVENT_SIZE + 16 ) );

    char buffer[EVENT_BUF_LEN];
    int length = read(m_fd, buffer, EVENT_BUF_LEN);
    int i = 0;

    // std::cout << m_path << std::endl;

    if ( length < 0 ) 
    {
        perror( "read" );
    } 

    while ( i < length ) 
    {     
        struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];     
        
        if ( event->len ) 
        {
            if ( event->mask & IN_CREATE ) 
            {
                if ( event->mask & IN_ISDIR ) 
                {
                    printf( "New directory %s created.\n", event->name );
                    // m_filenames.push_back(event->name);
                }
                else 
                {
                    printf( "New file %s created.\n", event->name );
                    m_filename = event->name;
                }
            }
            else if ( event->mask & IN_DELETE ) 
            {
                if ( event->mask & IN_ISDIR ) 
                {
                    printf( "Directory %s deleted.\n", event->name );
                    // m_filenames.push_back(event->name);
                }
                else    
                {
                    printf( "File %s deleted.\n", event->name );
                    // m_filenames.push_back(event->name);
                }
            }
            else if ( event->mask & IN_MODIFY ) 
            {
                if ( event->mask & IN_ISDIR ) 
                {
                    printf( "Directory %s modified.\n", event->name );
                    // m_filenames.push_back(event->name);
                }
                else    
                {
                    printf( "File %s modified.\n", event->name );
                    // m_filenames.push_back(event->name);
                }
            } 
        }
        i += EVENT_SIZE + event->len;

        
        // std::cout << "in while(1)" << std::endl;
        

    }
    return m_filename;
}


std::string Inotify::GetFilenames()
{
    return m_filename;
}