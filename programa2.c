#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#include<string.h>

struct new_var{
    int n;
    char s[1000];
};

void * function(void * parametro){
    
    struct new_var * var = (struct new_var *)parametro;

    printf("%d\n",var->n);
    printf("%s\n",var->s);

  pthread_exit(NULL);
}

int main(int argc, char *argv[]){

    int value;
 
    struct new_var *arr_newbar;

    pthread_t *threads;

    if(argc == 2){
        value = atoi(argv[1]);
    }else{
        printf("ingresar el numero de hilos\n");
        exit(0);
    }

    threads = (pthread_t *)malloc(sizeof(pthread_t *)*value);
    
    arr_newbar = (struct new_var*)malloc(sizeof(struct new_var)*value);


    char nums[1000];
    nums[0]='\0';

    for(int i=0; i<value; i++){

        arr_newbar[i].n=i;
        
        char num[20];
        sprintf(num,"%d",i);

        strcat(nums,num);

        memcpy(arr_newbar[i].s,nums,20);
        
        pthread_create(&threads[i], NULL, function,(void*)&arr_newbar[i]);
    }
     
    for(int i=0; i<value; i++){
       pthread_join(threads[i], NULL);
    }
    
    free(threads);

    exit(0);
}
