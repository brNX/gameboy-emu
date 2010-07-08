#include "cartridge.h"
#include <stdio.h>
#include <stdlib.h>


int readfile(char * filename){

FILE * file;
int filesize=0;

//abrir ficheiro e ler tamanho
file = fopen(filename, "rb");
if (file == NULL)
{
        printf("Error opening file for reading. Exiting...\n");
        return 1;
}
fseek(file, 0L, SEEK_END);
filesize = ftell(file);  //ignore EOF
fseek(file, 0L, SEEK_SET);

//ler ficheiro inteiro para array inByteArray
gbcart = (uint8_t*) calloc(filesize, sizeof(uint8_t));
fread(gbcart, 1, filesize, file);

printf("reading %s , filesize:%d K\n",filename,filesize/1024);

fclose(file);
return 0;

}

void destroy(){
    free(gbcart);
    gbcart=NULL;
}
