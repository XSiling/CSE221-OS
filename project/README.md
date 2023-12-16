## Overview

This file will show the function as well as guidance on how to run the codes. The codes are divided into four parts: CPU, Memory, Network, File System.

The base codes are mostly in C, with shell scripts to help do the repeative running. For most situations without special statements, you can run the codes by:

```
chmod +x <script>.sh
./<script>.sh
```

### CPU

#### Measurement overhead

For measurement overhead, we report the overhead of reading time by rdtsc. Which will be a basic overhead for the following evaluations.

Shell Script: cpu/measurementOverhead.sh

C Code: cpu/measurementOverhead.c

#### Procedure call overhead

For procedure call overhead, we have test the overhead of it of different parameter numbers from 0 to 7.

Shell Script: cpu/procedurecallOverhead.sh

C Code: cpu/procedurecallOverhead.c

#### System call overhead

For system call overhead, we report the cost of a minimal system call - getpid.

Shell Script: cpu/systemcallOverhead.sh

C Code: cpu/systemcallOverhead.c

#### Task creation time

For task creation time, we report the time to create and run both a process and a kernel thread, whose children are all empty functions.

Shell Script: cpu/taskCreationCompare.sh(Run this one); cpu/taskCreationTrial.sh

C Code: cpu/taskCreationProcess.c; cpu/taskCreationThread.c


#### Context switch time

For context switch time, we report the time to context switch from one process to another and from one kernel thread to another.

Shell Script: cpu/contextSwitchCompare.sh

C Code: cpu/contextSwitchProcess.c; cpu/contextSwitchThread.c

### Memory

#### RAM access time

For RAM access time, we report the back-to-back-load latency of reading RAM for differnt sizes.

Shell Script: memory/lat_mem_rd.sh

C Code: memory/lat_mem_rd.c

#### RAM bandwidth

For RAM bandwidth, we report the read and write bandwidth of an size_t array of size 200,000.

Shell Script: memory/bw_mem.sh

C Code: memory/bw_mem_rd.c; memory/bw_mem_wr.c

#### Page fault service time

For page fault service time, we report the time for faulting an entire page from disk to RAM using mmap.

Shell Script: memory/page_fault.sh

C Code: memory/page_fault.c

### Network

For network, since we use a client-server model, you have to first run the server by:

```
gcc -o <server_file> <server_file>.c
./<server_file>
```

And then run the shell script.

#### Rount trip time

For round trip time, we report the RTT of loopback as well as remote. To compare we also use ping as baseline.

Shell Script: network/pingRTT.sh(ping baseline); network/cRTT.sh(run it)

C Code: network/clientlb.c; network/clientremote.c; network/server.c

#### Peak bandwidth

For peak bandwidth, we report that in a client-server model on both loopback and remote.

Shell Script: network/peakBandwidith.sh

C Code: network/peakBandwidthl.c; network/peakBandwidthr.c; network/peakBandwidthServer.c

#### Connection overhead

For connection overhead, we report the setup and teardown overhead of TCP on both remote and loopback.

Shell Script: network/connection.sh

C Code: network/connectionlocal.c; network/connectionremote.c; network/connectionServer.c

### File System

If you want to create file of certain size, can use the file/createFile.sh.

#### File cache size

For file cache size, we report the average read I/O time for files of different sizes to check the disk cache size.

Shell Script: file/filecache.sh; 

C Code: file/filecache.c

#### File read time

For file read time, we report the performance of sequential read and random read on local disk.

Shell Script: file/readFile.sh

C Code: file/randomRead.c; file/sequantialRead.c


#### Remote file read time

For remote file read time, we report the performance of sequential read and random read on NFS.

Shell Script: file/readFile.sh

C Code: file/randomRead.c; file/sequantialRead.c

But run on the NFS.

#### Contention

For contention, we report the average sequential read I/O time for multiple processes getting access to different files.

Shell Script: file/contention.sh

C Code: file/contention.c

