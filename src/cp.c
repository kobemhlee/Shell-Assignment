#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h> 
#include <errno.h> 

#include "cp.h"
//size limit for file size
#define BUFFER_SIZE 1024 

//this function takes a source file and copies its contents onto a newly
//created target file
int cp(int argc, char** argv){
	int srcFile, targetFile, readStatus, writeStatus; 
	char *buff[BUFFER_SIZE]; 

	//if call does not have 3 arguments, print error message and return 1
	if(argc != 3){
		printf("\n Invalid cp call"); 
		return(1); 
	}

	//open source file as read only and return value to srcFile based on success
	srcFile = open(argv[1], O_RDONLY); 

	//if srcFile contains failed status, print error message and return 1
	if(srcFile == -1){
		printf("\nError opening file %s errno = %d\n", argv[1], errno); 
		return(1); 
	}
	//create and open target file with following permissions
	//write-only, created file, truncated, read-user, write-user
	targetFile = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR );

	//if targetFile contains failed status, print error message and return 1
	if(targetFile == -1){
		printf("\n Error opening file %s errno = %d\n", argv[2], errno); 
		return(1); 
	}
	//while loop as long as nbread is > 0, continue reading srcFile
	while((readStatus = read(srcFile, buff, BUFFER_SIZE)) > 0){
		//temp variable to store status from write function
		writeStatus = write(targetFile, buff, readStatus); 
		//if return status from read and write functions are not equal, print error
		//message
		if(writeStatus != readStatus)
			printf("\n Error in writing data to %s\n", argv[2]); 
	}
	//if error status from srcFile, print appropriate error message
	if(readStatus == -1)
		printf("\nError in reading data from %s \n", argv[1]); 

	//if error status from closing srcFile, print appropriate error message
	if(close(srcFile) == -1)
		printf("\nError in closing file %s\n", argv[1]); 

	//if error status from closing targetFile, print appropriate error message
	if(close(targetFile) == -1)
		printf("\nError in closing file %s\n", argv[2]); 

	return(0); 
}
