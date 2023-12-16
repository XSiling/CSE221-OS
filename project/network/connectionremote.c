// get the exact connection overhead-> setup and tear down;

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "rdtsc.h"
#include <getopt.h>


//src https://stackoverflow.com/questions/76012821/tcp-socket-round-trip-time-faster-than-network-stack-latency
#define PORT            8080
#define PACKET_SIZE     32
#define LOOP_TIME	16//for max-socket limitation not 100000
#define BUFFER_SIZE     32
#define DEST_ADDRESS    "192.168.1.36"
#define FREQUENCY 2592000000

//192.168.180.128 - vm ware
//192.168.1.36 - mac mini

int main() {
    int sock = 0;
    int total_latency = 0;
    unsigned long long a, b, a1, b1, sum, sum1;
    float peakBandwidth = 0.0;
    float tmpBandwidth;
    sum = 0;
    sum1 = 0;
    struct sockaddr_in serv_addr;
    struct in_addr dest_addr; 
    memset(&dest_addr, 0, sizeof(struct in_addr));
    inet_pton(AF_INET, DEST_ADDRESS, &dest_addr);


    serv_addr.sin_addr = dest_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);


    // Print out the options to use
    printf("Destination address is %s\n",       inet_ntoa(dest_addr));
    printf("Destination port    is %d\n",       PORT);
    

    if (sock < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    // Connect
    for (int i=0; i<LOOP_TIME; ++i){
    	sock = socket(AF_INET, SOCK_STREAM, 0);
    	a = rdtsc();
	int c = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	b = rdtsc();
	sum += (b-a);
	
	if (c < 0) {
	perror("Connection failed");
	exit(EXIT_FAILURE);
	}

	a1 = rdtsc();
	close(sock);
	b1 = rdtsc();
	
	sum1 += (b1-a1);
	//printf("%d\n", i);
    }
    printf("In a loop time of %d, average setup overhead: %f, average tear down overhead:%f\n", LOOP_TIME, sum*1.0/LOOP_TIME, sum1*1.0/LOOP_TIME);
    return 0;
}
