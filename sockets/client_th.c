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
    int sockfd, connfd,flag=1; 
    struct sockaddr_in server, client; 
  
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    }

    if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&flag,sizeof(flag))==-1){
        printf("setsockopt failed...\n"); 
        exit(0); 
    }

    bzero(&server, sizeof(server)); 
  
    server.sin_family = AF_INET; 
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    server.sin_port = htons(PORT);     

    char buff[MAX]; 
    int n;
     

    if (connect(sockfd, (struct sockaddr*)&server, sizeof(server)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    }else{
        printf("connected to the server..\n"); 
    }

    do{
        bzero(buff, sizeof(buff)); 
        printf("\t: ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n'); 
        
        int nbytess=sendto(sockfd,buff,sizeof(buff),0,NULL,0);

        if((strncmp(buff, "exit", 4)) == 0) { 
            printf("Client Exit...\n"); 
            break; 
        } 
            
            bzero(buff, sizeof(buff));
           
        int nbytesr=recvfrom(sockfd,buff,sizeof(buff),0,NULL,NULL);
        printf(": %s\n",buff);        
            
    }while(strncmp(buff, "exit", 4) != 0);

    close(sockfd);
       
    return 0;
}