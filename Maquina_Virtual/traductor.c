#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "traductor.h"
#include<ctype.h>

void create_mnemonics(char v_mnemonics[253][5]){
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
    //Funciones String
    strcpy(v_mnemonics[13],"SMOV");
    strcpy(v_mnemonics[12],"SLEN");
    strcpy(v_mnemonics[14],"SCMP");

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
    //Funciones Pila
    strcpy(v_mnemonics[252],"PUSH");
    strcpy(v_mnemonics[253],"POP");
    strcpy(v_mnemonics[254],"CALL");
    strcpy(v_mnemonics[4080],"RET"); // 0 operando

    strcpy(v_mnemonics[4081],"STOP");
}
void create_registers(char vec[16][3]){
int i;
    for (i=0;i<16;i++)
        strcpy(vec[i],"");
    strcpy(vec[0],"DS");
    strcpy(vec[1],"SS");
    strcpy(vec[2],"ES");
    strcpy(vec[3],"CS");
    strcpy(vec[4],"HP");
    strcpy(vec[5],"IP");
    strcpy(vec[6],"SP");
    strcpy(vec[7],"BP");
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
/*int operandos(char string[]){
    return (string[strlen(string)-1]==',');
}*/
int is_label(char string[]){
    return (string[strlen(string)-1]==':');
}
int is_cte(char string[],TListaC L){

while((L!=NULL && strcmp(L->name,string)!=0)){
    L=L->sig;
}
        return L!=NULL;
}
int valid_line(char string[]){    // string[] es la cadena completa de la linea del archivo
char aux[100];
    sscanf(string,"%s",aux);//leo el primer string de toda la cadena
    if (string[0]=='\n' ||string[0]=='\t'||string[0]==';') //si no es espacio laburo
        return 0;
    else
        return 1;
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

int find_nmemonic(char *mnem,char v_mnemonics[253][5]){ //paso la linea completa y busca en el vector y devuelve la posicion
int i=0;
    while((strcmp(mnem,v_mnemonics[i])!= 0) && (i<=260))
        i++;
        return (i<=260)? i:-1;
}

void add_label(TLista *L, char x[],int actual_line){//Inserta al final
    TLista aux;
    aux=(TLista)malloc(sizeof(nodo));
    aux->line=actual_line;
    strcpy(aux->label,x);
    aux->sig=NULL;
    aux->sig=*L;
    *L=aux;
}

void add_const(TListaC *LC,char name[],char value[]){
TListaC aux;
    aux=(TListaC)malloc(sizeof(nodoC));
    strcpy(aux->value,value);
    strcpy(aux->name,name);
    aux->sig=NULL;
    aux->sig=*LC;
    *LC=aux;
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

void change_char(char str[]){
int size=strlen(str), i=0;
    while(str[i]!=',' && i<size)
        i++;
    if(i<size)
        str[i]=' ';
}
void  clean_sign(char *string,char* aux){
int i;
for(i=1;i<=strlen(string);i++){
        aux[i-1]=string[i];

}

}

void clean_arg(char str[], char aux[]){//Entra str y devuelve un aux solo con el numero
int i=0,j=0;
    while(str[i]!='\0'){
        if((str[i]>='0' && str[i]<='9'||str[i]=='-'||str[i]=='+') || isalpha(str[i]) || str[i]=='\''){
            aux[j]=str[i];
            aux[j+1]='\0';
            j++;
        }
        i++;
    }
}

int find_label(TLista L,char x[]){
while (L!=NULL){
    if(strcmp(L->label,x)==0)
        return L->line;
    L=L->sig;
}
return 0x00000FFF;
}
void opereitor1(char ARG[], int *salida, TLista L_label, int *tipo, int *error, char v_registers[],TListaC L_const,int *lineaString){
    char aux[10],offset[10],clean_offset[10];
    clean_arg(ARG,aux);
    if (ARG[0] == '#' || isdigit(ARG[0]) || ARG[0] == '@' || ARG[0] == '%' || ARG[0]=='\''|| ARG[0] == '-'){//OPERANDO INMEDIATO
        *tipo=0;
        switch (ARG[0]){//Lo pasamos a binario
                case '\'': //ASCII
                   if(ARG[1]==NULL)
                    *salida=32;// ESPACIO
                   else
                   *salida=ARG[1];
                    break;
                case '@'://octal
                    *salida=strtoul(aux,NULL,8);
                    break;
                case '%'://hexa
                    *salida=strtoul(aux,NULL,16);
                    break;
                default://decimal
                    {
                    if(isalpha(ARG[0])){
                        *salida = find_const(ARG,L_const,lineaString);
                    }
                    else // es decimal
                       *salida=strtoul(aux,NULL,10);
                    }
        }
    }
    else{
        if (ARG[0]=='[' ){ //OPERANDO DIRECTO
            if((ARG[1]>='0' && ARG[1]<='9')|| is_cte(strupr(aux),L_const)){
                *tipo=2;
                switch (ARG[1]){
                case '\�': //ASCII
                   *salida=ARG[1];
                    break;
                case '@':
                    *salida=strtoul(aux,NULL,8);
                    break;
                case '%': //hexa
                    *salida=strtoul(aux,NULL,16);
                    break;
                default://decimal
                     {
                    if(isalpha(ARG[1])){
                        *salida = find_const(aux,L_const,lineaString);
                    }
                    else // es decimal
                       *salida=strtoul(aux,NULL,10);
                    }
                }
            }
            else{//OPERANDO INDIRECTO
                if (ARG[0]=='['&& (ARG[1]>='A' && ARG[1]<='z')){
                    offset[0]='\0';
                    //si offset es alfa hay que buscar en la lista de ctes
                    if(strchr(aux,'+'))
                        strcpy(offset,strchr(aux,'+'));
                    if(strchr(aux,'-'))
                        strcpy(offset,strchr(aux,'-'));
                    strcpy(aux,strtok(aux,"+-"));

                    if(offset[0]!='\0')
                        if(offset[1]>='0' &&offset[1]<='9')
                            *salida=(strtoul(offset,NULL,10))<<4;
                        else{  // es constante
                             clean_offset[0]='\0';
                            clean_sign(offset,clean_offset);
                            strupr(clean_offset);
                            if(offset[0]=='-')
                                *salida = (-1*find_const(clean_offset,L_const,lineaString))<<4;
                            else
                                *salida = find_const(clean_offset,L_const,lineaString)<<4;
                        }

                    if (is_register(strupr(aux),v_registers)){
                        *tipo=3;
                        *salida|=find_register(aux,v_registers);
                    }
                }
                else{//OPERANDO REGISTRO
                 if (is_register(strupr(aux),v_registers)){
                    *tipo=1;
                    *salida=find_register(aux,v_registers);
                }
                 else{//es rotulo
                    strupr(ARG);
                    *tipo=0;
                    *salida=find_label(L_label,ARG);
                    if(*salida==0x00000FFF){ // agregar busqueda de constante
                        *tipo=2;
                        if(ARG[0]!='"')
                            *tipo = 0;
                       *salida = find_const(ARG,L_const,lineaString);
                    if(*salida==0x00000FFF)
                        *error=1;
                    }

                }
               }
        }
    }
  }
}


int find_const(char ARG[],TListaC L_const,int *lineaString){
int salida;
while(L_const!=NULL && strcmp(ARG,L_const->name)!=0){
    L_const=L_const->sig;
}
        if(L_const!=NULL){
            switch (L_const->value[0]){//Lo pasamos a binario
                         case '"':  //String
                        salida = *lineaString;
                        *lineaString+=strlen(L_const->value)-1;
                        break;
                         case '\'': //ASCII
                           if(L_const->value[1]==NULL)
                            salida=32;// ESPACIO
                           else
                           salida=L_const->value[1];
                            break;
                        case '@'://octal
                            salida=strtoul(L_const->value,NULL,8);
                            break;
                        case '%'://hexa
                            salida=strtoul(L_const->value,NULL,16);
                            break;
                        default://decimal
                            salida=strtoul(L_const->value,NULL,10);
                   }
        }
        else
           salida = 0x00000FFF;
    return salida;
}
