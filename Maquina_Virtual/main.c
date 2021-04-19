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

void create_arch(int32_t memoria[],int N){
int i;
FILE *arch;
arch=fopen("nombredebinario.dat","wb");
for (i=0;i<N;i++){
    fwrite(&memoria[i],sizeof(memoria[i]),1,arch);
}

}

void load_register(int32_t memoria[], char v_mnemonics[],char v_registers[]){
    FILE *arch;
    TLista L=NULL;
    float flot;
    int lineaActual=0,error=0,tipo1,tipo2;
    char *filename="prueba.txt",auxline[100], finalLine[100],firstword[100],label[10],mnem[10],first_arg[10],second_arg[10];//finalLine es la linea sin rotulo ni comentarios
    int32_t salida1,salida2;
    char comentario[100];
    arch=fopen(filename,"rt");
    if(arch!=NULL){
        lineaActual=0;
         while (fgets(auxline,100,arch)!=NULL){
            if(valid_line(auxline)){
                sscanf(auxline,"%s",firstword);
                if (is_label(firstword)){
                    strupr(firstword);
                    firstword[strlen(firstword)-1]='\0';//paso label sin :
                    add_label(&L,firstword,lineaActual);
                }
            lineaActual++;
            }
        }
   //     muestra(L);
        rewind(arch);
        lineaActual=0;
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
                strupr(mnem);strupr(first_arg);strupr(second_arg);
                if (find_nmemonic(mnem,v_mnemonics)!=-1){
                    if(strcmp(second_arg,"NULL")!=0){
                        memoria[lineaActual]= find_nmemonic(mnem,v_mnemonics)<<28;
                        opereitor1(first_arg,&salida1,L, &tipo1,&error,v_registers);
                        opereitor1(second_arg,&salida2,L, &tipo2,&error,v_registers);
                        memoria[lineaActual]|= (tipo1 <<26& 0x0C000000); //tipo primer arg
                        memoria[lineaActual]|= (tipo2<<24 & 0x03000000);//tipo 2do arg
                        memoria[lineaActual]|= (salida1<<12 & 0x00FFF000); //primer arg (en hexa)
                        memoria[lineaActual]|= (salida2 & 0x00000FFF);//no necesita shifteos
                        salida1=trunc_warning(salida1);
                        salida2=trunc_warning(salida2);
                    }
                    else{
                        if(strcmp(first_arg,"NULL")!=0){
                            memoria[lineaActual]= find_nmemonic(mnem,v_mnemonics)<<24;// los de 1 operando usan 8
                            opereitor1(first_arg,&salida1,L, &tipo1,&error,v_registers);
                            memoria[lineaActual]|= (tipo1 <<22 & 0x00C00000); //tipo operando
                            memoria[lineaActual]|=(salida1 & 0x0000FFFF) ;
                        }
                        else// es stop
                            memoria[lineaActual]= 0xFF100000;
                    }
                }
                else{
                    memoria[lineaActual]=0xFFFFFFFF;//no ha menem
                    error=1;
                }
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
                lineaActual++;
            }
            else{
                printf("%s",auxline);
        }

        }
    }
    fclose(arch);
if(!error){
    create_arch(memoria,lineaActual);
}
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
