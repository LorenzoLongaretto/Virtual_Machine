#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "traductor.h"
#include<ctype.h>


void load_register(char v_mnemonics[]){
    FILE *arch;
    int lineaActual=0,pos;
    char *filename="prueba.txt",auxline[100], finalLine[100],firstword[100],mnem[50],label[10],A[10],B[10],C[10];//finalLine es la linea sin rotulo ni comentarios
    int32_t lineBinary;
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
                strcpy(C,"NULL");
                sscanf(auxline,"%s %s %s",A,B,C);
                strupr(A);strupr(B);strupr(C);
                //printf("%s\n", auxline);
                printf("%s %s %s \n",A,B,C);
                lineaActual++;
            }
            else{
                //HACER BANDERA (llamar a belgrano, by pablito)
                //aca va el error de syntax,
                //Ante alguno de estos errores la traducción deberá continuar,
                //pero no se generará el archivo Programa
                //Código Máquina.

            }
            //printf("%d", lineaActual); Indica el nro de linea, solo tiene en cuenta las lineas validas

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
