#!/bin/bash

ITERATION_TIME=100

cd /home/jieyi/Code/network

gcc -o clientlb clientlb.c
gcc -o clientremote clientremote.c

#for i in `seq 1 $ITERATION_TIME`
#do
#	./clientlb
#done


for i in `seq 1 $ITERATION_TIME`
do
	./clientremote
done
