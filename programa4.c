#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

typedef struct data{

}data;

void * funcion(void * parametro){

   
}

int main(int argc, char *argv[]){
  
    time_t t;
    srand((unsigned) time(&t));

    int t1r,t1c,t2r,t2c,nt,rxt,r;

    if(argc!=6){
        printf("parametros incompletos\n");
        exit(0);
    }
    t1r=atoi(argv[1]);
    t1c=atoi(argv[2]);
    t2r=atoi(argv[3]);
    t2c=atoi(argv[4]);
    nt=atoi(argv[5]);

    if(nt<1 || nt>t1r){
        printf("error en el # de hilos");
        exit(0);
    }else if(t1c!=t2r){
        printf("error en la longitud de las tablas");
        exit(0);        
    }

    int **m1 = (int **)malloc(sizeof(int*)*t1r);
    int **m2 = (int **)malloc(sizeof(int*)*t2r);
    int **mr = (int **)malloc(sizeof(int*)*t1r);

    for(int i=0;i<t1r;i++){
        m1[i]=(int*)malloc(sizeof(int)*t1c);
        for(int j=0;j<t1c;j++){
            int r=rand()%6;
            m1[i][j]=r;
            //printf("%d ",m1[i][j]);
        }
        //printf("\n");
    }

    for(int i=0;i<t2r;i++){
        m2[i]=(int*)malloc(sizeof(int)*t2c);
        for(int j=0;j<t2c;j++){
            int r=rand()%6;
            m2[i][j]=r;
            //printf("%d ",m2[i][j]);
        }
        //printf("\n");
    }

    for(int i=0;i<t1r;i++){
        mr[i]=(int*)malloc(sizeof(int)*t2c);
    }  

    rxt=t1r/nt;
    r=t1r%nt;

    pthread_t *threads;

    threads = (pthread_t *)malloc(sizeof(pthread_t)*nt);

    for(int i=0;i<nt;i++){
        pthread_create(&threads[i], NULL, function,(void*)&nth[i]);
    }

    exit(0);
}
