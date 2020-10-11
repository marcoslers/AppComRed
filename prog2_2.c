#include <stdio.h>
#include <stdlib.h> //exit(0)
#include <pthread.h>
#include <string.h>

typedef struct package{
    int n;
    char *s;
}package;

void * function(void * parametro){
    
    package *pck = (package*)parametro;

    printf("ci: %d\n",pck->n);
    printf("cs: %s\n",pck->s);

    pthread_exit((void*)pck);
}

int main(int argc, char *argv[]){

    int value;

    if(argc == 2){
        value = atoi(argv[1]);
    }else{
        printf("ingresar el numero de hilos\n");
        exit(0);
    }

    pthread_t *threads;
    package *p_arr;

    threads = (pthread_t *)malloc(sizeof(pthread_t *)*value);
    p_arr = (package *)malloc(sizeof(package)*value);

    char *str;

    str=(char*)malloc(sizeof(char)*20);
    str[0]='\0';

    char num[100];

    int s_str=20;

    for(int i=0;i<value;i++){

        sprintf(num,"%d",i); 

        if(strlen(str)>(s_str/2)) {
            s_str*=2;
            str=(char*)realloc(str,s_str);
        }
        strcat(str,num);  

        p_arr[i].n=i;
        p_arr[i].s = (char*)malloc(sizeof(char)*(strlen(str)+1));

        memcpy(p_arr[i].s,str,strlen(str));
        
        pthread_create(&threads[i], NULL, function,(void*)&p_arr[i]);

    }

    for(int i=0; i<value; i++){

        package *retval;
        pthread_join(threads[i], (void*)&retval);

        printf("pi: %d\n",(*retval).n);    
        printf("ps: %s\n",(*retval).s);

    }
    
    free(threads);

    exit(0);
}
