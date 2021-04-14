#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "traductor.h"
#include<ctype.h>


void load_register(char v_mnemonics[]){
    FILE *arch;
    TLista L=NULL;
    int lineaActual=0,pos;
    char *filename="prueba.txt",auxline[100], finalLine[100],firstword[100],label[10],mnem[10],first_arg[10],second_arg[10];//finalLine es la linea sin rotulo ni comentarios
    int32_t lineBinary;
    char lineB[33];
    arch=fopen(filename,"rt");
    if(arch!=NULL){
         while (fgets(auxline,100,arch)!=NULL){
            if (is_label(firstword)==1){
                sscanf(auxline,"%s",firstword);
                firstword[strlen(firstword)-1]='\0';//paso label sin :
                add_label(&L,firstword,lineaActual);
            }
            lineaActual++;
        }
        rewind(arch);//vuelvo al principio
        lineaActual=0;
        while(fgets(auxline,100,arch)!=NULL){
            sscanf(auxline,"%s",firstword);
          //  if(valid_line(auxline,v_mnemonics)){
                strcpy(auxline,strtok(auxline,";"));
                if(only_label(auxline) != NULL)
                    strcpy(auxline,only_label(auxline));
                strcpy(first_arg,"NULL");
                strcpy(second_arg,"NULL");
                sscanf(auxline,"%s %s %s",mnem,first_arg,second_arg);
                strupr(mnem);strupr(first_arg);strupr(second_arg);
                if(strcmp(second_arg,"NULL")!=0){ //2 operandos
                    memoria[lineaActual]= find_nmemonic(mnem,v_mnemonics)<<28;
                    opereitor1(first_arg,&salida,L, &tipo,&error,v_registers);
                    memoria[lineaActual]|=( tipo <<26& 0x0C000000); //tipo primer arg,la C es para deja el op a e inicializa el b
                    memoria[lineaActual]|= (salida<<12 & 0x00FFF000); //primer arg
                    opereitor1(second_arg,&salida,L, &tipo,&error,v_registers);
                    memoria[lineaActual]|= (tipo<<24 & 0x03000000);//tipo 2do arg
                    memoria[lineaActual]|= (salida & 0x00000FFF);//no necesita shifteos
                    printf("%04X \n",memoria[lineaActual]);
                }
                else{
                    if(strcmp(first_arg,"NULL")!=0){
                        opereitor1(first_arg,&salida,L, &tipo,&error,v_registers);
                        memoria[lineaActual]= find_nmemonic(mnem,v_mnemonics)<<24;// los de 1 operando usan 8
                        memoria[lineaActual]|= (tipo <<22 & 0x00C00000); //tipo operando
                        //printf("%04X \n",memoria[lineaActual]);
                        memoria[lineaActual]|=(salida & 0x00000FFF) ; //
                        //PRUEBA = memoria[lineaActual];
                        //printf("EL INT32es: %d");
                        printf("%08X \n",memoria[lineaActual]);
                    }
                    else{//es stop
                            //yoquese
                    }
                }
//                printf("%s %s %s \n",mnem,first_arg,second_arg);

                //Cargar el codigo


                //opereitor(char ARG[],char *,int *codigo, int *,char v_mnemonics[24][5])
                lineaActual++;
           // }
            else{
                printf("linea no valida");
                //Lineas en blanco
                //HACER BANDERA (llamar a belgrano, by pablito)
                //aca va el error de syntax,
                //Ante alguno de estos errores la traducción deberá continuar,
                //pero no se generará el archivo Programa
                //Código Máquina.

            }
            //printf("%d", lineaActual); Indica el nro de linea, solo tiene en cuenta las lineas validas
            //printf("%d ",filtranum);
        }

    }


    fclose(arch);
}

int main(int argc, char *argv[])
{
    int32_t memoria[4096];
    int DS=0; //DATA SEGMENT
    char v_mnemonics[24][5];
    create_mnemonics(v_mnemonics);
    load_register(v_mnemonics);

    return 0;
}
