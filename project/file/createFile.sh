#!/bin/bash

cd /home/jieyi/Code/file
gcc -o filecache filecache.c


FILE_SIZE=(256 300 400 512 600 700 800 900 1024 2048 4096 8192)

#for file_size in ${FILE_SIZE[@]}
#do
#	dd if=/dev/zero of=$file_size bs=1M count=$file_size
#done


dd if=/dev/zero of=256_0 bs=1M count=256
dd if=/dev/zero of=256_1 bs=1M count=256
dd if=/dev/zero of=256_2 bs=1M count=256
dd if=/dev/zero of=256_3 bs=1M count=256
dd if=/dev/zero of=256_4 bs=1M count=256
dd if=/dev/zero of=256_5 bs=1M count=256
dd if=/dev/zero of=256_6 bs=1M count=256
dd if=/dev/zero of=256_7 bs=1M count=256
dd if=/dev/zero of=256_8 bs=1M count=256
dd if=/dev/zero of=256_9 bs=1M count=256
