#include <stdio.h> 
#include <string.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <fcntl.h>
#include <sys/stat.h>

#define SEM_NAME1 "/sem1"
#define SEM_NAME2 "/sem2"

void *func1(void *args);
void *func2(void *args);

sem_t *sem1,*sem2;

char buf[50];

int main(int argv,char*argc[]){

    pthread_t th1,th2;
    sem1=sem_open(SEM_NAME1,O_CREAT,0660,1);
    sem2=sem_open(SEM_NAME2,O_CREAT,0660,1);

    pthread_create(&th1,NULL,func1,NULL);
    pthread_create(&th2,NULL,func2,NULL);

    pthread_join(th1,NULL);
    pthread_join(th2,NULL);

    return 0; 
} 

void *func1(void *args){
    
    char str[]="func1"; 

    sem_wait(sem1);
        printf("%s\n",str);
        memcpy(buf,str,6);
        printf("%s\n",buf);
    sem_post(sem1);

    pthread_exit(0);

}


void *func2(void *args){
    char str[]="func2"; 

    sem_wait(sem2);
        printf("%s\n",str);
        memcpy(buf,str,6);
        printf("%s\n",buf);
    sem_post(sem2);

    pthread_exit(0);
}