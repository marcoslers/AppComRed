#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/shm.h>
#include<sys/ipc.h>

#define SEM_PRODUCER_NAME "/myproducer"
#define SEM_CONSUMER_NAME "/myconsumer"

typedef struct{
    int l;
    int h;
}pair;

sem_t *sem_prod;
sem_t *sem_cons;

int varCrit,n;

void *producer(void *args){

  pair *pr=(pair*)args;
  int l = pr->l;
  int h = pr->h;

  for (int i = l; i <=h; i++){
    sem_wait(sem_prod);
    varCrit=i;
    printf("produciendo: %d\n",varCrit);
    sem_post(sem_cons);
  } 
}

void *consumer(void *args){
  for (int i = 1; i <= n; i++){
    sem_wait(sem_cons);
    printf("consumiendo: %d\n",varCrit);
    sem_post(sem_prod);
  }
}


int main(int argc,char  *argv[]){

  int nprod=atoi(argv[1]);
  int ncons=atoi(argv[2]);
  n        =atoi(argv[3]);

  sem_prod = sem_open(SEM_PRODUCER_NAME, O_CREAT, S_IRUSR | S_IWUSR,1);
  sem_cons = sem_open(SEM_CONSUMER_NAME, O_CREAT, S_IRUSR | S_IWUSR,0);
  

  if(sem_prod == SEM_FAILED){
    printf("Error al crear el semáforo\n");
    exit(-1);
  }

  if (sem_cons  == SEM_FAILED){
    printf("Error al crear el semáforo\n");
    exit(-1);
  }

  pthread_t *prodth,*consth;
  prodth = (pthread_t*)malloc(sizeof(pthread_t*)*nprod);
  consth = (pthread_t*)malloc(sizeof(pthread_t*)*ncons);

  pair * pairs;
  pairs = (pair*)malloc(sizeof(pair)*nprod);

  int c=n/nprod,r=n%nprod,l=0,h=0;

  for(int i=0;i<nprod;i++){
    if(i==0){
      l=1;
      h+=(c+r);
    }else{
      l=h+1;
      h+=c;
    }
    pairs[i].l=l;
    pairs[i].h=h;
    pthread_create(&prodth[i], NULL,(void*)producer,(void*)&pairs[i]);
  }
  
  for(int i=0;i<ncons;i++){
    pthread_create(&consth[i],NULL,(void*)consumer,NULL);
  }

  for(int i=0;i<nprod;i++){
    pthread_join(prodth[i],NULL);   
  } 
    
  for(int i=0;i<ncons;i++){
    pthread_join(consth[i],NULL);
  }

  sem_close(sem_prod);
  sem_close(sem_cons);
  

  return 0;
}

