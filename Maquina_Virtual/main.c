#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "traductor.h"
#include<ctype.h>

void muestra (TLista L){
    while (L!=NULL){
        printf("%s %d \n",L->label,L->line);
        L=L->sig;
    }
}

void load_register(int32_t memoria[], char v_mnemonics[],char v_registers[]){
    FILE *arch;
    TLista L=NULL;
    int lineaActual=0,error,tipo1,tipo2;
    char *filename="prueba.txt",auxline[100], finalLine[100],firstword[100],label[10],mnem[10],first_arg[10],second_arg[10];//finalLine es la linea sin rotulo ni comentarios
    int32_t salida1,salida2;
    char *comentario;
    arch=fopen(filename,"rt");
    if(arch!=NULL){
         while (fgets(auxline,100,arch)!=NULL){
            sscanf(auxline,"%s",firstword);
            if (is_label(firstword)){
                firstword[strlen(firstword)-1]='\0';//paso label sin :
                add_label(&L,firstword,lineaActual);
            }
            lineaActual++;
        }
        rewind(arch);//vuelvo al principio
        lineaActual=0;
        while(fgets(auxline,100,arch)!=NULL){
            sscanf(auxline,"%s",firstword);
            comentario=strchr(auxline,';');
            strcpy(auxline,strtok(auxline,";\n"));
           // printf("%s",comentario);
            if(only_label(auxline) != NULL)
                    strcpy(auxline,only_label(auxline));
            strcpy(first_arg,"NULL");
            strcpy(second_arg,"NULL");
            sscanf(auxline,"%s %s %s",mnem,first_arg,second_arg);
            strupr(mnem);strupr(first_arg);strupr(second_arg);
            if(strcmp(second_arg,"NULL")!=0){ //2 operandos
                memoria[lineaActual]= find_nmemonic(mnem,v_mnemonics)<<28;//necesito que salga en hexa de find_nmen
                opereitor1(first_arg,&salida1,L, &tipo1,&error,v_registers);
                opereitor1(second_arg,&salida2,L, &tipo2,&error,v_registers);
                //printf("%02X   02X   02X   02X", find_nmemonic(mnem,v_mnemonics), tipo, salida1);
                memoria[lineaActual]|= (tipo1 <<26& 0x0C000000); //tipo primer arg
                memoria[lineaActual]|= (tipo2<<24 & 0x03000000);//tipo 2do arg
                memoria[lineaActual]|= (salida1<<12 & 0x00FFF000); //primer arg (en hexa)
                memoria[lineaActual]|= (salida2 & 0x00000FFF);//no necesita shifteos
                if (comentario!=NULL)
                    printf("[%04d]: %02x %02X %02X %02X %s %s \n",lineaActual,(memoria[lineaActual]& 0xFF000000)>>24,(memoria[lineaActual]& 0x00FF0000)>>16,(memoria[lineaActual]& 0x0000FF00)>>8,memoria[lineaActual]& 0x000000FF,auxline,comentario);
                else
                    printf("[%04d] %02x %02X %02X %02X %s \n",lineaActual,(memoria[lineaActual]& 0xFF000000)>>24,(memoria[lineaActual]& 0x00FF0000)>>16,(memoria[lineaActual]& 0x0000FF00)>>8,memoria[lineaActual]& 0x000000FF,auxline);
                    printf("%08X \n",memoria[lineaActual]);
          //          printf("%02hX \n",memoria[lineaActual] & 0xFF000000);
            }
            else{
                if(strcmp(first_arg,"NULL")!=0){
                    opereitor1(first_arg,&salida1,L, &tipo1,&error,v_registers);
                    memoria[lineaActual]= find_nmemonic(mnem,v_mnemonics)<<24;// los de 1 operando usan 8
                    memoria[lineaActual]|= (tipo1 <<22 & 0x00C00000); //tipo operando
                    memoria[lineaActual]|=(salida1 & 0x00000FFF) ; //
  //                      printf("%08X \n",memoria[lineaActual]);
                }
                else{//es stop
                            //yoquese
                }
 //                 printf("%02X \n",memoria[lineaActual]& 0xFF000000);
  //                 printf("%02X %02X %02X %02X \n",memoria[lineaActual]& 0xFF000000,memoria[lineaActual]& 0x00FF0000,memoria[lineaActual]& 0x0000FF00,memoria[lineaActual]& 0x00000FF0);
                }
                lineaActual++;
        }
        /*
        if(no hay errores, estan los rotulos y no me pase de memoria){
            escribo el .dat con el vector memoria
        }
        */
    }
    fclose(arch);
}

int main(int argc, char *argv[])
{
    int32_t memoria[4096];
    int DS=0,x; //DATA SEGMENT
    char v_mnemonics[24][5], v_registers[16][3];
    create_mnemonics(v_mnemonics);
    create_registers(v_registers);
    load_register(memoria,v_mnemonics,v_registers);
    //memoria[0]= x<<28;
    return 0;

}
