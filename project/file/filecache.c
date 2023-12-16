#include <stdio.h>
#include <stdlib.h>
#include "rdtsc.h"
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

#define LOOP_TIME 10
#define BLOCK_SIZE 4096 * 1024


int main(int argc, char *argv[]){
	int in_file;
	unsigned long long file_size, a, b, sum, a1, b1;
	sum = 0;
	if (argc != 3){
		printf("Usage: ./filecache <file_size>(MB) <filename>\n");
		return -1;
	}
	
	file_size = atoi(argv[1]);
	file_size = file_size * 1024 * 1024;
	char *file_name = argv[2];
	char *buffer = (char*)malloc(BLOCK_SIZE);
	
	// first read first
	in_file = open(file_name, O_RDONLY);
	if (!in_file){
		printf("Error opening the target file, check the file name!\n");
		return -1;
	}
	
	for (int i=0; i<file_size/(BLOCK_SIZE); ++i){
		read(in_file, buffer, BLOCK_SIZE);
	}
	close(in_file);
	
	// read for LOOP_TIME
	for(int j=0; j<LOOP_TIME; ++j){
		in_file = open(file_name, O_RDONLY);
		a1 = rdtsc();
		for (int i=0; i<file_size/(BLOCK_SIZE);++i){
			a = rdtsc();
			read(in_file, buffer, BLOCK_SIZE);
			b = rdtsc();
			sum += (b-a);
		}
		b1 = rdtsc();
		close(in_file);
	}
	
	printf("The file size: %llu(MB), the total cycles: %llu, cycles per MB: %f(cycles/MB)\n", file_size/1024/1024, sum, sum*1.0/LOOP_TIME/file_size*1024 * 1024);

}
