#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include <arpa/inet.h>

#define PORT 7200
#define MAX 80

int main(int argv,char *args[]){
    int sockfd, connfd; 
    struct sockaddr_in server, client; 
  
    //domain,type,protocol
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    }else{
        printf("Socket successfully created..\n");    
    } 

    bzero(&server, sizeof(server)); 
  
    //IPv4, direccion y puerto en network byte order
    server.sin_family = AF_INET; 
    //localhost
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    server.sin_port = htons(PORT); 

    // Conectar al socket del servidor
    if (connect(sockfd, (struct sockaddr*)&server, sizeof(server)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    }else{
        printf("connected to the server..\n"); 
    } 

    char buff[MAX]; 
    int n;
    while(1){ 

        bzero(buff, sizeof(buff)); 
        printf("\t: ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n'); 
        
        write(sockfd, buff, sizeof(buff));

        //**
        if((strncmp(buff, "exit", 4)) == 0) { 
            printf("Client Exit...\n"); 
            break; 
        } 
        //**
    
        bzero(buff, sizeof(buff));
        
        read(sockfd, buff, sizeof(buff));  
        printf(": %s\n",buff);
        
        if((strncmp(buff, "exit", 4)) == 0) { 
            printf("Client Exit...\n"); 
            break; 
        } 
    } 

    close(sockfd);

    return 0;
}