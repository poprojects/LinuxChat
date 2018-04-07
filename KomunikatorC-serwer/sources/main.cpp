// Server side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <thread>
#include <iostream>

#define PORT 8080

void thread_client(int new_socket,char buffer[]){
			int valread;
			while(1) {

				valread = read( new_socket , buffer, 1024);

				if(strcmp(buffer, "close") == 0){
					close(new_socket);
					break;
				}

				printf("%s\n",buffer );
				memset(buffer, 0, sizeof buffer);
			}

}

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    //char *hello = "Hello from server";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 9999) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

while(1){

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
		std::cout << new_socket << '\n';
		std::thread t(thread_client,new_socket,buffer);
		t.detach();
    //send(new_socket , hello , strlen(hello) , 0 );
    //printf("disconnected\n");

	}
    return 0;
}
