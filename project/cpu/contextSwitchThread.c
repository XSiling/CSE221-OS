#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sched.h>
#include <pthread.h>
#include "rdtsc.h"
#include "math.h"


//global variable
const int nloops = 100000;
int first_pipefd[2], second_pipefd[2];


// the second thread, in this function, the child thread will continue to try to read from the first pipe and write to the second pipe
void *subRoutine(){
	for(int i=0; i<nloops; ++i){
		read(first_pipefd[0], NULL, 0);
		write(second_pipefd[1], NULL, 0);
	}
}

// the main thread
int main(){
	pthread_t thread;
	void *status;
	unsigned long long a,b, avg, std;
	unsigned long long value[nloops];
	
	// set cpu setting
	cpu_set_t set;
	CPU_ZERO(&set);
	CPU_SET(0, &set);
	
	
	pthread_create(&thread, NULL, subRoutine, NULL);
	a = rdtsc();
	for(int i=0; i<nloops; ++i){
		write(first_pipefd[1], NULL, 0);
		read(second_pipefd[0], NULL, 0);
	}
	pthread_join(thread, &status);
	b = rdtsc();
	

        printf("The average context switch cycles for %d times is %llu\n", nloops, (b-a)/nloops);
	return 0;
}
