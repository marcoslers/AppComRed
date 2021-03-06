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
#define BUFSIZE 80

int main(int argv,char *args[]){
    int sockfd, flag=1; 
    struct sockaddr_in client; 
  
    sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    }

    if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEPORT,&flag,sizeof(flag))==-1){
        printf("setsockopt failed...\n"); 
        exit(0); 
    }
    
    bzero(&client, sizeof(client)); 
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = htonl(INADDR_ANY); 
    client.sin_port = htons(PORT); 

    if ((bind(sockfd, (struct sockaddr*)&client, sizeof(client))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    }

    char buff[BUFSIZE]; 
    while(1){
        bzero(buff, BUFSIZE);     
        int nrecv = recvfrom(sockfd,(void*)buff,BUFSIZE,0,NULL,0);
        printf("%s\n",buff);
    }   

    close(sockfd);

    return 0;
}