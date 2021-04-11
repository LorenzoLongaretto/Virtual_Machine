#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "traductor.h"
#include<ctype.h>

void create_mnemonics(char v_mnemonics[24][5]){
    strcpy(v_mnemonics[0],"MOV");
    strcpy(v_mnemonics[1],"ADD");
    strcpy(v_mnemonics[2],"SUB");
    strcpy(v_mnemonics[3],"SWAP");
    strcpy(v_mnemonics[4],"MUL");
    strcpy(v_mnemonics[5],"DIV");
    strcpy(v_mnemonics[6],"MOD");
    strcpy(v_mnemonics[7],"SHL");
    strcpy(v_mnemonics[8],"SHR");
    strcpy(v_mnemonics[9],"AND");
    strcpy(v_mnemonics[10],"OR");
    strcpy(v_mnemonics[11],"XOR");
    strcpy(v_mnemonics[12],"SYS");
    strcpy(v_mnemonics[13],"JMP");
    strcpy(v_mnemonics[14],"JZ");
    strcpy(v_mnemonics[15],"JP");
    strcpy(v_mnemonics[16],"JN");
    strcpy(v_mnemonics[17],"JNZ");
    strcpy(v_mnemonics[18],"JNP");
    strcpy(v_mnemonics[19],"JNN");
    strcpy(v_mnemonics[20],"LDH");
    strcpy(v_mnemonics[21],"RND");
    strcpy(v_mnemonics[22],"NOT");
    strcpy(v_mnemonics[23],"STOP");
}

int is_mnemonic(char string[], char v_mnemonics[24][5]){
    int i=0;
    while((strcmp(string,v_mnemonics[i]) != 0) && i<=23)
        i++;
    return(i<=23);
}
int operandos(char string[]){
    return (string[strlen(string)-1]==',');
}
int is_label(char string[]){
    return (string[strlen(string)-1]==':');
}
/* no verifica si el label esta bien pero la instruccion no
int valid_line(char string[], char v_mnemonics[24][5]){
    return (!isspace(string[0]) && (is_label(string) || is_mnemonic(toupper(string),v_mnemonics)));// TOUPPER NO FUNCA, SI PONEN TODO EN MAYUS EN EL ARCH DEBERIA FUNCAR
}
*///nota: esta funcion es mejor que la de arriba ya que contempla mas casos pero no funca el toupper(estoy re quemado)
int valid_line(char string[], char v_mnemonics[24][5]){    // string[] es la cadena completa de la linea del archivo
char aux[10];
sscanf(string,"%s",aux);//leo el primer string de toda la cadena
    if (!isspace(aux[0])){ //si no es espacio laburo
         if (is_label(aux)){ //si es rotulo avanzo la lectura y veo si es instrucion
            sscanf(string,"%s %s",aux,aux);
            return is_mnemonic(strupr(aux),v_mnemonics); //toupper no funca SI TENEMOS QUE HACER UN VOID PARA
         }                                                      //HACER MAYUS LA CADENA HAY QUE PASAR ESTA FUNCION A VOID
         else //si no es rotulo puede ser instruccion
            return is_mnemonic(strupr(aux),v_mnemonics); //puedo sacar factor comun esta linea
    }
    else
        return 0;
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

int find_nmemonic(char *mnem,char v_mnemonics[24][5]){ //paso la linea completa y busca en el vector y devuelve la posicion
int i=0;
    while((strcmp(mnem,v_mnemonics[i]) != 0) && i<=23)
        i++;

        return (i<=23)? i:-1;
}
