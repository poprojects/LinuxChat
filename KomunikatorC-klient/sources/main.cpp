// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
 #include <arpa/inet.h>
 #include <unistd.h>
 #include <iostream>
#define PORT 8080

using namespace std;

struct header{
  int msgId;
};

struct login{
  char username[20];
  char password[20];
};

int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
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

    header msg;

    msg.msgId = 0x1;

    std::cout << sock << '\n';

    std::cin.getline(buffer,1024);

		while(strcmp(buffer, "exit") != 0){
      std::cin.getline(buffer,1024);
      send(sock,&msg,sizeof(header),0);
			//send(sock , buffer , strlen(buffer) , 0 )
      //memset(buffer, 0, sizeof buffer);
      //std::cin.getline(buffer,1024);
      recv( sock , buffer, 1024,0);

      header* msgresponse = (header*) buffer;

      if(msgresponse -> msgId == 1) {
        std::cout << "mozesz wprowadzic dane" << '\n';
      } else {
        std::cout << "nie mozesz elo 3 2 0" << '\n';
      }


			//cout<<"wartosc buffera: " << buffer[1];

  //  send(sock , hello , strlen(hello) , 0 );
   //	printf("Hello message sent\n");
    //valread = read( sock , buffer, 1024);
    //printf("%s\n",buffer );

  }
    close(sock);
    return 0;
}
