#!/bin/bash

cd /home/jieyi/Code/memory

gcc -o page_fault page_fault.c

ITERATION=100
# we cannnot do it like this!

for i in `seq 1 $ITERATION`
do
	./page_fault
done
