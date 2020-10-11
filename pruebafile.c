#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[]){
	FILE *fp;

	char str[30];

	fp=fopen("data.txt","r");

	fread(str,sizeof(char),29,fp);
	
	printf("%s\n",str);

	fclose(fp);
}