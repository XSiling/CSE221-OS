#include <stdio.h>
#include <unistd.h>
#include "rdtsc.h"
#include "math.h"

static int iterationTime = 100000;

int main(int argc, char* argv[]){
	// get an interations of 100 times of reading times
	unsigned long long a,b,avg,std;
	avg = 0;
	std = 0;
	for (int i=0; i<iterationTime; ++i){
		a = rdtsc();
		b = rdtsc();
		avg += (b-a);
	}
	avg = avg/(iterationTime * 2);
	
	printf("average: %llu\n", avg); 
	return 0;
}
