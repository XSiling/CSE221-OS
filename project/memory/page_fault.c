#include <stdio.h>
#include <sys/mman.h>
#include "rdtsc.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define PAGE_SIZE 4096
#define PAGE_NUM 16
#define FILE_SIZE PAGE_SIZE*PAGE_NUM
#define ARRAY_SIZE 200000


int main(int argc, char* argv[]){
	const char *filepath = "disk_file.txt";
	int fd = open(filepath, O_RDWR|O_CREAT|O_TRUNC);
	char tmp;
	register size_t *p;
	register size_t sum = 0;
	unsigned long long a,b;
	size_t dataArray[ARRAY_SIZE];
	
	
	if (fd<0){
		printf("File open failed!\n");
		return -1;
	}
	
	lseek(fd, FILE_SIZE-1, SEEK_SET);
	write(fd, "", 1);
	
	char *ptr = mmap(0, FILE_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	

	a = rdtsc();
	for(int i=0; i<PAGE_NUM;++i){
		//tmp = ptr[i*PAGE_SIZE];
		ptr[i*PAGE_SIZE]=0;
	}
	b = rdtsc();
	munmap(ptr, FILE_SIZE);
	close(fd);
	
	printf("The total cycles: %llu, the file size: %d, average for one page:%llu, average for one byte:%llu\n", b-a, FILE_SIZE, (b-a)/PAGE_NUM, (b-a)/PAGE_NUM/PAGE_SIZE );


}
