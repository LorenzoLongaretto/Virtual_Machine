typedef struct label_struct( //para los ignorantes label=rotulo
char label[];
int pos;
struct label_struct *sig;)label_struct;
typedef label_struct *label_list;

