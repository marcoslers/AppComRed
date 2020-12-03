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

#define SEM_PRODUCER_NAME1 "/producer1"
#define SEM_CONSUMER_NAME1 "/consumer1"
#define SEM_PRODUCER_NAME2 "/producer2"
#define SEM_CONSUMER_NAME2 "/consumer2"

#define SEM_PRODUCER_NAMEXT "/producer_ext"
#define SEM_CONSUMER_NAMEXT "/consumer_ext"

typedef struct{
    int id;
    int l;
    int h;
}pair;

sem_t *sem_prod1;
sem_t *sem_cons1;
sem_t *sem_prod2;
sem_t *sem_cons2;

sem_t *sem_prodext;
sem_t *sem_consext;

int n, critReg[2],nproducts;

void *producer(void *args){

    //Rangos a producir
    pair *pr=(pair*)args;
    int l = pr->l;
    int h = pr->h;
    int tid = pr->id;

    for(int i = l; i <=h; i++){

        sem_wait(sem_prodext);
             
            int val1,val2;
            sem_getvalue(sem_prod1,&val1);
            sem_getvalue(sem_prod2,&val2);
            
            //printf("%d %d\n",val1,val2);
            
            if(val1==1){
                sem_wait(sem_prod1);
                    critReg[0]++;
                    printf("P%d en s1 : %d\n",tid,critReg[0]);
                sem_post(sem_cons1); 
            }else{
                sem_wait(sem_prod2);
                    critReg[1]++;
                    printf("P%d en s2 : %d\n",tid,critReg[1]);
                sem_post(sem_cons2); 
            }    

        sem_post(sem_consext);  
        
    }

    //printf("P%d exit \n",tid);
    pthread_exit(NULL);
    
}

void *consumer(void *args){
    pair *pr=(pair*)args;
    int tid = pr->id;

    while(1){


        if(nproducts==n){
            //printf("C%d exit  \n",tid);
            exit(0);
        }

        sem_wait(sem_consext);

            int val1,val2;
            sem_getvalue(sem_cons1,&val1);
            sem_getvalue(sem_cons2,&val2);
            
            //printf("%d %d\n",val1,val2);

            if(val1==1){ 
                sem_wait(sem_cons1);
                    critReg[0]--;
                    printf("C%d en s1: %d\n",tid,critReg[0]);
                    nproducts++;
                sem_post(sem_prod1); 
            }else{
                sem_wait(sem_cons2);
                    critReg[1]--;
                    printf("C%d en s2: %d\n",tid,critReg[1]);
                    nproducts++;
                sem_post(sem_prod2); 
            }    

        sem_post(sem_prodext);
    }
}

int main(int argc,char *argv[]){
    
    int nprod=atoi(argv[1]);
    int ncons=atoi(argv[2]);
    n        =atoi(argv[3]);

    sem_prodext = sem_open(SEM_PRODUCER_NAMEXT, O_CREAT, S_IRUSR | S_IWUSR,2);
    sem_consext = sem_open(SEM_CONSUMER_NAMEXT, O_CREAT, S_IRUSR | S_IWUSR,0);

    sem_prod1 = sem_open(SEM_PRODUCER_NAME1, O_CREAT, S_IRUSR | S_IWUSR,1);
    sem_cons1 = sem_open(SEM_CONSUMER_NAME1, O_CREAT, S_IRUSR | S_IWUSR,0);
  
    sem_prod2 = sem_open(SEM_PRODUCER_NAME2, O_CREAT, S_IRUSR | S_IWUSR,1);
    sem_cons2 = sem_open(SEM_CONSUMER_NAME2, O_CREAT, S_IRUSR | S_IWUSR,0);

    if( sem_prodext == SEM_FAILED || sem_consext == SEM_FAILED
    ||  sem_prod1 == SEM_FAILED || sem_cons1 == SEM_FAILED
    || sem_prod2 == SEM_FAILED || sem_cons2 == SEM_FAILED){
        printf("Error al crear semaforos\n");
        exit(-1);
    }

    pthread_t *prodth,*consth;
    prodth = (pthread_t*)malloc(sizeof(pthread_t*)*nprod);
    consth = (pthread_t*)malloc(sizeof(pthread_t*)*ncons);
   
    
    pair *pairs_prod,*pairs_cons;
    pairs_prod = (pair*)malloc(sizeof(pair)*nprod);
    pairs_cons = (pair*)malloc(sizeof(pair)*ncons);

    //Num de elementos a producir por hilo
    int c=n/nprod,r=n%nprod,l=0,h=0;

    //Crear hilos productores y consumidores
    for(int i=0;i<nprod;i++){;
        if(i==0){
            l=1;
            h+=(c+r);
        }else{
            l=h+1;
            h+=c;
        }
        pairs_prod[i].l=l;
        pairs_prod[i].h=h;
        pairs_prod[i].id=i+1;

        pthread_create(&prodth[i], NULL,(void*)producer,(void*)&pairs_prod[i]);
    }

    for(int i=0;i<ncons;i++){
        pairs_cons[i].id=i+1;
        pthread_create(&consth[i],NULL,(void*)consumer,(void*)&pairs_cons[i]);
    }

    //Esperar hilos productores y consumidores
    for(int i=0;i<nprod;i++){
        pthread_join(prodth[i],NULL);   
    } 

    for(int i=0;i<ncons;i++){
        pthread_join(consth[i],NULL);
    }

    sem_close(sem_prodext);
    sem_close(sem_consext);
    sem_close(sem_prod1);
    sem_close(sem_cons1);
    sem_close(sem_prod2);
    sem_close(sem_cons2);

    return 0;
}