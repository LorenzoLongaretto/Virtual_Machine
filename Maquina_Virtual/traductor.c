#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "traductor.h"
#include<ctype.h>

void create_mnemonics(char v_mnemonics[254][5]){
int i;
    for (i=0;i<16;i++)
        strcpy(v_mnemonics[i],"");
    strcpy(v_mnemonics[0],"MOV");//2 operandos
    strcpy(v_mnemonics[1],"ADD");
    strcpy(v_mnemonics[2],"SUB");
    strcpy(v_mnemonics[3],"SWAP");
    strcpy(v_mnemonics[4],"MUL");
    strcpy(v_mnemonics[5],"DIV");
    strcpy(v_mnemonics[6],"CMP");
    strcpy(v_mnemonics[7],"SHL");
    strcpy(v_mnemonics[8],"SHR");
    strcpy(v_mnemonics[9],"AND");
    strcpy(v_mnemonics[10],"OR");
    strcpy(v_mnemonics[11],"XOR");
    strcpy(v_mnemonics[240],"SYS");//1 operando
    strcpy(v_mnemonics[241],"JMP");
    strcpy(v_mnemonics[242],"JZ");
    strcpy(v_mnemonics[243],"JP");
    strcpy(v_mnemonics[244],"JN");
    strcpy(v_mnemonics[245],"JNZ");
    strcpy(v_mnemonics[246],"JNP");
    strcpy(v_mnemonics[247],"JNN");
    strcpy(v_mnemonics[248],"LDL");
    strcpy(v_mnemonics[249],"LDH");
    strcpy(v_mnemonics[250],"RND");
    strcpy(v_mnemonics[251],"NOT");
    strcpy(v_mnemonics[252],"STOP");//0 operando
}

void create_registers(char vec[16][3]){
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

int is_mnemonic(char string[], char v_mnemonics[24][5]){
    int i=0;
    while((strcmp(string,v_mnemonics[i]) != 0) && i<=24)
        i++;
    return(i<=24);
}
int operandos(char string[]){
    return (string[strlen(string)-1]==',');
}
int is_label(char string[]){
    return (string[strlen(string)-1]==':');
}


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
/*
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
*/
int find_nmemonic(char *mnem,char v_mnemonics[24][5]){ //paso la linea completa y busca en el vector y devuelve la posicion
int i=0;
    while((strcmp(mnem,v_mnemonics[i]) != 0) && i<=260)
        i++;
        return (i<=260)? i:-1;
}

void add_label(TLista *L, char x[],int actual_line){//Inserta al final
    TLista aux,ult;
    aux=(TLista)malloc(sizeof(nodo));
    aux->line=actual_line;
    aux->sig=NULL;
    strcpy(aux->label,x);
    aux->sig=*L;
    *L=aux;
}

int is_register(char x[],char v_registers[][3]){
int i=0;
    while (i<16 && strcmp(x,v_registers[i])!=0)
        i++;
        return i<16;
}

int find_register(char ARG[],char v_registers[][3]){
int i=0;
    while (i<16 && strcmp(ARG,v_registers[i])!=0)
        i++;
    return i;
}

void clean_arg(char str[], char aux[]){//Entra str y devuelve un aux solo con el numero
int i=0,j=0;
    while(str[i]!='\0'){
        if((str[i]>='0' && str[i]<='9') || isalpha(str[i])){
            aux[j]=str[i];
            aux[j+1]='\0';
            j++;
        }
        i++;
    }

}




void opereitor1(char ARG[], int *salida, TLista L_label, int *tipo, int *flag_error, char v_registers[]){
    char aux[10];
    clean_arg(ARG,aux);
    if (ARG[0] == '#' || isdigit(ARG[0]) || ARG[0] == '@' || ARG[0] == '%' || ARG[0] == '‘'){//OPERANDO INMEDIATO
        *tipo=0;
        switch (ARG[0]){//Lo pasamos a binario
                case '‘':
                   //ACII
                   *salida=ARG[1];//Sumar el DS RECORDAR!!!!!!!!!!!!
                    break;
                case '@':
                    //octal
                    *salida=strtoul(aux,NULL,8);
                    break;
                case '%':
                    //hexa
                    *salida=strtoul(aux,NULL,16);
                    break;
                default:
                    //decimal
                    *salida=strtoul(aux,NULL,10);
        }
    }
    else{
        if (is_register(aux,v_registers)){//OPERANDO REGISTRO
            *tipo=1;
            *salida=find_register(aux,v_registers);
        }
        else{
            if (ARG[0]=='['){ //OPERANDO DIRECTO
                *tipo=2;
                switch (ARG[1]){
                case '‘':
                   //ACII
                   *salida=ARG[1];
                    break;
                case '@':
                    *salida=strtoul(aux,NULL,8);
                    break;
                case '%':
                    //hexa
                    *salida=strtoul(aux,NULL,16);
                    break;
                default:
                    //decimal
                    *salida=strtoul(aux,NULL,10);
                }
            }
        }/*
        if(is_label){//Crear lista
            *tipo=0; //el rotulo es inmediato
            list_pos = find_label(L_label, ARG);
            if(lista_pos!=-1)//Si lo encontre
                lineBinary
                //(modifico int32, aplicar mascara);
            else//No lo encontre
                //aplicar mascara, fff1;
                //bandera
        }*/
    }
}

