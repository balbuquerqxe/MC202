#define MAX_COMANDO 7

// Estruturas da cobra.
typedef struct pedaco_cobra *p_pedaco_cobra; /* Representa o ponteiro para o nó.*/
typedef struct cobra *p_cobra;               /* Representa o ponteiro para a cobra.*/

// Funções associadas à manipulação da matriz.
char **alocacao_matriz(int *total_colunas, int *total_linhas);                         /* Verifica se há espaço na memória para criar a matriz.*/
void cria_matriz(char **p_matriz, int total_colunas, int total_linhas, p_cobra cobra); /* Cria a matriz.*/
void imprime_matriz(char **p_matriz, int total_colunas, int total_linhas);             /* Imprime a matriz.*/
void destroi_matriz(char **p_matriz, int i);                                           /* Destroi a matriz no final do código.*/

// Funções relacionadas ao deslocamento da cobra.
void comando_deslocamento(char **p_matriz, int total_colunas, int total_linhas, p_cobra cobra, int *continua, char comando[MAX_COMANDO]); /* Análise de qual comando foi passado.*/
int correcao_posicao_linha(int total, int posicao, char comando[MAX_COMANDO]);                                                            /* Corrige a posição da linha se ultrapassar a margem.*/
int correcao_posicao_coluna(int total, int posicao, char comando[MAX_COMANDO]);                                                           /* Corrige a posição da coluna se ultrapassar a margem.*/
int checa_vitoria(char **p_matriz, int total_colunas, int total_linhas);                                                                  /* Checa se o deslocamento possibilitu a vitória.*/

// Funções relacionadas às mudanças do corpo da cobra.
p_cobra cria_cobra();                                                                                   /* Cria a cobra inicial, vazia.*/
void comando_cobra(char **p_matriz, int total_colunas, int total_linhas, p_cobra cobra, int *continua); /*Insere o primeiro segmento de cobra.*/
p_pedaco_cobra cria_pedaco_cobra();                                                                     /* Cria um "nó" da cobra.*/
p_pedaco_cobra aumenta_cobra(int linha, int coluna, p_cobra cobra);                                     /* Aumenta o tamanho da cobra quando ela anda ou come uma fruta.*/
p_pedaco_cobra muda_fim(p_cobra cobra);                                                                 /* Muda o fim da cobra quando ela se desloca.*/
void destroi_segmento(p_pedaco_cobra segmento);                                                         /* Destroi segmento da cobra para não ocupar espaço.*/
void destroi_cobra(p_cobra cobra);                                                                      /* Destroi a cobra por inteira.*/

// Funções relacionadas à criação de uma fruta.
void comando_fruta(char **p_matriz, int total_colunas, int total_linhas, p_cobra cobra, int *continua); /* Indica a posição que a fruta deve estar.*/
void adiciona_desenho(char **p_matriz, int linha, int coluna, char desenho);                            /*Adiciona o desenho de fruta na matriz.*/