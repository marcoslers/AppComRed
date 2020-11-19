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

#define SEM_PRODUCER_NAME1 "/myproducer1"
#define SEM_CONSUMER_NAME1 "/myconsumer1"
#define SEM_PRODUCER_NAME2 "/myproducer2"
#define SEM_CONSUMER_NAME2 "/myconsumer2"

#define SEM_NPRODUCTS      "/nproducts"

typedef struct{
    int id;
    int l;
    int h;
}pair;

sem_t *sem_prod1;
sem_t *sem_cons1;
sem_t *sem_prod2;
sem_t *sem_cons2;

sem_t *sem_nprod;

int varCrit[2],n,nproducts;

void *producer(void *args){

    //Rangos a producir
    pair *pr=(pair*)args;
    int l = pr->l;
    int h = pr->h;
    int tid = pr->id;

    for(int i = l; i <=h; i++){
        //Vamos a crear un ciclo para recorrer las secciones criticas
        for(int j=0;j<2;j++){
                
            if(j==0){
                //Esta parte es la sincronizacion de la seccion critica 1
                sem_wait(sem_prod1);
                    varCrit[j]++;//<-esto representa la seccion critica 1
                    printf("P%d produciendo en seccion 1 : %d\n",tid,varCrit[j]);
                sem_post(sem_cons1); 

            }else{
                //Esta parte es la sincronizacion de la seccion critica 2
                sem_wait(sem_prod2);
                    varCrit[j]++;//<-esto representa la seccion critica 2
                    printf("P%d produciendo en seccion 2 : %d\n",tid,varCrit[j]);
                sem_post(sem_cons2); 
            }
      
        }       
    } 

    printf("P%d exit \n",tid);
    pthread_exit(NULL);

}

void *consumer(void *args){

    pair *pr=(pair*)args;
    int tid = pr->id;

    while(1){
        for(int j=0;j<2;j++){  
            if(nproducts==(n*2)){
                printf("C%d exit  \n",tid);
                exit(0);
            }
            if(j==0){
                sem_wait(sem_cons1);
                    varCrit[j]--;
                    printf("C%d consumiendo en seccion 1: %d\n",tid,varCrit[j]);
                    nproducts++;
                sem_post(sem_prod1);
            }else{
                sem_wait(sem_cons2);
                    varCrit[j]--;
                    printf("C%d consumiendo en seccion 2: %d\n",tid,varCrit[j]);
                    nproducts++;
                sem_post(sem_prod2); 
            }
        }
    }
}


int main(int argc,char  *argv[]){

    int nprod=atoi(argv[1]);
    int ncons=atoi(argv[2]);
    n        =atoi(argv[3]);

    /*Estos dos sem son para la primera seccion critica*/

    sem_prod1 = sem_open(SEM_PRODUCER_NAME1, O_CREAT, S_IRUSR | S_IWUSR,1);
    sem_cons1 = sem_open(SEM_CONSUMER_NAME1, O_CREAT, S_IRUSR | S_IWUSR,0);
  
    /*Estos dos sem son para la segunda seccion critica*/

    sem_prod2 = sem_open(SEM_PRODUCER_NAME2, O_CREAT, S_IRUSR | S_IWUSR,1);
    sem_cons2 = sem_open(SEM_CONSUMER_NAME2, O_CREAT, S_IRUSR | S_IWUSR,0);

    sem_nprod = sem_open(SEM_NPRODUCTS     , O_CREAT, S_IRUSR | S_IWUSR,1);

    if(sem_prod1 == SEM_FAILED || sem_cons1 == SEM_FAILED){
        printf("Error al crear semaforos region critica 1\n");
        exit(-1);
    }

    if(sem_prod2 == SEM_FAILED || sem_cons2 == SEM_FAILED){
        printf("Error al crear semaforos region critica 2\n");
        exit(-1);
    }

    pthread_t *prodth,*consth;
    prodth = (pthread_t*)malloc(sizeof(pthread_t*)*nprod);
    consth = (pthread_t*)malloc(sizeof(pthread_t*)*ncons);

    pair *pairs, *pairs1;
    pairs = (pair*)malloc(sizeof(pair)*nprod);
    pairs1 = (pair*)malloc(sizeof(pair)*ncons);

    //Parametros para definir el numero de elementos a producir por cada productor
    int c=n/nprod,r=n%nprod,l=0,h=0;

    //Creacion hilos productor

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
        pairs[i].id=i+1;
        pthread_create(&prodth[i], NULL,(void*)producer,(void*)&pairs[i]);
    }

  
    //Creacion hilos consumidor
    for(int i=0;i<ncons;i++){
        pairs1[i].id=i+1;
        pthread_create(&consth[i],NULL,(void*)consumer,(void*)&pairs1[i]);
    }

    for(int i=0;i<nprod;i++){
        pthread_join(prodth[i],NULL);   
    } 
    
    for(int i=0;i<ncons;i++){
        pthread_join(consth[i],NULL);
    }

    sem_close(sem_prod1);
    sem_close(sem_cons1);
    sem_close(sem_prod2);
    sem_close(sem_cons2);


    return 0;
}