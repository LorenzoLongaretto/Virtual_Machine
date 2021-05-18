#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "traductor.h"
#include<ctype.h>
#define DS 0
#define SS 1
#define ES 2
#define CS 3

void create_arch(int32_t memoria[],int N,char *filename){
int i;
FILE *arch;
arch=fopen("prueba.bin","wb");
for (i=0;i<N;i++){
    fwrite(&memoria[i],sizeof(memoria[i]),1,arch);
}
fclose(arch);

}
int seekFlag(char* flag,char *aux[],int argc){
    int i;
    for(i=0;i<argc;i++){
        if(strcmp(flag,aux[i])==0)
            return 1;
    }
    return 0;
}
/*
void muestraL(TListaC L){
while(L!=NULL){
    printf("%s %s\n",L->name,L->value);
    L=L->sig;
}

}*/
void muestra_por_pantalla(int32_t memoria[],int lineaActual,char auxline[],char comentario[],char auxcte[],char mnem[],char firstword[]){

    if( strcmp(auxcte,"EQU")!=0 && strcmp(mnem,"\\\\ASM")!=0 &&auxline[0]!=';'){
        if (firstword[0]=='\0')
            if(comentario[0]=='\0')
                printf("[%04d]: %02X %02X %02X %02X\t%d:\t%s\n",lineaActual,(memoria[lineaActual]& 0xFF000000)>>24,(memoria[lineaActual]& 0x00FF0000)>>16,(memoria[lineaActual]& 0x0000FF00)>>8,memoria[lineaActual]& 0x000000FF,lineaActual+1,auxline);
            else
                printf("[%04d]: %02X %02X %02X %02X\t%d:\t%s \t%s",lineaActual,(memoria[lineaActual]& 0xFF000000)>>24,(memoria[lineaActual]& 0x00FF0000)>>16,(memoria[lineaActual]& 0x0000FF00)>>8,memoria[lineaActual]& 0x000000FF,lineaActual+1,auxline,comentario);
        else
            if(comentario[0]=='\0')
                            printf("[%04d]: %02X %02X %02X %02X\t%s\t%s \n",lineaActual,(memoria[lineaActual]& 0xFF000000)>>24,(memoria[lineaActual]& 0x00FF0000)>>16,(memoria[lineaActual]& 0x0000FF00)>>8,memoria[lineaActual]& 0x000000FF,firstword,auxline);
            else
                            printf("[%04d]: %02X %02X %02X %02X\t%s\t%s\t%s",lineaActual,(memoria[lineaActual]& 0xFF000000)>>24,(memoria[lineaActual]& 0x00FF0000)>>16,(memoria[lineaActual]& 0x0000FF00)>>8,memoria[lineaActual]& 0x000000FF,firstword,auxline,comentario);
                    }
    else{
        if(auxline[0]==';')
            printf("%s",auxline);
        else
            printf("%s \n",auxline);
    }

}




void primera_pasada(char auxline[100],TLista *L,TListaC *LC,char sizes[],int *lineaActual){
char firstword[10],nom[10],equ[10],valor[10];
int sumalinea=1;
    if(valid_line(auxline)){
        sscanf(auxline,"%s",firstword);
            if(strcmp(strupr(firstword),"\\\\ASM")==0){
                sumalinea=0;
                size_segment(auxline,sizes);
            }
            else{
                if (is_label(firstword)){  // Rotulo
                    strupr(firstword);
                    firstword[strlen(firstword)-1]='\0';//paso label sin :
                    add_label(L,firstword,*lineaActual); //ese * dudoso esta bien
                }
                else{    // Constante
                    sscanf(auxline,"%s %s %s",nom,equ,valor);
                    strupr(equ);
                    if(strcmp(equ,"EQU")==0){
                        sumalinea=0;
                        add_const(LC,strupr(nom),valor);
                    }
                }
            }
          if(sumalinea) //de merca
            (*lineaActual)++;
          sumalinea=0;
        }
}
void cargamem(int32_t memoria[],char sizes[]){
int i,j=0;
memoria[0]= 1297494577;
    for(i=1;i<5;i++,j++){
        memoria[i]=sizes[j];
    }
}

