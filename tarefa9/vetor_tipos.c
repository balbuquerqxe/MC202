#include "fila_prioridade.h"

/* Essa função cria um vetor com os tipos de objetos e, dentro de cada tipo, uma fila com as posições que aparecem.*/
void criacao_vetor_tipos(v_t *vetor_tipos, int tipos, int comprimento, int *sequencia)
{
	int auxiliar = 0;
	int i = 0;
	for (i = 0; i < tipos; i++)
	{
		vetor_tipos[i].lista = criar_fila(); // Cria uma fila para cada tipo de objeto, onde serão inseridas as posições.
		vetor_tipos[i].quantidade = 0;		 // Quantidade inicial é zero.
	}
	for (i = 0; i < comprimento; i++)
	{
		scanf("%d", &auxiliar);					   // Armazena temporariamente.
		sequencia[i] = auxiliar;				   // Vai preenchendo um array com os elementos da sequência.
		enfileira(vetor_tipos[auxiliar].lista, i); // Enfileiro a posição no seu determinado tipo de objeto.
		vetor_tipos[auxiliar].quantidade++;		   // Aumenta a quantidade.
	}
}

/* Essa função cria a fila que armazenará as posições que um tipo de objeto aparece.*/
p_fila criar_fila()
{
	p_fila fila = malloc(sizeof(struct fila));
	fila->ini = NULL; // Começa vazia.
	fila->fim = NULL; // Termina vazia.
	return fila;
};

/* Essa função enfileira as posições que o tipo de objeto aparece.*/
void enfileira(p_fila f, int posicao)
{
	p_no novo = malloc(sizeof(struct no)); // Armazena o nó que conterá a posição.
	novo->prioridade = posicao;			   // A prioridade será a posição que aparece, sempre.
	novo->prox = NULL;
	if (f->ini == NULL) // Se for o primeiro elemento.
		f->ini = novo;
	else					 // Se não for uma fila vazia.
		f->fim->prox = novo; // O próximo do último elemento.
	f->fim = novo;
}

/* Essa função desenfileira a posição da fila quando já tiver passado por ela.*/
void desenfileira(p_fila fila)
{
	p_no primeiro = fila->ini;
	fila->ini = fila->ini->prox; // Diminuiu a fila.
	if (fila->ini == NULL)
		fila->fim = NULL;
	free(primeiro);
}

/* Essa função destroi o vetor que aloca os tipos de objetos e suas informações.*/
void destroi_vetor_tipos(v_t *vetor_tipos, size_t tipos)
{
	if (vetor_tipos != NULL)
	{ // Verifica se o vetor não é vazio.
		for (size_t i = 0; i < tipos; i++)
		{
			destroi_fila(vetor_tipos[i].lista); // Libera a fila associada ao tipo de objeto.
		}
		free(vetor_tipos); // Libera o vetor por si só.
	}
}