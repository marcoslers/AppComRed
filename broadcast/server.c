#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<pthread.h>
#include<arpa/inet.h>

#define PORT 7200
#define BUFSIZE 80

int main(int argv,char *args[]){

    int sockfd,flag=1,len; 
    struct sockaddr_in brcast; 
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0); 

    if(sockfd == -1){ 
        printf("socket creation failed...\n"); 
        exit(0); 
    }

    if(setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,&flag,sizeof(flag))==-1){
        printf("setsockopt failed...\n"); 
        exit(0); 
    }

    bzero(&brcast, sizeof(brcast)); 

    brcast.sin_family = AF_INET;
    brcast.sin_addr.s_addr = inet_addr("192.168.1.255"); 
    brcast.sin_port = htons(PORT); 

    len = sizeof(brcast);
    char buff[BUFSIZE];

    while(1){
        
        bzero(buff,BUFSIZE);
        strcpy(buff,"Hola broadcast");
        int nsend = sendto(sockfd,(void*)buff,BUFSIZE,0,(struct sockaddr*)&brcast,len);
    }

    close(sockfd);

    return 0;
}