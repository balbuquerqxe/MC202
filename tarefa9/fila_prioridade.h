#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vetor_tipos.h"

#define PAI(i) ((i - 1) / 2) // Define o pai.
#define F_ESQ(i) (2 * i + 1) // Define o filho esquerdo de i.
#define F_DIR(i) (2 * i + 2) // Define o filho direito de i.

typedef struct fp *p_fp; // Representa o ponteiro da fila de prioridade.

typedef struct
{
    int chave;         // Prioridade do objeto.
    int codigo_objeto; // Tipo de objeto.
} objeto;

struct fp
{
    objeto *v; // Vetor, alocado dinamicamente, de itens.
    int ocupadas;
    int tamanho; // Quantidade ocupada e quantidade máxima.
};

/* Essa função cria a fila de prioridade.*/
p_fp cria_filaprio(int tamanho);

/* Essa função insere um elemento na fila de prioridade.*/
void insere(int *armazena_posicao, p_fp fprio, objeto elemento);

/* Essa função sobe na lista de prioridade o objeto inserido, organizando-a.*/
void sobe_no_heap(int *armazena_posicao, p_fp fprio, int k);

/* Essa função troca a posição de um objeto com a de outro na lista de prioridade.*/
void troca(int *armazena_posicao, objeto *a, objeto *b);

/* Essa função checa se o objeto já esta no cache.*/
int checa_cache(int *armazena_posicao, int *sequencia, int i, int comprimento);

/* Essa função desce o objeto no heap, mantendo a lista de prioridade organizada.*/
void desce_no_heap(int *armazena_posicao, p_fp fprio, int k);

/* Essa função atualiza a posição que o objeto se encontra no cache.*/
int posicao_no_heap(p_fp fprio, int *sequencia, int i, v_t *vetor_tipos, int comprimento);

/* Essa função libera a fila de prioridades.*/
void destroi_filaprio(p_fp fila);

/* Essa função destroi a fila que armazena as posições de cada tipo de objeto.*/
void destroi_fila(p_fila fila);

/* Realiza todas as mudanças no cache.*/
void modifica_cache(int *armazena_posicao, v_t *vetor_tipos, int *sequencia, p_fp fila_prioridade, int tamanho, int tipos, int comprimento, int mudancas);