#!/bin/bash

cd /home/jieyi/Code/memory
gcc -O0 -o bw_mem_rd bw_mem_rd.c
gcc -O0 -o bw_mem_wr bw_mem_wr.c


ITERATION=100
for i in `seq 1 $ITERATION`
do
	./bw_mem_rd 
done


for i in `seq 1 $ITERATION`
do
	./bw_mem_wr
done
exit
