
#include <iostream>
#include "inotify.hpp"

int main()
{

    char path[] = "/tmp/example";
    int i = 0;

    Inotify inotify(path);

    inotify.WatchDirectory();

    for (i = 0; i < inotify.GetFilenames().size(); ++i)
    {
        std::cout << inotify.GetFilenames().at(i) << std::endl;
    }

    return 0;
}