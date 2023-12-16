// get the peak bandwidth in a client server model

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
#define LOOP_TIME    100000
#define PACKET_SIZE     1024
#define BUFFER_SIZE     1024
#define DEST_ADDRESS    "127.0.0.1"
#define FREQUENCY 2592000000

//192.168.180.128 - vm ware
//192.168.1.36 - mac mini

int main() {
    int sock = 0;
    int total_latency = 0;
    unsigned long long a, b;
    float peakBandwidth = 0.0;
    float tmpBandwidth;
    float sum = 0.0;
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
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    // Connect
    int c = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (c < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    printf("Connectioned to server!\n");


    // Connection and out times
    char message[PACKET_SIZE] = {};
    char buffer[BUFFER_SIZE] = {};

    memset(message, 'A', strlen(message));
    double latency;

    // Send and recv
    printf("Ready to send/recv messages\n");\

    for (int i = 0; i < LOOP_TIME; i++) {
    	peakBandwidth = 0.0;
    	for (int j = 0; j<10; ++j){
	    	//printf("%d/%d\n", i, NUM_MESSAGES);
		a = rdtsc();

		if (send(sock, message, sizeof(message), 0) == -1) {
		    perror("Send failed");
		    continue;
		}

		b = rdtsc();
		tmpBandwidth = 1.0 * PACKET_SIZE/ ((b-a)*1.0/FREQUENCY)/1024/1024;
		if (tmpBandwidth > peakBandwidth){
			peakBandwidth = tmpBandwidth;
		}
        }
        sum += peakBandwidth;
    }
    printf("Send packages of size %d, loop time: %d, average peak bandwidth:%fMb/s\n", PACKET_SIZE, LOOP_TIME, sum/LOOP_TIME);
    close(sock);
    return 0;
}
