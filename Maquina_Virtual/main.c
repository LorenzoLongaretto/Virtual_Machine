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

int filtranum(char auxline[]){
int num,i,j=0;
char straux[100];
    for (i=0;i<strlen(auxline);i++)
        if (auxline[i]>='0' && auxline[i]<='9'){
            straux[j]=auxline[i];
            straux[j+1]="\0";
            j++;
        }
    if (straux[0]!='\0')
        return atoi(straux); //pasa string a decimal
    else
        return -1;
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
            printf("%s", auxline);
            //printf("%s\n",only_label(auxline));
            printf("%d \n",filtranum(auxline));
        }
        //printf("%d ",filtranum);
    }


    fclose(arch);
}

int main(int argc, char *argv[])
{
    load_register();
    return 0;
}
