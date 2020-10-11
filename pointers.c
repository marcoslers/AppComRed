#include<stdio.h>
#include<stdlib.h>

void myfunction(void *arg){


    int *p=(int*)arg;

	printf("%d",*p);

}

int suma(int x,int y){
    return x+y;
}


int prom(int (*ptr2func)(int, int),int p){

    return ((*ptr2func)(6,7))*p;

}

int main(){

    int x=5;
    //myfunction(&x); 

    int *ptr,**ptr2;
    
    ptr=&x;
    ptr2=&ptr;

    printf("%p\n",&x); //impresion direccion de x
    printf("%p\n",ptr); //impresion de la direccion de x
    printf("%p\n",&ptr);//impresion de la direccion de ptr
    printf("%d\n",*ptr);//impresion valor del valor de x

    printf("%p\n",ptr2);//imprimir la direccion de ptr
    printf("%p\n",*ptr2);//imprime la direccion de x
    printf("%d\n",**ptr2);//imprime el valor de x
}