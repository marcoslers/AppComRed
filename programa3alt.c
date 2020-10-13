#include <stdio.h>
#include <stdlib.h> //exit(0)
#include <pthread.h>
#include <string.h>

void * function(void * parametro){
    
    int *val = (int*)parametro,n;

    n=*val;

    int prev[2];

    prev[0]=0;
    prev[1]=1;

    char str[n+2];

    str[0]='0';
    str[1]='1';
    str[2]='\0';

    if(n==0) printf("0  :  0\n");
    else if(n==1) printf("1 :  01\n");
    else{

        char num[100];
        for(int i=2;i<=(n+1);i++){
            int r;
            r=prev[1]+prev[0];

            sprintf(num,"%d",r);

            strcat(str,num);  

            prev[0]=prev[1];
            prev[1]=r;
        }
        printf("%d :  %s\n",n,str);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){

    int nth[argc-1];

    for(int i=1,j=0;i<(argc);i++,j++){
        nth[j]=atoi(argv[i]);
    }

    pthread_t *threads;

    threads = (pthread_t *)malloc(sizeof(pthread_t *)*(argc-1));


    for(int i=0;i<(argc-1);i++){
        pthread_create(&threads[i], NULL, function,(void*)&nth[i]);
    }

    for(int i=0; i<(argc-1); i++){

        pthread_join(threads[i], NULL);
    }
    
    free(threads);

    exit(0);
}
