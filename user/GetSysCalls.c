#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
	
    int pid = fork(); //create child
    
    //no input error
    if(argc < 2) {
      printf("no input provided");
      exit(1);
    }
    
    //child process
    if(pid == 0) {
      
      if(exec(argv[1], argv) < 0) { //execute the given program in child process
        printf("exec failed");
        exit(1);
      }
      
      printf("Some error happened");
      exit(1);    
    }
    
    //parent process
    else if(pid > 0) {
    
      wait(0); //wait for child to excecute
      int c = childSysCallCount(); //get the child's sys calls with the newly created system call
      printf("The program ended with this many sys calls: %d\n", c);
      exit(0);
    }
    
    //forking error
    else {
      printf("some error happened");
      exit(1);
    }
    
    exit(0);

}

