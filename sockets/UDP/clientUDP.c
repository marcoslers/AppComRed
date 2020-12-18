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
    int sockfd, connfd,flag=1; 
    struct sockaddr_in server, client; 
  
    //domain,type,protocol
    sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    }else{
        printf("Socket successfully created..\n");    
    } 
    
    //Llena de ceros los n siguientes bytes apuntados por server
    bzero(&server, sizeof(server)); 
  
    //Configuracion del servidor
    server.sin_family = AF_INET; 
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    server.sin_port = htons(PORT); 

    //Configuracion del cliente
    bzero(&client, sizeof(client)); 
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = htonl(INADDR_ANY); 
    client.sin_port = htons(0); 

    ////Unir el socket a la IP y puerto
    if ((bind(sockfd, (struct sockaddr*)&client, sizeof(client))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    }

    char buff[BUFSIZE]; 
    
    strcpy(buff,"Hola servidor");
    //Envio de mensaje al servidor
    int nbytess=sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&server,sizeof(server));

    close(sockfd);

    return 0;
}