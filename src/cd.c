#include <stdio.h> 
#include <stdlib.h> 
#include<string.h> 
#include<unistd.h> 

int cd(int argc, char** argv){
  // check for whether the argument count is invalid
	if (argc != 2){
    printf("\n Invalid cd call\n\n"); 
		return(1); 
  }
  // the case of cd'ing in to .. is unique; check for it here
  if(strcmp(argv[1], "..") == 0){
    chdir("..");
  }
  // any other directory will be changed accordingly through the proper argument
  else{
    if(chdir(argv[1])==0){
      printf("\nDirectory changed successfully\n\n");
    }
    // if it doesn't return a zero status, the directory is not valid
    else {
      printf("\nInvalid directory\n\n");
    }
  }
  return(0);
}