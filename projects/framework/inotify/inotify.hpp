#ifndef RD70_INOTIFY
#define RD70_INOTIFY

#include <iostream>
#include <cstdio>
#include <vector>
class Inotify
{
public:
    explicit Inotify(std::string);
    ~Inotify();

    std::string WatchDirectory();
    std::string GetFilenames();

    // void ChangePath(std::string);
    

public:
    std::string m_path;
    int m_fd;
    int m_wd;
    // std::vector<std::string> m_filenames;
    std::string m_filename;
};

#endif //RD70_INOTIFY