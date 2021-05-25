#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

enum errors {pipe_problem = 1, fork_problem};
int main()
{
  int fd;
  char *myfifo = "/home/student/roy-yablonka/system_programming/ipc/myfifo";

  char pong[] = "pong";

  int num_of_bytes;
  char input[20];


  /* mkfifo(myfifo, 0640);*/



  fd = open(myfifo, O_RDWR);
  while (1)
  {
    read(fd, input, sizeof(input));
    write(fd, pong, sizeof(pong));
    printf("%s\n", input);
    sleep(1);
  }

  return 0;
}
