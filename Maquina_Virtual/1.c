#include "1.h"
#include<string.h>
#include <stdio.h>
#include <stdlib.h>

int primero()
{

    char linea[256];
    FILE *arch;
    arch = fopen("prueba.txt","rt");
    if(arch == NULL)
        return 1;
    while(fgets(linea, 256, arch) != NULL){
        printf("%10d | %s", strlen(linea), linea);
    }
    fclose(arch);
    printf("Priemro!\n");
    return 0;
}

