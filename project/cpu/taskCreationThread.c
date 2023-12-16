#include <stdio.h>
#include <unistd.h>
#include "rdtsc.h"
#include <pthread.h>

void *testCode(){
	//return 0;
}

int main(int argc, char* argv[]){
	unsigned long long a,b;
	FILE *fptr;
	pthread_t thread;
	void *status;
	
	// create a thread
	a = rdtsc();
	pthread_create(&thread, NULL, testCode, NULL);
	pthread_join(thread, &status);
	b = rdtsc();
	//printf("thread cycles: %llu\n", b-a);
	fptr = fopen("/home/jieyi/Code/cpu/taskCreationResult.txt", "a");
	fprintf(fptr, "thread:");
	fprintf(fptr, "%llu", b-a);
	fprintf(fptr, "\n");
	return 0;
}
