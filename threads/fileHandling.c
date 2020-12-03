#include<stdio.h>
#include<stdlib.h>

int main(int argc, char*argv[]){
	
	//open or create a file
	FILE *fp;
	fp  = fopen ("data.txt", "w");	


	/*file mode
	r	Open a file for reading. If a file is in reading mode, 
		then no data is deleted if a file is already present on a system.
	w	Open a file for writing. If a file is in writing mode, 
		then a new file is created if a file doesn't exist at all. 
		If a file is already present on a system, then all the data 
		inside the file is truncated, and it is opened for writing purposes.
	a	Open a file in append mode. If a file is in append mode, 
		then the file is opened. The content within the file doesn't change.
	r+	open for reading and writing from beginning
	w+	open for reading and writing, overwriting a file
	a+	open for reading and writing, appending to file
	*/

	//close a file
	FILE *fp;
	fp  = fopen ("data.txt", "r");
	fclose (fp)

	//writing to a file

	//fputc(char, file_pointer): It writes a character to the file pointed to by file_pointer.

	fputc(str[i], fptr);

	//fputs(str, file_pointer): It writes a string to the file pointed to by file_pointer.

	fputs("We don't need to use for loop\n", fp);
	
	//fprintf(file_pointer, str, variable_lists): It prints a string to the file pointed to by file_pointer. The string can optionally include format specifiers 
	//and a list of variables variable_lists.

	fprintf(fp, "%s %s %s %d", "We", "are", "in", 2012);	

	//fgetc(file_pointer): It returns the next character from the file pointed to by the file pointer. 
	//When the end of the file has been reached, the EOF is sent back.
	
	printf( "%c", fgetc(fichero) );

	//fgets(buffer, n, file_pointer): It reads n-1 characters from the file and stores the string 
	//in a buffer in which the NULL character '\0' is appended as the last character.
	
	if(fgets (str, 60, fp)!=NULL) {

	//fscanf(file_pointer, conversion_specifiers, variable_adresses): It is used to parse and analyze data.
	// It reads characters from the file and assigns the input to a list of variable pointers variable_adresses using conversion specifiers.
	// Keep in mind that as with scanf, fscanf stops reading a string when space or newline is encountered.

	fscanf(fp, "%s %s %s %d", str1, str2, str3, &year);


	//fread reads the whole file

	fread(str,sizeof(char),29,fp);

	/*
		size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
	
		Parameters
		ptr − This is the pointer to a block of memory with a minimum size of size*nmemb bytes.

		size − This is the size in bytes of each element to be read.

		nmemb − This is the number of elements, each one with a size of size bytes.

		stream − This is the pointer to a FILE object that specifies an input stream.
	*/
}
//https://www.guru99.com/c-file-input-output.html file handling