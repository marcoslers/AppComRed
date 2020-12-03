#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void * function(void * parametro){
  int variable = *((int*)parametro);
  printf("hola Mundo desde el hilo: %d\n", variable);
  pthread_exit(NULL);
}

int main(int argc, char *argv[]){

    int value, *values;

    pthread_t *threads;

    if(argc == 2){
        value = atoi(argv[1]);
    }else{
        printf("ingresar el numero de hilos\n");
        exit(0);
    }

    threads = (pthread_t *)malloc(sizeof(pthread_t *)*value);
    values = (int *)malloc(sizeof(int)*value);
    
    //for(int i=0;i<value;i++) values[i]=i;
    
    for(int i=0; i<value; i++){
        values[i]=i;
        pthread_create(&threads[i], NULL, function,(void*)&values[i]);
    }
     
    for(int i=0; i<value; i++){
       pthread_join(threads[i], NULL);
    }
    
    free(threads);

    exit(0);
}

