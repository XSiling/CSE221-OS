#include <stdio.h>
#include <stdlib.h>
#include "rdtsc.h"
#include <string.h>


#define LOOP_TIME 100000
#define ARRAY_SIZE 200000

//measuring the bandwidth for the memory read time
int main(int argc, char*argv[]){
	//array initialization
	register size_t *p;
	size_t dataArray[ARRAY_SIZE];
	size_t *end;
	register size_t sum = 0;
	unsigned long long a,b;
	float clockTime, bandWidth;
	//dataArray = (size_t*) malloc(ARRAY_SIZE *sizeof(size_t));
	memset(&dataArray[0], 1, ARRAY_SIZE*sizeof(size_t));

	a = rdtsc();
	for(int i=0; i<LOOP_TIME; ++i){
		//printf("%d\n",i);
		p = dataArray;
		for (int j=0; j<(ARRAY_SIZE/128); ++j){
		//while (p <= end){
#define DOIT(i) p[i]=2;
			DOIT(0) DOIT(8) DOIT(16) DOIT(24) DOIT(32) DOIT(40)
			DOIT(48) DOIT(56) DOIT(64) DOIT(72) DOIT(80) DOIT(88)
			DOIT(96) DOIT(104) DOIT(112) DOIT(120)
			p += 128;
		}
	}
	b = rdtsc();
#undef DOIT
	//free(dataArray);
	
	clockTime = (b-a)*1.0/2592000000;
	//bandWidth = (unsigned long long)LOOP_TIME * (unsigned long long)ARRAY_SIZE / 128 * 16 * 8 / clockTime /1000000;
	
	printf("Memory Write. The total cycles:%llu, the average cycles:%llu, bandwidth:%fMB/s\n", b-a, (b-a)/LOOP_TIME, LOOP_TIME*1.0*ARRAY_SIZE/128 * 16 * 8 /clockTime/1024/1024);
	
	//the total time:%f, the bandwidth:%f\n", b-a, clockTime, bandWidth);
}
