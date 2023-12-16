#include <stdio.h>
#include <stdlib.h>
#include "rdtsc.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include<stdio.h>
 
#include<stdlib.h>
 
#include<string.h>
#include <fcntl.h>
// simultanueously read the files of the same sizes
// 256MB

#define BLOCK_SIZE 4096
#define FILE_SIZE 256*1024*1024
int main(int argc, char *argv[]){
	int process_number;
	int process_id;
	int status;
	int ret;
	process_id = 0;
	pid_t pid;
	if (argc != 2){
		printf("Usage: ./contention <process_number>\n");
	}
	
	process_number = atoi(argv[1]);
	
	
	printf("Running... process number:%d\n", process_number);
	for(int i=0; i<process_number; ++i){
		pid = fork();
		if (pid == 0){
			//printf("%d\n", process_id);
			break;
		}else if(pid <0){
			perror("fork error!\n");
			return -1;
		}
		process_id ++;
	}
	
	if (pid==0){
	// read the file!
		//printf("I'm here!I'm child!\n");
		char *buff[3];
		char *file_name[10];
		snprintf (buff, sizeof(buff), "%d",process_id);
		//printf("1\n");
		strcpy(file_name, "256_");
		strcpy(file_name, buff);
		//printf("2\n");
		int in_file;
		unsigned long long a,b, sum;
		char *buffer = (char*)malloc(BLOCK_SIZE);
		sum = 0;
		
		in_file = open(file_name, O_RDONLY);
		if (!in_file){
			printf("Error opening the target file: %s\n", file_name);
			return -1;
		}
		for (int j=0; j<(FILE_SIZE/BLOCK_SIZE); ++j){
			a = rdtsc();
			read(in_file, buffer, BLOCK_SIZE);
			b = rdtsc();
			sum += (b-a);
		}
		
		printf("Child Process: %d, the total cycles: %llu, cycles per block: %f\n", process_id, sum, 1.0*sum/((FILE_SIZE)/BLOCK_SIZE));
		exit(0);
	
	}else{
	    	while (1) {
			ret = wait(NULL);
			if (ret == -1) {
				break;
		    	}
		}
	    }
	
	return 0;
}
