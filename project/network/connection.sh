#!/bin/bash

ITERATION_TIME=100

cd /home/jieyi/Code/network

gcc -o connectionlocal connectionlocal.c
gcc -o connectionremote connectionremote.c

for i in `seq 1 $ITERATION_TIME`
do
	./connectionlocal
done

for i in `seq 1 $ITERATION_TIME`
do
	./connectionremote
done
