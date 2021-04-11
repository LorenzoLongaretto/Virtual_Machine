#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "traductor.h"


void load_register(char v_mnemonics[]){
    FILE *arch;
    int lineaActual=0;
    char *filename="prueba.txt",auxline[100], finalLine[100],firstword[100];//finalLine es la linea sin rotulo ni comentarios
    arch=fopen(filename,"rt");
    if(arch!=NULL){
        while(fgets(auxline,100,arch)!=NULL){
            //sscanf(auxline,"%s",firstword);
            if(valid_line(auxline,v_mnemonics))
            {
                strcpy(auxline,strtok(auxline,";"));//Elimina los comenarios

                if(only_label(auxline) != NULL)   //Elimina los rotulos, revisar doble llamado, problema:only label devuelve char o NULL
                    strcpy(auxline,only_label(auxline));
                    printf("%s\n", auxline);
                //printf("%d \n",filtranum(auxline));
               // find_nmemonic() encuentra el nemonico y en caso de que no exista establece error

                lineaActual++;
            }
            //printf("%d", lineaActual); Indica el nro de linea, solo tiene en cuenta las lineas validas
            //printf("%d ",filtranum);
        }

    }


    fclose(arch);
}

int main(int argc, char *argv[])
{
    char v_mnemonics[24];
    create_mnemonics(v_mnemonics);
    load_register(v_mnemonics);

    return 0;
}
