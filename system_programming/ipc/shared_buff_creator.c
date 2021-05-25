#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define BUF_SIZE 1024
#define SHM_KEY 0x1234

struct shmseg {
   int cnt;
   int complete;
   char buf[BUF_SIZE];
};
int fill_buffer();

int main() {
   int shmid, numtimes;
   struct shmseg *shmp;
   char *bufptr;
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

   /* Transfer blocks of data from buffer to shared memory */
   bufptr = shmp->buf;

   for (numtimes = 0; numtimes < 3; ++numtimes) {
      shmp->cnt = fill_buffer(bufptr);
      /*shmp->complete = 0;*/
      printf("Writing Process: Shared Memory Write: Wrote %d bytes\n", shmp->cnt);
      bufptr = shmp->buf;
      sleep(1);
   }
   printf("Writing Process: Wrote %d times\n", numtimes);
   /*shmp->complete = 1;*/

   if (shmdt(shmp) == -1) {
      perror("shmdt");
      return 1;
   }

   printf("Writing Process: Complete\n");
   return 0;
}

int fill_buffer(char * bufptr)
{
   int filled_count;

   memcpy(bufptr, "WOW\0", 4);
   filled_count = strlen(bufptr);

   return filled_count;
}
