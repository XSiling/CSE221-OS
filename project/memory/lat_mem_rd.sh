#!/bin/bash

cd /home/jieyi/Code/memory
gcc -o lat_mem_rd lat_mem_rd.c

ITERATION=100
STRIDE_ARRAY=(16 32 64 128 256)
for i in `seq 1 $ITERATION`
do
	for stride in "${STRIDE_ARRAY[@]}"
	do
		./lat_mem_rd $stride
	done
done

exit
