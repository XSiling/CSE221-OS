#!/bin/bash
cd /home/jieyi/Code/cpu
gcc -O0 -pthread -o procedurecallOverhead procedurecallOverhead.c -lm
ITERATION=100
for i in `seq 1 $ITERATION`
do 
	./procedurecallOverhead
done

exit


