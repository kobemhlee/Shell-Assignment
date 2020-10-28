.PHONY = all clean

CC = gcc 

LINKERFLAG = -lm 

SRCS := src
BINS := src 

all: test 

#like a main method, calls ls.o, pwd.o, etc
#echoes status message and compiles each object file with readline linkage
#test shell program with input.txt file that has an order of commands 
#output.txt file contains the results of input commands in a txt format
test: ls.o pwd.o cp.o execute.o cd.o shell.o
	@echo "Linking files" 
	gcc -o src/shell src/cd.o src/ls.o src/pwd.o src/cp.o src/execute.o src/shell.o -lreadline
	./src/shell < tests/input.txt > tests/output.txt
	diff -s tests/output.txt tests/expectedOutput.txt

#compile ls.c file and create object extension file
ls.o: src/ls.c
	@echo "Compiling ls" 
	gcc -c src/ls.c -o src/ls.o

#compile pwd.c file and create object extension file
pwd.o: src/pwd.c
	@echo "Compiling pwd" 
	gcc -c src/pwd.c -o src/pwd.o

#compile cp.c file and create object extension file
cp.o: src/cp.c
	@echo "Compiling cp" 
	gcc -c src/cp.c -o src/cp.o

execute.o: src/execute.c 
	@echo "Compiling execute" 
	gcc -c src/execute.c -o src/execute.o

cd.o: src/cd.c 
	@echo "Compiling cd" 
	gcc -c src/cd.c -o src/cd.o 

#compile shell.c file and create object extension file
shell.o: src/shell.c 
	@echo "Compiling shell" 
	gcc -c src/shell.c -o src/shell.o

#removes all files that were not present prior to use of the shell program
clean: 
	@echo "Cleaning up..." 
	rm -rvf src/shell.o src/ls.o src/pwd.o src/cp.o src/cd.o src/execute.o src/shell tests/output.txt tests/testFiles/newDrawing.txt