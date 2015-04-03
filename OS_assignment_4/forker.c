#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <sched.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXFILENAMELENGTH 80

int main(int  argc, char* argv[]){

	//argv1 = program
	//argv2 = number of processes
	//argv3 = arguments to give to program

	if(argc != 4){
		exit(1);
	}

	//fork n processes
	int i;
	int j;
	int status;
	for(i = 0; i < atol(argv[2]); i++){
		if(fork() == 0){
			execve(argv[1], &argv[3], NULL); // run program with arguments
										// you want it to take
		}
	}
	for(j = 0; j < atol(argv[2]); j++){
		waitpid(0, &status, 0); // wait for the children
	}

	return 0;

}