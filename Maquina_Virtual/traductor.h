typedef struct nodo{
    char label[50];
    int line;
     struct nodo *sig;
}nodo;
typedef nodo* TLista;

void create_mnemonics(char v_mnemonics[24][5]);

int is_mnemonic(char str[], char v_mnemonics[24][5]);

int is_label(char str[]);

int valid_line(char str[]);

void clean_comments();

char *only_label(char str[]);

int filter_num(char auxline[]);

int find_nmemonic(char *mnem,char v_mnemonics[24][5]);

void opereitor1(char ARG[], int *salida, TLista L_label, int *tipo, int *error, char v_registers[]);
void add_label(TLista *L, char x[],int actual_line);
