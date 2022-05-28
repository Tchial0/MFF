/* 
 * Manix File Fragmenter (MFF)
 * File: libmff.c
 * Description: MFF library
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include "mff.h"


/* Check if a file exists*/
int fexists(const char * fname){
	int fd = open(fname,O_RDONLY);
	close(fd);
	return (fd > 0);
}

/* Returns the size of a file*/
fsize_t fbytes(const char * name){
    FILE * fp = fopen(name,"rb");
    if(fp == NULL) return 0;
	fsize_t size = 0;
	while(getc(fp) != EOF){
		size++;
	}
	fclose(fp);
	return size;
}

/*
 Fragments the file which path is 'file_name', dividing it in small pieces of size 'frag_size'.
 Returns 0 for failure, other for success.  
 */
int frag_file(const char * file_name, size_t frag_size){
    FILE * fp = fopen(file_name,"rb");
	
	if(fp == NULL) return 0;
	
	int count = 1;
	size_t pos = 0;
	char frag_name[100];
	char dir_name[100];
	
	strcpy(dir_name,file_name);
	strcat(dir_name," [Frags]\\");
	mkdir(dir_name);
	
	strcpy(frag_name,dir_name);
	strcat(frag_name,"frag_1");
	FILE * frag = fopen(frag_name,"wb");
  
	if(frag  == NULL) return 0;
	
	int byte;
	while((byte = getc(fp)) != EOF){
		putc(byte,frag);
		if(++pos == frag_size){
			count++;
			pos = 0;
			fflush(frag);
		    fclose(frag);
			strcpy(frag_name,dir_name);
			strcat(frag_name,"frag_");
			strcat(frag_name,itoa(count,(char *) malloc(100),10));
			frag = fopen(frag_name,"wb");
		}
	}
	fclose(fp);
	fflush(frag);
	fclose(frag);
	return 1;
}

/*
 Gathers all the pieces in the current directory into 'file_name'
 Returns 0 for failure, other for success.  
 */
int defrag_file(const char * file_name){
    FILE * fp = fopen(file_name,"wb");
    if(fp == NULL) return 0;

   	size_t count = 1;
	char frag_name[100] = "frag_1";
	FILE * frag;
	
	while((frag = fopen(frag_name,"rb")) != NULL){
		int byte;
		while((byte = getc(frag)) != EOF){
			putc(byte,fp);
		}
		fflush(frag);
		fclose(frag);
		count++;
		strcpy(frag_name,"frag_");
		strcat(frag_name,ltoa(count,(char*)malloc(100),10));
	}
    fflush(fp);
    fclose(fp);
    fclose(frag);
    return 1;
}