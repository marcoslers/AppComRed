#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<pthread.h>

#define PORT 7200
#define BUFSIZE 80

int main(int argv,char *args[]){

    int sockfd,clilen,flag=1; 
    struct sockaddr_in server,client; 
    
    //domain,type,protocol
    sockfd = socket(AF_INET, SOCK_DGRAM, 0); 

    if(sockfd == -1){ 
        printf("socket creation failed...\n"); 
        exit(0); 
    }

    //habilitar reutilizacion de puerto
    if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&flag,sizeof(flag))==-1){
        printf("setsockopt failed...\n"); 
        exit(0); 
    }

    //Llena de ceros los n siguientes bytes apuntados por server
    bzero(&server, sizeof(server)); 

    //IPv4, direccion y puerto en network byte order
    server.sin_family = AF_INET;
    //Todas las interfaces locales 
    server.sin_addr.s_addr = htonl(INADDR_ANY); 
    server.sin_port = htons(PORT); 

    //Unir el socket a la IP y puerto
    if ((bind(sockfd, (struct sockaddr*)&server, sizeof(server))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    }

    clilen = sizeof(client);
    char buff[BUFSIZE];

    while(1){
        //Recepcion mensaje del cliente
        int nrecv = recvfrom(sockfd,(void*)buff,BUFSIZE,0,(struct sockaddr*)&client,&clilen);
        printf("%s\n",buff);
        bzero(buff,BUFSIZE);
        strcpy(buff,"Hola cliente");
        //Envio de mensaje al cliente
        int nsend = sendto(sockfd,(void*)buff,BUFSIZE,0,(struct sockaddr*)&client,clilen);
    }

    close(sockfd);

    return 0;
}