#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "traductor.h"

void create_mnemonics(char v_mnemonics[]){
    strcpy(v_mnemonics[0], "MOV");
    strcpy(v_mnemonics[1], "ADD");
    strcpy(v_mnemonics[2], "SUB");
    strcpy(v_mnemonics[3], "SWAP");
    strcpy(v_mnemonics[4], "MUL");
    strcpy(v_mnemonics[5], "DIV");
    strcpy(v_mnemonics[6], "MOD");
    strcpy(v_mnemonics[7], "SHL");
    strcpy(v_mnemonics[8], "SHR");
    strcpy(v_mnemonics[9], "AND");
    strcpy(v_mnemonics[10], "OR");
    strcpy(v_mnemonics[11], "XOR");
    strcpy(v_mnemonics[12], "SYS");
    strcpy(v_mnemonics[13], "JMP");
    strcpy(v_mnemonics[14], "JZ");
    strcpy(v_mnemonics[15], "JP");
    strcpy(v_mnemonics[16], "JN");
    strcpy(v_mnemonics[17], "JNZ");
    strcpy(v_mnemonics[18], "JNP");
    strcpy(v_mnemonics[19], "JNN");
    strcpy(v_mnemonics[20], "LDH");
    strcpy(v_mnemonics[21], "RND");
    strcpy(v_mnemonics[22], "NOT");
    strcpy(v_mnemonics[23], "STOP");
}

int is_mnemonic(char string[], char v_mnemonics[]){
    int i=0;
    while((strcmp(string,v_mnemonics[i]) != 0) && i<=23)
        i++;
    return(i<=23);
}

int is_label(char string[]){
    return (string[strlen(string)-1]==":");
}

int valid_line(char string[], char v_mnemonics[]){
    return (!isspace(string[0]) && (is_label(string) || is_mnemonic(string,v_mnemonics)));
}

void clean_comments(){

}

char *only_label(char string[]){
    char ch = ':', *ret;
    ret = strchr(string,ch);
    if (ret!=NULL){//Si hay label es !=NULL
      ret = strtok(ret,":");
      return (++ret);//Borra el : que nos quedaba al eliminar el rotulo
    }
    else
      return NULL;
}

<<<<<<< Updated upstream
int filter_num(char auxline[]){//Filtra los numeros dada una cadena
int num,i,j=0;
char straux[100];
    for (i=0;i<strlen(auxline);i++)
        if (auxline[i]>='0' && auxline[i]<='9'){
            straux[j]=auxline[i];
            straux[j+1]="\0";
            j++;
        }
    if (straux[0]!='\0')
        return atoi(straux); //pasa string a decimal, ej '1' pasa a 1
    else
        return -1;
}
=======
int find_nmemonic(char *mnem,char v_mnemonics[24][5]){ //paso la linea completa y busca en el vector y devuelve la posicion
int i=0;
    while((strcmp(mnem,v_mnemonics[i]) != 0) && i<=23)
        i++;
        return (i<=23)? i:-1;
}
/*
void opereitor(char ARG[],char *,int *codigo, int *,char v_mnemonics[24][5]){
    char aux[];

    if (ARG[0] == '#' || isdigit(ARG[0]) || ARG[0] == '@' || ARG[0] == '%'){// INMEDIATO
    //Asumimos que hay que tomar 4bytes para la reserva en ram, PREGUNTAR

    }
    else{
        if (isalpha(ARG[0])){//REGISTRO
        }
        else{
            if (ARG[0]=='['){ // DIRECTO
                strncpy(aux,ARG,strlen(ARG)-1);//Dejamos el "]" afuera
                switch (ARG_A[1]){
                case ('#' || isdigit(ARG[1])):
                    //decimal
                    break;
                case '@':
                    //octal
                    break;
                case '%'
                    //hexa
                    break;
                default:
                    //caracter
                }
            }
        }
    }
}*/



>>>>>>> Stashed changes
