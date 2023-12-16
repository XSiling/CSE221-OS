#!/bin/bash
cd /home/jieyi/Code/cpu
gcc -O0 -pthread -o contextSwitchProcess contextSwitchProcess.c -lm
gcc -O0 -pthread -o contextSwitchThread contextSwitchThread.c -lm


ITERATION=100
for i in `seq 1 $ITERATION`
do 
	./contextSwitchProcess
	./contextSwitchThread
done

exit
