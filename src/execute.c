#include <stdio.h> 
#include <sys/types.h>

#include "execute.h"

int execute(int argc, char** argv){
	//process id for the execution call
	pid_t pid; 
	int status; //status to keep program running while it waits for other pid

	//uses fork to go from parent process to child process
	//if pid does not exist, forking to child process will fail
	if((pid = fork())< 0){
		printf("Error: Failed to fork child process\n"); 
		exit(1); 
	}

	// uses exec to execute the file
	else if(pid == 0){
		// fails if the file doesn't exist 
		if(execl(argv[1],"", (char *)NULL) < 0){
			printf("Error: Execution failed\n"); 
			exit(1); 
		}
	}
	
	// wait for other commands
	else{
		while(wait(&status) != pid)
			;
	}
}