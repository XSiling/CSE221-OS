#!/bin/bash

cd /home/jieyi/Code/cpu
gcc -O0 -pthread -o taskCreationThread taskCreationThread.c -lm
gcc -O0 -pthread -o taskCreationProcess taskCreationProcess.c -lm
ITERATION=100
for i in `seq 1 $ITERATION`
do 
	./taskCreationTrial.sh
done

exit
