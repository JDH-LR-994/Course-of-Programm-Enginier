#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main(void)
{
  printf("Enter 'q' to exit\n");
  while (getchar()!= 'q'){
    key_t key;
    int semid;
    int count;
    
    if ((key = ftok(".", 'J')) == -1){
      perror("ftok");
      exit(1);
    }
    
     if ((semid = semget(key, 1, 0)) == -1){
      perror("semget");
      exit(1);
    }
    
     if ((count = semctl(semid, 0, GETNCNT)) == -1){
      perror("semctl");
      exit(1);
    }
    
    printf("Semafores in waiting state: %d\n", count);
    printf("Enter 'q' to exit\n");
  }
  
  return 0;
}

