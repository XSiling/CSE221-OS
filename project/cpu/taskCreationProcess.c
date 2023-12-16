#include <stdio.h>
#include <unistd.h>
#include "rdtsc.h"
#include <sys/wait.h>
#include <sys/types.h>


int main(int argc, char* argv[]){
	unsigned long long a,b;
	FILE *fptr;
	int status;
	char *newArgv[] = {NULL};
	
	// create a process
	a = rdtsc();
	pid_t parent = getpid();
	pid_t pid = fork();
	
	if (pid==-1){
		return -1;
	}else if (pid > 0){
		//parent process
		waitpid(pid, &status, 0);
	}else{
		//child process
		execve("./testCode", newArgv, NULL);
		//return 0;
	}
	b = rdtsc();
	//printf("process cycles: %llu\n", b-a);
	
	
	fptr = fopen("/home/jieyi/Code/cpu/taskCreationResult.txt", "a");
	fprintf(fptr, "process:");
	fprintf(fptr, "%llu", b-a);
	fprintf(fptr, "\n");
	
	return 0;
}
