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
#define MAX 80

typedef struct{
    int id_ch;
    int id_th;
}Ntype; 

void *handler(void *args){

    int n;
    char buff[MAX]; 

    Ntype *nt = (Ntype*)args; 

    do{
        bzero(buff, MAX); 
        int nbytesr=recvfrom((*nt).id_ch,buff,sizeof(buff),0,NULL,NULL);
            
        if(strncmp("exit",buff,4)==0)break;

        printf(": %s\n",buff);



        int nbytess=sendto((*nt).id_ch,buff,sizeof(buff),0,NULL,0);

    }while(strncmp("exit",buff,4)!=0);


    close((*nt).id_ch);
    free(id_ch);
}

int main(int argv,char *args[]){

    int sockfd,connfd,len,flag=1,cont=0; 
    struct sockaddr_in server,client; 
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 

    if(sockfd == -1){ 
        printf("socket creation failed...\n"); 
        exit(0); 
    }

    if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&flag,sizeof(flag))==-1){
        printf("setsockopt failed...\n"); 
        exit(0); 
    }

    bzero(&server, sizeof(server)); 

    server.sin_family = AF_INET; 
    server.sin_addr.s_addr = htonl(INADDR_ANY); 
    server.sin_port = htons(PORT); 

    if ((bind(sockfd, (struct sockaddr*)&server, sizeof(server))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    }

    if((listen(sockfd, 3)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    }

    len = sizeof(client);


    while(1){

        cont++;

        Ntype *nt = (Ntype*)malloc(sizeof(Ntype));
        (*nt).id_ch = accept(sockfd,(struct sockaddr*)&client, &len);
        (*nt).id_th = cont;

        if((*nt).id_ch<0){ 
           printf("server acccept failed...\n"); 
           exit(0); 
        }else{
            printf("server acccept the client...\n"); 
        }

        pthread_t *thread = (pthread_t*)malloc(sizeof(pthread_t));

        pthread_create(thread, NULL,(void*)handler,(void*)nt);

        free(thread);

    }

    close(sockfd);

    return 0;
}





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

    int sockfd,connfd,len,flag=1; 
    struct sockaddr_in server,client; 
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 

    if(sockfd == -1){ 
        printf("socket creation failed...\n"); 
        exit(0); 
    }

    if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&flag,sizeof(flag))==-1){
        printf("setsockopt failed...\n"); 
        exit(0); 
    }

    bzero(&server, sizeof(server)); 

    server.sin_family = AF_INET; 
    server.sin_addr.s_addr = htonl(INADDR_ANY); 
    server.sin_port = htons(PORT); 

    if ((bind(sockfd, (struct sockaddr*)&server, sizeof(server))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    }

    if((listen(sockfd, 3)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    }

    len = sizeof(client);

    char buff[MAX]; 
    int n;
    while(1){

        connfd = accept(sockfd,(struct sockaddr*)&client, &len);

        if(connfd<0){ 
            printf("server acccept failed...\n"); 
            exit(0); 
        }else{
            printf("server acccept the client...\n"); 
        }

        do{
            bzero(buff, MAX); 
            int nbytesr=recvfrom(connfd,buff,sizeof(buff),0,NULL,NULL);
            
            if(strncmp("exit",buff,4)==0)break;

            printf(": %s\n",buff);
            bzero(buff, MAX); 
            n=0;
            printf("\t: ");
            while((buff[n++] = getchar()) != '\n'); 

            int nbytess=sendto(connfd,buff,sizeof(buff),0,NULL,0);

        }while(strncmp("exit",buff,4)!=0);

        close(connfd);
    }

    close(sockfd);

    return 0;
}