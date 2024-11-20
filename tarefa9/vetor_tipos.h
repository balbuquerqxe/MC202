#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tipos v_t;	 // Lista dos tipos de objetos.
typedef struct no *p_no;	 // Representa o ponteiro para o nó.
typedef struct fila *p_fila; // Representa o ponteiro para a fila de posições.

// Estrutura para cada tipo de objeto que aparece.
struct tipos
{
	p_fila lista;	// Lista com as posições que o tipo de objeto aparece.
	int quantidade; // Quantidade total de vezes que esse tipo de objeto aparece.
};

// Estrutura do nó da lista ligada das posições que o objeto aparece.
struct no
{
	int prioridade; // Valor da posição na chamada.
	p_no prox;		// Aponta para a posição do próximo (é um ponteiro).
};

struct fila
{
	p_no ini; // Início da fila.
	p_no fim; // Fim da fila.
};

/* Essa função cria um vetor com os tipos de objetos e, dentro de cada tipo, uma fila com as posições que aparecem.*/
void criacao_vetor_tipos(v_t *vetor_tipos, int tipos, int comprimento, int *sequencia);

/* Essa função cria a fila que armazenará as posições que um tipo de objeto aparece.*/
p_fila criar_fila();

/* Essa função enfileira as posições que o tipo de objeto aparece.*/
void enfileira(p_fila f, int posicao);

/* Essa função desenfileira a posição da fila quando já tiver passado por ela.*/
void desenfileira(p_fila fila);

/* Essa função destroi o vetor que aloca os ipos de objetos e suas informações.*/
void destroi_vetor_tipos(v_t *vetor_tipos, size_t tipos);
