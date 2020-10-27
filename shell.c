/*	
Assignment 4
Author: Rahul Talari
Email: rtalari@cpp.edu
Andrew Kim, Kobe Lee, Celine Tran

Necessary commands -- 
cd - Change directory
pwd - Present Working directory
mkdir - Make a directory (Alerts if already exists)
rmdir - Remove the directory (Alerts if no such file or directory)
ls - List contents of pwd
cp - Copy contents from one file to another
exit - Exit the shell
Should be able to run executables
*/

// cd src
// gcc -c ls.c
// gcc -c shell.c
// gcc -o test ls.o shell.o -lreadline
// ./test
// gcc -lm src/shell.c -o src/shell -lreadline

#include<stdio.h> 
#include<string.h> 
#include<stdlib.h>
#include<readline/readline.h>
#include<sys/wait.h> 

#include <sys/stat.h>
#include <sys/types.h>

#include "ls.h"
#include "pwd.h"
#include "cp.h"

int mkdir(const char *pathname, mode_t mode);
char **get_input(char *);
int cd(char *);  


int main(void){
  //indicates which specific command to run at the moment
  char **command; 
	//store user input to indicate command
  char *input; 

	//while loop to allow continuous control of shell until terminated
  while(1){
		//add in patriotsh for Team Patriots shell
    input = readline("patriotsh> "); 
		//call get_input function with input to parse the input to indicate command
		//and any other arguments
    command = get_input(input); 

    if (!command[0]){ // empty commands, no input
      free(input); 
      free(command); 
      continue; 
    }
		//change directory command is called
    if(strcmp(command[0], "cd") == 0){
      if(cd(command[1]) < 0){
        perror(command[1]); 
      }
      continue; 
    }
		//present working directory path
		else if(strcmp(command[0], "pwd") == 0){
      char *p[2] = {"pwd", "."}; 
      pwd(2, p); 
    }
		//make directory command is called
    else if(strcmp(command[0], "mkdir") == 0){
      mkdir(command[1],0777);
    }
		//remove directory command is called
    else if(strcmp(command[0], "rmdir") == 0){
      rmdir(command[1]);
    }
		//list contents of present working directory called
    else if(strcmp(command[0], "ls") == 0){
      char *p[2] = {"ls", "."}; 
      ls(2, p); 
    }
		//copy file content from one file to another file
		else if(strcmp(command[0], "cp") == 0){
			char *p[3] = {"cp", command[1], command[2]}; 
			cp(3, p); 
		}
		//exit command is called
    else if(strcmp(command[0], "exit") == 0){
      exit(0); 
    }
		//for any input that is not a correct built in command
		else
			printf("Command does not exist");
    
    free(input); 
    free(command); 
  }
  
  return 0; 
}

//function called to parse the user's input to identify specific command
//and subsequent arguments
char **get_input(char *input){
  // initialize pointer to pointer by allocating //block of memory on the heap
  char **command = malloc(8* sizeof(char *));
  
  //will identify a space " " as the separator key between commands and 
	//arguments
  char *separator = " "; 
  char *parsedInput; 
	//used for the index of command array
  int index = 0; 

  //strtok function breaks input string into multiple parts
  //separator signals where to break
  parsedInput = strtok(input, separator); 

	
  while(parsedInput != NULL){
    // Iterate through the tokens with index and subsequent increments
    command[index] = parsedInput; 
    index++; 
    
    //empty parsed
    parsedInput = strtok(NULL, separator); 
  }

  // Set final index of command to null in order to terminate
  command[index] = NULL; 
  return command; 
}

int cd(char *path){
  return chdir(path);
}