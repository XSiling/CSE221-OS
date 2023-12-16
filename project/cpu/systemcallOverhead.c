#include <stdio.h>
#include <unistd.h>
#include "rdtsc.h"
#include <sys/types.h>
#include "math.h"


#define ITERATION 100000

int main(int argc, char* argv[]){
	unsigned long long a,b,avg,std;
	unsigned long long value[ITERATION];
	std = 0;
	avg = 0;
	for (int i=0; i<ITERATION; ++i){
		a = rdtsc();
		getpid();
		b = rdtsc();
		avg += (b-a);
	}
	avg = avg/ITERATION;

	printf("average: %llu for iteration time %d\n", avg, ITERATION); 
	return 0;
}
