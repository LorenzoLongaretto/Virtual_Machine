typedef struct nodo{
    char label[50];
    int line;
     struct nodo *sig;
}nodo;
typedef nodo* TLista;

void create_mnemonics(char v_mnemonics[24][5]);

int is_mnemonic(char str[], char v_mnemonics[24][5]);

int is_label(char str[]);

int valid_line(char str[], char v_mnemonics[24][5]);

void clean_comments();

char *only_label(char str[]);

int filter_num(char auxline[]);

int find_nmemonic(char *mnem,char v_mnemonics[24][5]);
