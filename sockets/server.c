#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>

#define PORT 7200
#define MAX 80

int main(int argv,char *args[]){

    int sockfd,connfd,len; 
    struct sockaddr_in server,client; 
    
    //domain,type,protocol
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 

    if(sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    }else{
        printf("Socket successfully created..\n");
    } 

    //Llena de ceros los n siguientes bytes apuntados por server
    bzero(&server, sizeof(server)); 

    //IPv4, direccion y puerto en network byte order
    //inet_pton(AF_INET,"10.12.110.57", &(sa.sin_addr)); 

    server.sin_family = AF_INET; 
    //Todas las interfaces locales
    server.sin_addr.s_addr = htonl(INADDR_ANY); 
    server.sin_port = htons(PORT); 

    //Unir el socket a la IP y puerto
    if ((bind(sockfd, (struct sockaddr*)&server, sizeof(server))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    }else{
        printf("Socket successfully binded..\n"); 
    } 

    //Listen marca el socket como pasivo, es decir, se utilizará
    //para acpetar peticiones entrantes de conección 
    //5 es el numero maximo de peticiones pendientes 
    //que pueden formarse 
    if ((listen(sockfd, 5)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    }else{
        printf("Server listening..\n"); 
    } 

    len = sizeof(client);
    //Accept extrae la primera peticion de coneccion de la cola
    //crea un nuevo socket y retorna un filedescriptor refiriendose
    //a ese nuevo socket
    connfd = accept(sockfd,(struct sockaddr*)&client, &len);

    if(connfd<0){ 
        printf("server acccept failed...\n"); 
        exit(0); 
    }else{
        printf("server acccept the client...\n"); 
    }

    char buff[MAX]; 
    int n;
    while(1){
        bzero(buff, MAX); 

        //Leer mensaje del cliente y copiarlo en el buffer
        read(connfd, buff, sizeof(buff)); 
        
        //**
        if (strncmp("exit", buff, 4) == 0) { 
            printf("Server Exit...\n"); 
            break; 
        } 
        //**

        printf(": %s\n",buff); 
        
        //limpiar el buffer
        bzero(buff, MAX);
        
        //Leer todos los caracteres hasta encontrar un salto
        //de linea
        n=0;
        printf("\t: ");
        while((buff[n++] = getchar()) != '\n'); 
  
        // Enviar el buffer al cliente
        write(connfd, buff, sizeof(buff)); 
  
        //salir al leer la palabra exit
        if (strncmp("exit", buff, 4) == 0) { 
            printf("Server Exit...\n"); 
            break; 
        } 
    }

    close(sockfd);

    return 0;
}