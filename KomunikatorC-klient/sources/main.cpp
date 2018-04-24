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

int choice = 0;

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

do {
    std::cout<<"*****MENU*****"<<'\n';
    std::cout<<"1. Rejestracja"<<'\n';
    std::cout<<"2. Logowanie"<<'\n';
    std::cout<<"0. Exit"<<'\n';


  //  std::cin.getline(buffer,1024);


		//while(strcmp(buffer, "exit") != 0){

      //std::cin.getline(buffer,1024);
      std::cin>>choice;

      if(choice==1){
        // //Wysyałnie prośby o rejsetrację do serwera
        // header headerRequest;
        // headerRequest.msgId = 1;
        // send(sock,&headerRequest,sizeof(header),0);
        //
        // //Odbiernie od serer wiadomości potwierdzającej rejestrację
        // recv( sock , buffer, 1024,0);
        // code* codeResponse = (code*) buffer;
        //
        // if(codeResponse -> codeId == 200) {
        //   registration registrationRequest;
        //
        //   std::cout << "Podaj nazwę użytkownika:" << '\n';
        //   std::cin >> registrationRequest.username;
        //   std::cout << "Podaj hasło:" << '\n';
        //   std::cin >> registrationRequest.password;
        //   send(sock,&registrationRequest,sizeof(registration),0);
        //
        //   recv( sock , buffer, 1024,0);
        //   codeResponse = (code*) buffer;
        //   if(codeResponse -> codeId == 200) {
        //     std::cout << "Zapisano" << '\n';
        //   } else {
        //     std::cout << "Nie zapisano" << '\n';
        //   }
        //
        // } else {
        //     std::cout << "nie mozesz elo 3 2 0" << '\n';
        // }
      }
      else if(choice==2){

        unsigned int msgSize = sizeof(Header) + sizeof(Login) - sizeof(char);
        void* msg = malloc(msgSize);

        if(nullptr==msg){
          return -1;
        }

        Header* createMsg =(Header*) msg;

        createMsg->msgId = 2;
        createMsg->size = sizeof(Login);

        Login login = {"justynapatryktofajn","justynapatryktofajn"};
        memcpy(createMsg->content,&login,sizeof(Login));

        send(sock,createMsg,msgSize,0);

      }
      else{

      }

			//send(sock , buffer , strlen(buffer) , 0 )
      //memset(buffer, 0, sizeof buffer);
      //std::cin.getline(buffer,1024);




			//cout<<"wartosc buffera: " << buffer[1];

  //  send(sock , hello , strlen(hello) , 0 );
   //	printf("Hello message sent\n");
    //valread = read( sock , buffer, 1024)
    //printf("%s\n",buffer );

  //}
} while (choice != 0);
    close(sock);
    return 0;
}
