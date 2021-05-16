#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "traductor.h"
#include<ctype.h>
int o;
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
void muestraL(TListaC L){
while(L!=NULL){
    printf("%s %s\n",L->name,L->value);
    L=L->sig;
}
}

void load_register(int32_t memoria[], char v_mnemonics[],char v_registers[],char *argv[]){
    FILE *arch;
    TLista L=NULL;
    TListaC LC=NULL;
    int lineaActual=0,error=0,tipo1,tipo2,warningcont=0,lineaString,cte=0;
    char *filename=argv[1],auxline[100], finalLine[100],firstword[100],label[10],mnem[10],first_arg[10],second_arg[10],nom[10],equ[10],valor[10],auxcte[10];//finalLine es la linea sin rotulo ni comentarios
    int32_t salida1,salida2;
    char comentario[100];
    arch=fopen("prueba.txt","rt");
    if(arch!=NULL){
        lineaActual=0;
        // Rotulos y Constantes
         while (fgets(auxline,100,arch)!=NULL){
            if(valid_line(auxline)){
                sscanf(auxline,"%s",firstword);
                if (is_label(firstword)){  // Rotulo
                    strupr(firstword);
                    firstword[strlen(firstword)-1]='\0';//paso label sin :
                    add_label(&L,firstword,lineaActual);
                }
                else{    // Constante
                    sscanf(auxline,"%s %s %s",nom,equ,valor);
                    strupr(equ);
                    if(strcmp(equ,"EQU")==0){
                            cte=1;
                        add_const(&LC,nom,valor);
                    }

            }
            if(cte!=1)
            lineaActual++;

            cte=0;
        }
        }
        muestraL(LC);
        lineaString = lineaActual;
        //Traduccion
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
                strcpy(auxcte,second_arg); strupr(auxcte);
                strupr(mnem);/*strupr(first_arg);strupr(second_arg);*/
                if (find_nmemonic(mnem,v_mnemonics)!=-1 && strcmp(auxcte,"EQU")!=0){
                    if(strcmp(second_arg,"NULL")!=0){
                        memoria[lineaActual]= find_nmemonic(mnem,v_mnemonics)<<28;
                        opereitor1(first_arg,&salida1,L, &tipo1,&error,v_registers,LC,&lineaString);
                        opereitor1(second_arg,&salida2,L, &tipo2,&error,v_registers,LC,&lineaString);
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
                        if(strcmp(first_arg,"NULL")!=0){
                            memoria[lineaActual]= find_nmemonic(mnem,v_mnemonics)<<24;// los de 1 operando usan 8
                            opereitor1(first_arg,&salida1,L, &tipo1,&error,v_registers,&LC,&lineaString);
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
                    memoria[lineaActual]=0xFFFFFFFF;//no ha menem
                    error=1;
                }
                if(o==0){//si no esta el comando -o entra
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
            }
            else
                if(o==0)
                    printf("%s",auxline);
        }
    }
    printf("%d",lineaString);
    fclose(arch);
if(warningcont!=0)
    printf("hay %d warnings",warningcont);
if(!error){
    create_arch(memoria,lineaActual,argv[2]);
}else{
    printf("No se creo el archivo ya que hubo errores");
}
}


int main(int argc, char *argv[])
{
    int32_t memoria[4096];
    char v_mnemonics[24][5], v_registers[16][3];
    //argc=4;
    //argv[1]="prueba.txt";
    //argv[2]="prueba.bin";
    //o=seekFlag("-o",argv,argc);
    //if(argc>2){
        create_mnemonics(v_mnemonics);
        create_registers(v_registers);
        load_register(memoria,v_mnemonics,v_registers,argv);
    //}
    //else
      //  printf("Ingrese nombre del archivo a leer y nombre del arch a crear");
    return 0;
}

