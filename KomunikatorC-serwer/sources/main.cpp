// Server side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <thread>
#include <iostream>
#include <fstream>
#define PORT 8080

struct Header{
	int msgId;
	int size;
	unsigned int content[1];
};

struct code{
  int codeId;
};

struct registration{
  char username[20];
  char password[20];
};

struct Login{
  char username[20];
  char password[20];
};

void thread_client(int socket){

			while(1) {

				char buffer[1024];

				unsigned int headerSize = sizeof(Header);

				int countReceiveChar = 0;

				int result = 0;

				while(countReceiveChar < headerSize) {
					result = recv( socket ,buffer + countReceiveChar,headerSize-countReceiveChar,0);
					if( result == -1){
						break;
					} else {
						 countReceiveChar += result;
					}
				}

				Header* headerRequest = (Header*) buffer;

				if(headerRequest->msgId == 1){
					// code codeResponse;
          //
					// codeResponse.codeId = 200;
					// send(socket,&codeResponse,sizeof(code),0);
          //
					// recv( socket , buffer, 1024,0);
					// registration* registrationRequest = (registration*) buffer;
          //
					// //zapis do pliku
					// std::ofstream fileUsers;
					// fileUsers.open("../users.txt", std::ios_base::app);
					// fileUsers<<registrationRequest->username<<":"<<registrationRequest->password<<'\n';
					// fileUsers.close();
          //
					// codeResponse.codeId = 200;
					// send(socket,&codeResponse,sizeof(code),0);

				}
				else if(headerRequest->msgId == 2){

					unsigned int toRecive = headerRequest->size - sizeof(unsigned int);
					std::cout << toRecive << '\n';

					int countReceiveCharLogin = 0;

					while(countReceiveCharLogin < toRecive) {
						result = recv( socket ,buffer + countReceiveChar + countReceiveCharLogin,toRecive-countReceiveCharLogin,0);
						if( result == -1){
							break;
						} else {
							 countReceiveCharLogin += result;
						}
					}

					Header* loginRequest = (Header*) buffer;

					//result = recv( socket ,(char*) loginRequest,loginSize,0);
					//std::cout << "result: " << result << '\n';
					//std::cout << loginRequest->password<< '\n';
					//int result = recv(socket, recv_buffer + recv_len, BUF_SIZE - recv_len, 0);

					 std::cout << ((Login*) loginRequest->content)->username << '\n';
					// std::cout << ((Login*) loginRequest->content)->password << '\n';
					std::cout<<"header request: " <<headerRequest->size<<'\n';
				}
				else {
					close(socket);
					break;
				}

			}
}

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

		//tworzenie pliku
		std::ifstream ifile("../users.txt");
		if(ifile.good() == false) {
			std::ofstream fileUsers("../users.txt");
			fileUsers.close();
		}

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

		std::thread t(thread_client,new_socket);
		t.detach();
    //send(new_socket , hello , strlen(hello) , 0 );
    //printf("disconnected\n");

	}
    return 0;
}
