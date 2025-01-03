#include "kernel/types.h"
#include "user/user.h"
#include "kernel/syscall.h"


int main(void) {
	int fd[2];
	int fd1[2];
	
	pipe(fd);
	pipe(fd1);
	
	if(fork() == 0) {
	  
	  close(fd[1]);
	  char buff[10];	  
	  read(fd[0], buff, 10);
	  printf("P1 said: %s\n",buff);
	  close(fd[0]);
	  
	  close(fd1[0]);
	  write(fd1[1], "pong", 4);
	  close(fd1[1]);
	  
	
	}
	
  else {
  
    close(fd[0]);
    write(fd[1], "ping", 4);
    close(fd[1]);
    
    wait(0);
    
    close(fd1[1]);
    char buff[10];
    read(fd1[0], buff, 10);
	  printf("P2 said: %s\n",buff);
    close(fd1[0]);

  
  }
  
  exit(0);
	
}






