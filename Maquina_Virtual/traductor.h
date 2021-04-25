typedef struct nodo{
    char label[50];
    int line;
     struct nodo *sig;
}nodo;
typedef nodo* TLista;

void create_mnemonics(char v_mnemonics[24][5]);

void create_registers(char vec[16][3]);

int is_mnemonic(char str[], char v_mnemonics[24][5]);

int is_label(char str[]);

int valid_line(char str[]);

char *only_label(char str[]);

int find_nmemonic(char *mnem,char v_mnemonics[24][5]);

void add_label(TLista *L, char x[],int actual_line);

int is_register(char x[],char v_registers[][3]);

int find_register(char ARG[],char v_registers[][3]);

void change_char(char str[]);

void clean_arg(char str[], char aux[]);

int find_label(TLista L,char x[]);

void opereitor1(char ARG[], int *salida, TLista L_label, int *tipo, int *error, char v_registers[]);
