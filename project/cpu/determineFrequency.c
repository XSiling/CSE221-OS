#include <stdio.h>
#include <unistd.h>
#include "rdtsc.h"


int main(int argc, char* argv[]){
	unsigned long long a,b,avg;
	avg = 0;
	for (int i=0; i<10; ++i){
		a = rdtsc();
		sleep(10);
		b = rdtsc();
		printf("cycles: %llu\n", b-a);
		avg += (b-a);
	}
	printf("average: %llu\n", avg/10); 
	return 0;
}
