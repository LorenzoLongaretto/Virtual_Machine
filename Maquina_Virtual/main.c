#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "traductor.h"
#include<ctype.h>


void load_register(char v_mnemonics[]){
    FILE *arch;
    int lineaActual=0,pos;
    char *filename="prueba.txt",*auxline, finalLine[100],firstword[100],label[10];//finalLine es la linea sin rotulo ni comentarios
    int32_t lineBinary;
    arch=fopen(filename,"rt");
    if(arch!=NULL){
        while(fgets(auxline,100,arch)!=NULL){
            sscanf(auxline,"%s",firstword);
            if(valid_line(auxline,v_mnemonics))
            {
                strcpy(auxline,strtok(auxline,";"));//Elimina los comenarios

                if(only_label(auxline) != NULL){    //Elimina los rotulos, revisar doble llamado, problema:only label devuelve char o NULL
                        sscanf(auxline,"%s",label); //Guarda el rotulo
                        //listLabels(*l_labels,label);
                        strcpy(auxline,only_label(auxline)); //Elimina rotulo
                }
                strcpy(finalLine,auxline); // copio la linea completa en finalLine para no perderla
                printf("%s\n", finalLine);
                auxline = strtok(auxline," ");
                pos = find_nmemonic(strupr(auxline),v_mnemonics);  // primero analizo el mnemonico

                if(pos==-1){ //error, no encuentra mnemonico
                    //lineBinary = ;
                }else{
                    //lineBinary = ;
                }

                 while(auxline!=NULL){   // analizo los otros terminos recorriendo

                      if(auxline[0] =='['){ // es directo


                      }


                    auxline = strtok(NULL," ");
               }
                //printf("%d \n",filtranum(auxline));


                lineaActual++;
            }else{
                //lineBinary = ;        //error, no es una linea valida
            }
            //printf("%d", lineaActual); Indica el nro de linea, solo tiene en cuenta las lineas validas
            //printf("%d ",filtranum);
        }

    }


    fclose(arch);
}

int main(int argc, char *argv[])
{
    char v_mnemonics[24][5];
    create_mnemonics(v_mnemonics);
    load_register(v_mnemonics);

    return 0;
}
