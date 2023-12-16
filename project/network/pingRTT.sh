#!/bin/bash

ITERATION_TIME=100

echo "192.168.1.36"
for i in `seq 1 $ITERATION_TIME`
do	
	echo $i
	ping -c 10 -s 32 192.168.1.36
done

echo "127.0.0.1"
for i in `seq 1 $ITERATION_TIME`
do
	echo $i
	ping -c 10 -s 32 127.0.0.1
done
