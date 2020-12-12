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
#define MSGLEN 1500

typedef struct{
    int id;
    char msg[MSGLEN];
}Package; 

void sendMsg(int sockfd){

    int idMsg = 0;

    FILE *fp;
    fp = fopen("img.png","rb");

    if(fp==NULL){
        printf("error opening the file");
        exit(0);
    } 

    Package pkg;

    while(fread(pkg.msg,sizeof(char),MSGLEN,fp)>0){

        pkg.id=idMsg++;
        int nbytess=sendto(sockfd,&pkg,sizeof(Package),0,NULL,0);
            
        bzero(pkg.msg,MSGLEN); 

        int nbytesr=recvfrom(sockfd,&pkg,sizeof(Package),0,NULL,NULL);

        if(pkg.id!=idMsg){
            printf("error sending package\n");
            exit(0);
        }

        bzero(pkg.msg,MSGLEN);
    }

    pkg.id=-1;
    int nbytess=sendto(sockfd,&pkg,sizeof(Package),0,NULL,0);

    printf("image completed\n");

    fclose(fp);

}

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
    
    if (connect(sockfd, (struct sockaddr*)&server, sizeof(server)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    }else{
        printf("connected to the server..\n"); 
    }

    sendMsg(sockfd);

    close(sockfd);
       
    return 0;
}