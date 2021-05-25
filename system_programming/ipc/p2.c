/* MUST INPUT NUMBER AFTER EXECUTION FOR PROCESS NUMBER */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define NUM_OF_PCSS (3)

struct my_msgbuf
{
   long mtype;
   char mtext[20];
};

int main(int argc, char *argv[])
{
   struct my_msgbuf buf;
   int msqid;
   key_t key;
   int num_of_arg;

   if (argc != 2)
   {
     printf("no argument inserted! please input num from 0 to %lu at execution!\n", NUM_OF_PCSS);
     return -1;
   }

   num_of_arg = atoi(argv[1]);

   if ((key = ftok("/home/student/roy-yablonka/system_programming/ipc/msgq.txt", 'B')) == -1)
   {
      perror("ftok");
      return(1);
   }

   if ((msqid = msgget(key, 0644)) == -1)  /* connect to the queue */
   {
      perror("blah");
      return(1);
   }

    if (msgrcv(msqid, &buf, sizeof(buf.mtext), 0, num_of_arg) == -1)
    {
       perror("msgrcv");
       exit(1);
    }

    printf("recvd: \"%s\"\n", buf.mtext);


    if (num_of_arg == 2)
    {
      if (msgctl(msqid, IPC_RMID, NULL) == -1)
      {
        perror("msgctl");
        exit(1);
     }
    }

    /*system("rm msgq.txt");*/
    return 0;
}