void load_register(int32_t memoria[], char v_mnemonics[],char v_registers[],char *argv[],int o){
FILE *arch;
TLista L=NULL;
TListaC LC=NULL;
int lineaActual=0,error=0,tipo1,tipo2,warningcont=0,lineaString,cte=0,primera=0,header=0;
char *filename=argv[1],auxline[100], finalLine[100],firstword[100],label[10],mnem[10],first_arg[10],second_arg[10],nom[10],equ[10],valor[10],auxcte[10];//finalLine es la linea sin rotulo ni comentarios
int32_t salida1,salida2,sizes[5];
char comentario[100];
arch=fopen("prueba.txt","rt");
    if(arch!=NULL){// Rotulos y Constantes

         while (fgets(auxline,100,arch)!=NULL)
            primera_pasada(auxline,&L,&LC,sizes,&lineaActual);
        sizes[CS] = lineaActual;
        cargamem(memoria,sizes);

      /* printf("%X\n",memoria[0]);
       printf("%d\n",memoria[1]);
       printf("%d\n",memoria[2]);
       printf("%d\n",memoria[3]);*/

        lineaString = lineaActual+5;
        // Cargar en memoria los 5 bloques del header

        //Traduccion
        rewind(arch);
        lineaActual=5;;
        while(fgets(auxline,100,arch)!=NULL){
            if(valid_line(auxline)){
                sscanf(auxline,"%s",firstword);
                comentario[0]='\0';
                if(strchr(auxline,';')!=NULL)
                    strcpy(comentario,strchr(auxline,';'));
                strcpy(auxline,strtok(auxline,";\n"));
                firstword[0]='\0';
                if(only_label(auxline) != NULL){
                    sscanf(auxline,"%s",firstword);
                    strcpy(auxline,only_label(auxline));
                }
                strcpy(first_arg,"NULL");
                strcpy(second_arg,"NULL");
                change_char(auxline);
                sscanf(auxline,"%s %s %s",mnem,first_arg,second_arg);
                strcpy(auxcte,first_arg); strupr(auxcte);
                strupr(mnem);/*strupr(first_arg);strupr(second_arg);*/
                if (find_nmemonic(mnem,v_mnemonics)!=-1 && strcmp(auxcte,"EQU")!=0  && strcmp(mnem,"\\\\ASM")!=0){
                    if(strcmp(second_arg,"NULL")!=0){
                        memoria[lineaActual]= find_nmemonic(mnem,v_mnemonics)<<28;
                        opereitor1(first_arg,&salida1,L, &tipo1,&error,v_registers,LC,&lineaString,&primera);
                        opereitor1(second_arg,&salida2,L, &tipo2,&error,v_registers,LC,&lineaString,&primera);
                        if(salida1>0x00000FFF) //WARNING
                            warningcont+=1;
                        if(salida2>0x00000FFF)
                            warningcont+=1;
                        memoria[lineaActual]|= (tipo1 <<26& 0x0C000000); //tipo primer arg
                        memoria[lineaActual]|= (tipo2<<24 & 0x03000000);//tipo 2do arg
                        memoria[lineaActual]|= (salida1<<12 & 0x00FFF000); //primer arg (en hexa)
                        memoria[lineaActual]|= (salida2 & 0x00000FFF);//no necesita shifteos

                    }
                    else{
                        if(strcmp(first_arg,"NULL")!=0 && strcmp(auxcte,"EQU")!=0){
                            memoria[lineaActual]= find_nmemonic(mnem,v_mnemonics)<<24;// los de 1 operando usan 8
                            opereitor1(first_arg,&salida1,L, &tipo1,&error,v_registers,LC,&lineaString,&primera);
                            if(salida1>0x0000FFFF) //WARNING
                            warningcont+=1;
                            memoria[lineaActual]|= (tipo1 <<22 & 0x00C00000); //tipo operando
                            memoria[lineaActual]|=(salida1 & 0x0000FFFF) ;
                        }
                        else// es stop
                            memoria[lineaActual]= 0xFF100000;
                    }
                }
                else{
                    if(strcmp(auxcte,"EQU" )!=0 && strcmp(mnem,"\\\\ASM")!=0){
                        memoria[lineaActual]=0xFFFFFFFF;//no ha menem
                        error=1;
                    }
                }

        }
         if(o==0)//si no esta el comando -o entra
            muestra_por_pantalla(memoria,lineaActual,auxline,comentario,auxcte,mnem,firstword);
    }
    //printf("%d\n",lineaString);
        fclose(arch);
        load_cte_string(LC,memoria);
        if(warningcont!=0)
            printf("hay %d warnings",warningcont);
        if(!error){
            create_arch(memoria,lineaActual,argv[2]);
            printf("Creacion exitosa");
        }else{
            printf("No se creo el archivo ya que hubo errores");
        }
    }
}

int main(int argc, char *argv[])
{
    int32_t memoria[8192];
    int o=0;
    char v_mnemonics[4081][5], v_registers[16][3];
    //argc=4;
    //argv[1]="prueba.txt";
    //argv[2]="prueba.bin";
    //o=seekFlag("-o",argv,argc);
    //if(argc>2){
        create_mnemonics(v_mnemonics);
        create_registers(v_registers);
        load_register(memoria,v_mnemonics,v_registers,argv,o);
    //}
    //else
      //  printf("Ingrese nombre del archivo a leer y nombre del arch a crear");
    return 0;
}

