#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int valid_line(char *line){


}
void clean_comments(){

}
char *only_label(char auxline[]){

return strchr(auxline,":");
}

void load_register(){
    FILE *arch;
    int i=0;
    char *filename="prueba.txt",auxline[100];
    arch=fopen(filename,"rt");
    if(arch!=NULL)
    {
        while(fgets(auxline,100,arch)!=NULL){
            strcpy(auxline,strtok(auxline,";"));
            printf("%s\n", auxline);
            printf("%s\n",only_label(auxline));
        }
    }


    fclose(arch);
}

int main(int argc, char *argv[])
{
    load_register();
    return 0;
}
