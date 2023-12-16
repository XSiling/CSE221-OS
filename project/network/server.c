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

#include <getopt.h>


#define PORT            8080
#define BUFFER_SIZE     1024
#define PACKET_SIZE     32

int main() {
    int     socket_fd, new_socket, rc;


    // Creating socket file descriptor
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd  == 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }


    // Set socket options with setsockopt
    int opt = 1;
    rc = setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    if (rc < 0) {
        perror("Setsockopt failed");
        exit(EXIT_FAILURE);
    }

    // Bind socket to address:port
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    rc = bind(socket_fd, (struct sockaddr *)&address, sizeof(address));
    if (rc < 0) {
        perror("Socket bind failed");
        exit(1);
    }

    printf("Listening to %s:%d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
    if (listen(socket_fd, 3)) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    while(1){
    // Accept
	int addrlen = sizeof(address);
	new_socket = accept(socket_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
	if (new_socket < 0) {
	perror("Accept failure");
	exit(EXIT_FAILURE);
	}

	// Address of connected client
	char ip_address[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(address.sin_addr), ip_address, INET_ADDRSTRLEN);
	printf("New connection from %s:%d\n", ip_address, ntohs(address.sin_port));

	// Listen and respond
	int val_read, val_send;
	char    buff[BUFFER_SIZE];
	while (1) {
		memset(buff, 0, sizeof(buff));
		val_read = read(new_socket, buff, sizeof(buff));
		if(val_read==0){
			printf("zero message\n");
			break;
		}
		if(val_read == -1) {
		    perror("Read failed");
		    exit(EXIT_FAILURE);
		}
		else if (val_read > 0) {
		    val_send = send(new_socket, buff, sizeof(buff), 0);
		    if (val_send == -1) {
			perror("Send failed");
			exit(EXIT_FAILURE);
		    }
		}

	}
    }
    close(socket_fd);
    return 0;
}
