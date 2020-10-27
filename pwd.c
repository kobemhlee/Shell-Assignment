#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

#include "pwd.h"
//function presents current working directory
int pwd(int argv, char **argc)
{
	//initialize cwd char array at a limit of 1024 bytes
  char cwd[1024];
	//call getcwd with cwd and its size as a limiter
  getcwd(cwd, sizeof(cwd));
	//print the current working directory and return as success
  printf("%s\n", cwd);
	return 0;
}