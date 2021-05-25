#include <stdio.h>
#include <unistd.h>

enum errors {pipe_problem = 1, fork_problem};
int main()
{
  int ping_to_pong[2];  /*0 is reader. 1 is writer*/
  int pong_to_ping[2];

  char ping[] = "ping";
  char pong[] = "pong";

  int num_of_bytes;
  char input1[20];
  char input2[20];

  int child_pid;


  if ((-1 == pipe(ping_to_pong)) || (-1 == pipe(pong_to_ping)))
  {
    perror("pipe");
    return pipe_problem;
  }

  if ((child_pid = fork()) == -1)
  {
    perror("fork");
    return(fork_problem);
  }

  if (child_pid == 0) /*child process. writes ping and reads pong*/
  {
    close(pong_to_ping[1]);
    close(ping_to_pong[0]);
    while (1)
    {
      write(ping_to_pong[1], ping, sizeof(ping));
      read(pong_to_ping[0], input2, sizeof(input2));
      printf("%s\n", input2);
      sleep(1);
    }
  }
  else  /*parent process*/
  {
    close(pong_to_ping[0]);
    close(ping_to_pong[1]);
    while (1)
    {
      read(ping_to_pong[0], input1, sizeof(input1));
      write(pong_to_ping[1], pong, sizeof(pong));
      printf("%s\n", input1);
      sleep(1);
    }
  }

  return 0;
}
