#include<stdio.h>

#define MSGLEN 1500

typedef struct{
    int id;
    char msg[MSGLEN];
}Package; 

int main(int argv,char*args[]){

    Package pkg;
    printf("%d",sizeof(pkg));
    
    char buff[MSGLEN]; 

    FILE *fp,*fpw;

    fp = fopen("img.png","rb");
    fpw = fopen("img1.png", "a+");

    if(fp==NULL){
        printf("error opening the file");
        //exit(0);
    } 

    while(fread(buff,sizeof(char),MSGLEN,fp)>0){
        fwrite(buff,sizeof(char), MSGLEN,fpw);
    }

    fclose(fp);
    fclose(fpw);

    return 0;*/

}