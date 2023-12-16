// random read of a file
#include <stdio.h>
#include <stdlib.h>
#include "rdtsc.h"
#include <unistd.h>
#include <fcntl.h>
#include <time.h>


#define BLOCK_SIZE 4096

int main(int argc, char *argv[]){
	
	unsigned long long file_size, a, b, sum;
	int in_file;
	int r;
	if(argc!=3){
		printf("Usage: ./randomRead <file_size> <file_name>\n");
		return -1;
	}
	file_size = atoi(argv[1]);
	file_size = file_size * 1024 * 1024;
	char *file_name = argv[2];
	char *buffer = (char*)malloc(BLOCK_SIZE);
	
	
	in_file = open(file_name, O_RDONLY);
	if (!in_file){
		printf("Error opening the target file, check the file name!\n");
		return -1;
	}
	
	// set no cache
	// set no cache
    	//system("hdparm -W 0 /dev/sda1");
	
	srand(time(NULL));
	sum = 0;
	
	
	for(int i=0; i<file_size/BLOCK_SIZE; ++i){
		r = rand()%(file_size-BLOCK_SIZE);
		
		a = rdtsc();
		lseek(in_file, r, SEEK_SET);
		read(in_file, buffer, BLOCK_SIZE);
		b = rdtsc();
		sum += (b-a);
	}
	

	printf("Random Read: total cycles: %llu, file size: %d(MB), average cycles per block: %f\n", sum, atoi(argv[1]), 1.0*sum/(file_size/BLOCK_SIZE));

}
