#include "1.h"
#include <stdio.h>
#include <stdlib.h>
#include "instrucciones.h"


//instrucciones nemonicas void mov()



/*

int segundo()
{
//ERASE UNA VEZ
    char linea[256], *token;
    FILE *arch;
    arch = fopen("prueba.txt","rt");
    if(arch == NULL)
        return 1;
    char *token = strtok(linea,":");
    printf("%10d | %s", strlen(linea), *token);
    while(fgets(linea, 256, arch) != NULL){
        //printf("%10d | %s", strlen(linea), linea);
        printf("%10d | %s", strlen(linea), *token);
    }
    strcmp(palabras[i],':')
    fclose(arch);
    printf("Priemro!\n");
    return 0;
}




void create_registers(char vec[]){
int i;

for (i=0;i<16;i++)
    strcpy(vec[i],"");
strcpy(vec[0],"DS");
strcpy(vec[5],"IP");
strcpy(vec[8],"CC");
strcpy(vec[9],"AC");
strcpy(vec[10],"AX");
strcpy(vec[11],"BX");
strcpy(vec[12],"CX");
strcpy(vec[13],"DX");
strcpy(vec[14],"EX");
strcpy(vec[15],"FX");
}


/*
void MOV(int *arg1,int *arg2){ //MOV AX,BX son int de 32 creo

    *arg1=*arg2;
}

void ADD(int *arg1, int *arg2){
    *arg1+=*arg2;
}

void SUB(int *arg1, int *arg2){
    *arg1-=*arg2;
}

void SWAP(int *arg1, int *arg2){
int cambio;
    cambio=*arg1;
    *arg1=*arg2;
    *arg2=cambio;
}

void MUL(int *arg1, int *arg2){

    *arg1 *=*arg2;
}

void DIV(int *arg1, int *arg2){

    *arg1 /=arg2;
}

void CMP(int *arg1, int *arg2){//FALTA

}

void SHL(int *arg1, int *arg2){

    *arg1 <<=*arg2;
}

void SHR(int *arg1, int *arg2){

    *arg1 >>=*arg2;
}

void AND(int *arg1, int *arg2){

    *arg1 &=*arg2;
}

void OR(int *arg1, int *arg2){

    *arg1 |=*arg2;
}

void XOR(int *arg1, int *arg2){

    *arg1 ^=*arg2; //gracias google
}

void SYS(){

}



void NOT(int *arg1, int *arg2){ //paso arg2 al pedo

    *arg1=-*arg1;
}

*/







