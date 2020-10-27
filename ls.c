#include<sys/types.h>
#include<dirent.h>
#include<stdio.h>
#include<stdlib.h>

#include "ls.h"

//this function lists the contents of the present working directory
int ls(int argc, char** argv){
	//directory data type, to store the path of the directory
  DIR* dirPath;
	//data structure for directory entries
  struct dirent* dirEntry;

	//if opendir function returns as failed, then print error and exit
  if(!(dirPath=opendir(argv[1])) ) {
    printf("opendir error\n");
    exit(1);
  }
    
	//while loop to read directory and breaks when it has reached the end of path
  while(1) {
    dirEntry=readdir(dirPath);
      if(!dirEntry)
        break;
		//print path
    printf("%s \n", dirEntry->d_name);

  }
  
  return 0;
}