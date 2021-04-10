#include <stdio.h>
#include <stdlib.h>
<<<<<<< Updated upstream
#include "1.h"


int main()
{
    //int aux = primero();hbhj
    int aux2 = segundo();
    printf("Entro main!\n");
=======
#include <string.h>
#include "instrucciones.h"
#include "traductor.h"

void load_register(char v_mnemonics[]){
    FILE *arch;
    int lineaActual=0;
    char *filename="prueba.txt",auxline[100], finalLine[100];//finalLine es la linea sin rotulo ni comentarios
    arch=fopen(filename,"rt");
    if(arch!=NULL){
        while(fgets(auxline,100,arch)!=NULL){
            //if(valid_line(auxline,v_mnemonics))
            {
                strcpy(auxline,strtok(auxline,";"));//Elimina los comenarios
                if(only_label(auxline) != NULL)   //Elimina los rotulos, revisar doble llamado, problema:only label devuelve char o NULL
                    strcpy(auxline,only_label(auxline));
                printf("%s\n", auxline);
                //printf("%d \n",filtranum(auxline));
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
>>>>>>> Stashed changes
    return 0;
}
