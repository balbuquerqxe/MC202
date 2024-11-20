#include "fila_prioridade.h"

int main()
{
    int tamanho = 0, tipos = 0, i = 0, mudancas = 0, comprimento = 0;   // Incializa as variáveis.
    scanf("%d %d %d", &tamanho, &tipos, &comprimento);                  // Tamanho do cache, quantidade de tipos de objetos, comprimento da sequencia.
    p_fp fila_prioridade = cria_filaprio(tamanho);                      // Cria a fila de prioridade.
    int *sequencia = (int *)malloc((size_t)comprimento * sizeof(int));  // Cria a sequencia de acesso dos objetos.
    v_t *vetor_tipos = (v_t *)malloc((size_t)tipos * sizeof(v_t));      // Armazena vetor com os tipos de objetos e suas informações.
    criacao_vetor_tipos(vetor_tipos, tipos, comprimento, sequencia);    // Cria vetor com os tipos de objetos e suas informações.
    int *armazena_posicao = (int *)malloc((size_t)tipos * sizeof(int)); // Cria array que armazena a posição no cache de cada tipo de objeto.

    for (i = 0; i < tipos; i++)
        armazena_posicao[i] = comprimento; // Inicializa para não dar erro de segmentação.

    modifica_cache(armazena_posicao, vetor_tipos, sequencia, fila_prioridade, tamanho, tipos, comprimento, mudancas); // Realiza as mudanças no cache.
    destroi_vetor_tipos(vetor_tipos, tipos);                                                                          // Libera a memória do vetor e suas filas.
    free(armazena_posicao);
    free(sequencia);
    destroi_filaprio(fila_prioridade); // Libera a memória da fila de prioridade.

    return 0;
}