#include<stdio.h>
#include<pthread.h>

void *myfunction(void *arg){

	printf("hola");

	pthread_exit(NULL);
}

int main(){

	pthread_t thread_id;

	pthread_create(&thread_id, NULL,&myfunction,NULL);

	pthread_join(thread_id,NULL);
}