#include <stdio.h>
#include <stdlib.h>
#include "rdtsc.h"

#define LOOP_TIME1 1000000000
#define LOOP_TIME 100000
struct node{
	size_t val;
	struct node *next;
};

int main(int argc, char *argv[]){
	size_t stride, array_size,tmp;
	struct node *array;
	struct node *toolArray;
	register struct node *p;
	unsigned long long a, b;
	
	if (argc != 2){
		printf("run as ./lat_mem_rd <stride>\n");
		return -1;
	}
	
	stride = atoi(argv[1]);
	
	for (int j=0; j<25; ++j){
		unsigned long long array_size = 1 << j;
		//array_size = array_sizes[j];
	
		if (stride > array_size){
			continue;
		}
		
		// initialization
		array = (struct node*)malloc(array_size *sizeof(struct node));
		//printf("here\n");
		for (size_t i = 0; i< array_size; ++i){

			array[i].val = i;
			//random next
			//array[i].next = &array[(i*stride%array_size + rand()%array_size * stride % array_size)%array_size];
			//sequantial next
			array[i].next = &array[(i + stride)%array_size];
		}
		
		// running
		p = array;
		a = rdtsc();
		for (size_t i = 0; i < LOOP_TIME; ++i){
			p = p->next;
			// add this line to avoid optimization
			tmp = p->val;
		}
		b = rdtsc();
		printf("The total running cycles: %llu, the average running cycles: %llu, the array_size: %llu, the stride: %zu\n", b-a, (b-a)/LOOP_TIME, array_size, stride);
		free(array);
	}
	//free(toolArray)
	return 0;
}
