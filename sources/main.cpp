#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8000

int main(int argc, char* argv[])
{

	int server_fd;
	int opt = 1;
	struct sockaddr_in address;
	 int addrlen = sizeof(address);
	int valread;
	int new_socket;
	char buffer[1024] = {0};
	char *hello = "It's sever here!"
//tworzenie soketu i przypisanie go do server_fd
		if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        return 100;
    }
//SOL_SOCKET - protokół socketu
		if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)))
	 {
			 return 101;
	 }

	  address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

		if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        return 102;
    }
		if (listen(server_fd, 99999) < 0)
		{
			  return 103;
		}
		if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
											(socklen_t*)&addrlen))<0)
	 {
			 return 104;
	 }
//-----------------------------------------------------------------------------
	 if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("\n Socket creation error \n");
		return -1;
}

memset(&serv_addr, '0', sizeof(serv_addr));

serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(PORT);

// Convert IPv4 and IPv6 addresses from text to binary form
if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
}

if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
{
		printf("\nConnection Failed \n");
		return -1;
}
send(sock , hello , strlen(hello) , 0 );
printf("Hello message sent\n");
valread = read( sock , buffer, 1024);
printf("%s\n",buffer );
return 0;

	 valread = read( new_socket , buffer, 1024);
	 printf("%s\n",buffer );
	 send(new_socket , hello , strlen(hello) , 0 );
	 printf("Hello world!\n");


	return 0;
}
