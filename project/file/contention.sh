#!/bin/bash

hdparm -W 0 /dev/sda

cd home/jieyi/Code/file

gcc -o contention contention.c

ITERATION_TIME=100
PROCESS_NUM=(2 3 4 5 6 7 8 9 10)

for i in `seq 1 $ITERATION_TIME`
do
	for j in ${PROCESS_NUM[@]}
	do
		./contention $j 
		sleep 5
	done
done
