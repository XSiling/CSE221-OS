#include <stdio.h>
#include <unistd.h>
#include "rdtsc.h"
#include "math.h"
//#define MAX_INT 2147483646
#define MAX_INT 100000
#pragma OPTIMIZE OFF

static __attribute__ ((noinline)) void testFunction0(){asm volatile("");}

static __attribute__ ((noinline)) void testFunction1(unsigned long long int arg1){asm volatile("");}

static __attribute__ ((noinline)) void testFunction2(unsigned long long int arg1, unsigned long long int arg2){asm volatile("");}

static __attribute__ ((noinline)) void testFunction3(unsigned long long int arg1, unsigned long long int arg2, unsigned long long int arg3){asm volatile("");}

static __attribute__ ((noinline)) void testFunction4(unsigned long long int arg1, unsigned long long int arg2, unsigned long long int arg3, unsigned long long int arg4){asm volatile("");}

static __attribute__ ((noinline)) void testFunction5(unsigned long long int arg1, unsigned long long int arg2, unsigned long long int arg3, unsigned long long int arg4, unsigned long long int arg5){asm volatile("");}

static __attribute__ ((noinline)) void testFunction6(unsigned long long int arg1, unsigned long long int arg2, unsigned long long int arg3, unsigned long long int arg4, unsigned long long int arg5, unsigned long long int arg6){asm volatile("");}

static __attribute__ ((noinline)) void testFunction7(unsigned long long int arg1, unsigned long long int arg2, unsigned long long int arg3, unsigned long long int arg4, unsigned long long int arg5, unsigned long long int arg6, unsigned long long int arg7){asm volatile("");}

int main(int argc, char* argv[]){
	unsigned long long a,b;
	int iterationTime = MAX_INT;
	unsigned long long tmp;
	volatile unsigned long long int param = 12345678;
	unsigned long long int value[iterationTime];
	
	// param0
	a = rdtsc();
	for(int i=0; i<iterationTime; ++i){
		a = rdtsc();
		testFunction0();
		b = rdtsc();
	}
	b = rdtsc();
	printf("param0:%llu\n", (b-a)/iterationTime);
	
	// param1
	a = rdtsc();
	for(int i=0; i<iterationTime; ++i){
		testFunction1(param);
	}
	b = rdtsc();
	printf("param1:%llu\n", (b-a)/iterationTime);
	// param2
	a = rdtsc();
	for(int i=0; i<iterationTime; ++i){
		testFunction2(param, param);
	}
	b = rdtsc();
	printf("param2:%llu\n", (b-a)/iterationTime);
	// param3
	a = rdtsc();
	for(int i=0; i<iterationTime; ++i){
		testFunction3(param, param, param);
	}
	b = rdtsc();
	printf("param3:%llu\n", (b-a)/iterationTime);
	
	// param4
	a = rdtsc();
	for(int i=0; i<iterationTime; ++i){
		testFunction4(param, param, param, param);
	}
	b = rdtsc();
	printf("param4:%llu\n", (b-a)/iterationTime);
	// param5
	a = rdtsc();
	for(int i=0; i<iterationTime; ++i){
		testFunction5(param, param, param, param, param);
	}
	b = rdtsc();
	printf("param5:%llu\n", (b-a)/iterationTime);
	
	// param6
	a = rdtsc();
	for(int i=0; i<iterationTime; ++i){
		testFunction6(param, param, param, param, param, param);
	}
	b = rdtsc();
	printf("param6:%llu\n", (b-a)/iterationTime);
	
	// param7
	a = rdtsc();
	for(int i=0; i<iterationTime; ++i){
		testFunction7(param, param, param, param, param, param, param);
	}
	b = rdtsc();
	printf("param7:%llu\n", (b-a)/iterationTime);
	
	
	
	
}


