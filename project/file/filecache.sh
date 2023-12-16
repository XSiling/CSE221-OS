#!/bin/bash

cd /home/jieyi/Code/file
gcc -o filecache filecache.c

ITERATION_TIME=100

FILE_SIZE=(256 512 1024 2048 4096 8192)

for i in `seq 1 $ITERATION_TIME`
do
	for file_size in ${FILE_SIZE[@]}
	do
		#dd if=/dev/zero of=$file_size bs=1M count=$file_size
		./filecache $file_size $file_size
		#rm $file_size
	done
done
