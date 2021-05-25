#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define NUM_OF_PCSS (3)
struct msgbuf
{
   long mtype;
   char mtext[20];
};

int main()
{
  char message[] = "whaddup??";
  char message2[] = "my";
  char message3[] = "friend";

  int msqid;
  key_t key;
  struct msgbuf buff;
  struct msgbuf buff2;
  struct msgbuf buff3;
  size_t i = 0;

  strcpy(buff.mtext, message);
  buff.mtype = 1;

  strcpy(buff2.mtext, message2);
  buff2.mtype = 2;

  strcpy(buff3.mtext, message3);
  buff3.mtype = 3;

  system("touch msgq.txt");

  if ((key = ftok("/home/student/roy-yablonka/system_programming/ipc/msgq.txt", 'B')) == -1)
  {
      perror("ftok");
      return(1);
   }

   if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1)
   {
      perror("msgget");
      return(2);
   }

   /*for (i = 0; i < NUM_OF_PCSS; ++i)
   {*/
     if (msgsnd(msqid, &buff, 10, 0) == -1)
     {
       perror("msgsend");
       return 3;
     }

     if (msgsnd(msqid, &buff2, 10, 0) == -1)
     {
       perror("msgsend");
       return 3;
     }

     if (msgsnd(msqid, &buff3, 10, 0) == -1)
     {
       perror("msgsend");
       return 3;
     }

   /*}*/
   /*
   if (msgctl(msqid, IPC_RMID, NULL) == -1)
   {
      perror("msgctl");
      exit(1);
   }
*/

   return 0;
}
