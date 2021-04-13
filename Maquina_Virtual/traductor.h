typedef struct nodo{
    char label[50];
    int line;
     struct nodo *sig;
}nodo;
typedef nodo* TLista;

void create_mnemonics(char v_mnemonics[24][5]);

int is_mnemonic(char string[], char v_mnemonics[24][5]);
int is_label(char string[]);

int valid_line(char string[], char v_mnemonics[24][5]);

void clean_comments();

char *only_label(char string[]);

int filter_num(char auxline[]);
int find_nmemonic(char *mnem,char v_mnemonics[24][5]);
