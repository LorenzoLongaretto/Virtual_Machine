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
<<<<<<< Updated upstream
    int lineaActual=0;
    char *filename="prueba.txt",auxline[100], finalLine[100];//finalLine es la linea sin rotulo ni comentarios
=======
    int lineaActual=0,pos;
    char *filename="prueba.txt",auxline[100], finalLine[100],firstword[100],label[10],mnem[50],first_arg[10],second_arg[10];//finalLine es la linea sin rotulo ni comentarios
    int32_t lineBinary;
>>>>>>> Stashed changes
    arch=fopen(filename,"rt");
    if(arch!=NULL){
        while(fgets(auxline,100,arch)!=NULL){
            //if(valid_line(auxline,v_mnemonics))
            {
                strcpy(auxline,strtok(auxline,";"));//Elimina los comenarios
<<<<<<< Updated upstream
                if(only_label(auxline) != NULL)   //Elimina los rotulos, revisar doble llamado, problema:only label devuelve char o NULL
                    strcpy(auxline,only_label(auxline));
                printf("%s\n", auxline);
                //printf("%d \n",filtranum(auxline));
                lineaActual++;
            }
=======

                if(only_label(auxline) != NULL){   //Elimina los rotulos, revisar doble llamado, problema:only label devuelve char o NULL
                        sscanf(auxline,"%s",label);//Guarda label
                        //listLabels(*l_labels,label);
                        strcpy(auxline,only_label(auxline));//Elimina rotulo
                }
                strcpy(first_arg,"NULL");//Nos avisa si NO hay operador
                strcpy(second_arg,"NULL");//Nos avisa si solo hay un operador
                sscanf(auxline,"%s %s %s",mnem,first_arg,second_arg);//Mnemonico y operandos
                strupr(mnem);strupr(first_arg);strupr(second_arg);
                printf("%s %s %s \n",mnem,first_arg,second_arg);
                strtok(first_arg,"],");//Dejamos pelado el primer operando
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
>>>>>>> Stashed changes
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
