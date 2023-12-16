#!/bin/bash

cd /home/jieyi/Code/cpu
rm taskCreationResult.txt
ITERATION=100000

processTime=0
threadTime=0

for i in `seq 1 $ITERATION`
do 
	./taskCreationProcess
	./taskCreationThread
done

# get the average value

for line in `cat taskCreationResult.txt`
do 
	OLD_IFS=$IFS
	IFS=':'
	arr=($line)

	if [ ${arr[0]} == "process" ];then
		processTime=$[$processTime + ${arr[1]}]
	fi
	
	if [ ${arr[0]} == "thread" ];then
		threadTime=$[$threadTime + ${arr[1]}]
	fi
	IFS=$OLD_IFS
done

echo "thread average"
echo $[$threadTime/$ITERATION]

echo "process average"
echo $[$processTime/$ITERATION]


