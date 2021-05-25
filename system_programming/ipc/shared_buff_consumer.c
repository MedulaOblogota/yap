/* MUST INPUT NUMBER AFTER EXECUTION FOR PROCESS NUMBER */

#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>

#define BUF_SIZE 1024
#define SHM_KEY 0x1234
#define NUM_OF_PCSS (3)

struct shmseg {
   int cnt;
   int complete;
   char buf[BUF_SIZE];
};

int main(int argc, char *argv[]) {
   int shmid;
   struct shmseg *shmp;

   int num_of_arg = 0;

   if (argc != 2)
   {
     printf("no argument inserted! please input num from 0 to %lu at execution!\n", NUM_OF_PCSS);
     return -1;
   }

   num_of_arg = atoi(argv[1]);

   (void)argc;

   shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644|IPC_CREAT);
   if (shmid == -1) {
      perror("Shared memory");
      return 1;
   }

   shmp = shmat(shmid, NULL, 0);
   if (shmp == (void *) -1) {
      perror("Shared memory attach");
      return 1;
   }

   /* Transfer blocks of data from shared memory to stdout*/

    if (!strcmp("", shmp->buf))
    {
      printf("no shared memory created!\n");
      return -1;
    }
    
    printf("segment contains : \n\"%s\"\n", shmp->buf);

    if (shmp->cnt == -1) {
       perror("read");
       return 1;
    }

    printf("Reading Process: Shared Memory: Read %d bytes\n", shmp->cnt);

   printf("Reading Process: Reading Done, Detaching Shared Memory\n");
   if (shmdt(shmp) == -1) {
      perror("shmdt");
      return 1;
   }
   printf("Reading Process: Complete\n");

   if (num_of_arg == 2)
   {
     if (shmctl(shmid, IPC_RMID, 0) == -1)
     {
        perror("shmctl");
        return 1;
     }
   }

   return 0;
}
