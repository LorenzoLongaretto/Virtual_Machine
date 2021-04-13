#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "traductor.h"
#include<ctype.h>


void load_register(char v_mnemonics[]){
    FILE *arch;
    int lineaActual=0,pos;
    char *filename="prueba.txt",auxline[100], finalLine[100],firstword[100],label[10],mnem[10],first_arg[10],second_arg[10];//finalLine es la linea sin rotulo ni comentarios
    int32_t lineBinary;
    char lineB[33];
    arch=fopen(filename,"rt");
    if(arch!=NULL){
        while(fgets(auxline,100,arch)!=NULL){
            sscanf(auxline,"%s",firstword);
            if(valid_line(auxline,v_mnemonics)){
                strcpy(auxline,strtok(auxline,";"));//Elimina los comenarios

                if(only_label(auxline) != NULL){   //Elimina los rotulos, revisar doble llamado, problema:only label devuelve char o NULL
                        sscanf(auxline,"%s",label);//Guarda label
                        //listLabels(*l_labels,label);
                        strcpy(auxline,only_label(auxline));//Elimina rotulo
                }
                strcpy(first_arg,"NULL");//Nos avisa si NO hay operador
                strcpy(second_arg,"NULL");//Nos avisa si solo hay un operador
                sscanf(auxline,"%s %s %s",mnem,first_arg,second_arg);//Mnemonico y operandos
                strupr(mnem);strupr(first_arg);strupr(second_arg);
                write_mnemonic(find_nmemonic(mnem),lineBinary);
                printf("%s %s %s \n",mnem,first_arg,second_arg);
                strtok(first_arg,"],");//Dejamos pelado el primer operando
                //Cargar el codigo
                if(first_arg==NULL){//es STOP


                }
                else
                    if(second_arg==NULL){//1Argumento
                        //void opereitor(char ARG[],char *,int *codigo, int *,char v_mnemonics[24][5]){//Devuelve los argumentos y el codigo de operacion en binario para su posterior
                        opereitor(first_arg, lineBinary);

                    }

                    else{//2Argumentos
                        opereitor(first_arg, lineBinary);
                        opereitor(second_arg, lineBinary);


                    }

                //opereitor(char ARG[],char *,int *codigo, int *,char v_mnemonics[24][5])
                lineaActual++;
            }
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
