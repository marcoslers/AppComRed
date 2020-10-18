#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

typedef struct matrix{
    int **m;
    int r;
    int c;
}matrix;

typedef struct package{
    matrix *m1;
    matrix *m2;
    matrix *mrx;
    int l,h;
}package;

void * function(void * parametro){

    package *pkg = (package*)parametro;

    printf("l: %d\n",pkg->l);
    printf("h: %d\n",pkg->h);

    //pkg->m1->m[0][0]=55;
    //pkg->m1->m[1][0]=65;
       
}

int main(int argc, char *argv[]){
  
    time_t t;
    srand((unsigned) time(&t));

    matrix m1;
    matrix m2;
    matrix mrx;

    int nt,rxt,r,l=0,h=0;

    if(argc!=6){
        printf("parametros incompletos\n");
        exit(0);
    }

    m1.r=atoi(argv[1]);
    m1.c=atoi(argv[2]);
    m2.r=atoi(argv[3]);
    m2.c=atoi(argv[4]);
    mrx.r=m1.r;
    mrx.c=m2.c;

    nt=atoi(argv[5]);

    if(nt<1 || nt>m1.r){
        printf("error en el # de hilos");
        exit(0);
    }else if(m1.c!=m2.r){
        printf("error en la longitud de las tablas");
        exit(0);        
    }

    m1.m = (int **)malloc(sizeof(int*)*m1.r);
    m2.m = (int **)malloc(sizeof(int*)*m2.r);
    mrx.m = (int **)malloc(sizeof(int*)*mrx.r);

    for(int i=0;i<m1.r;i++){
        m1.m[i]=(int*)malloc(sizeof(int)*m1.c);
        for(int j=0;j<m1.c;j++){
            int r=rand()%6;
            m1.m[i][j]=r;
           // printf("%d ",m1.m[i][j]);
        }
        //printf("\n");
    }

    for(int i=0;i<m2.r;i++){
        m2.m[i]=(int*)malloc(sizeof(int)*m2.c);
        for(int j=0;j<m2.c;j++){
            int r=rand()%6;
            m2.m[i][j]=r;
          //  printf("%d ",m2.m[i][j]);
        }
        //printf("\n");
    }

    for(int i=0;i<mrx.r;i++){
        mrx.m[i]=(int*)malloc(sizeof(int)*mrx.c);
    }  

    rxt=m1.r/nt;
    r=m1.r%nt;

    pthread_t *threads;

    threads = (pthread_t *)malloc(sizeof(pthread_t)*nt);

    for(int i=0;i<nt;i++){

        if(i==0){
            l=0;
            h+=(rxt+r-1);
        }else{
            l+= rxt+r;
            h+=(rxt+r-1);
        }
     
        package pck;
        pck.m1=&m1;
        pck.m2=&m2;
        pck.mrx=&mrx;
        pck.l=l;
        pck.h=h;

        printf("%d %d\n",l,h);

        //pthread_create(&threads[i], NULL, function,(void*)&pck);
    }

    for(int i=0; i<nt; i++){

        pthread_join(threads[i], NULL);
    }

    free(threads);

    exit(0);
}
