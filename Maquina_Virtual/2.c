#include "1.h"
#include<string.h>
#include <stdio.h>
#include <stdlib.h>

int segundo()
{
//ERASE UNA VEZ
    char linea[256], *token;
    FILE *arch;
    arch = fopen("prueba.txt","rt");
    if(arch == NULL)
        return 1;
    char *token = strtok(linea,":");
    printf("%10d | %s", strlen(linea), *token);
    while(fgets(linea, 256, arch) != NULL){
        //printf("%10d | %s", strlen(linea), linea);
        printf("%10d | %s", strlen(linea), *token);
    }
    strcmp(palabras[i],':')
    fclose(arch);
    printf("Priemro!\n");
    return 0;
}
