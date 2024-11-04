#include "funcoes.h"

int main()
{
    int dimensao = 0;
    scanf("%d", &dimensao);                                     // Dimensão do mapa.
    p_no arvore = cria_arvore(Vazio, dimensao, 0, 0, dimensao); // Criação da árvore que forma o mapa.
    arvore = comandos_arvore(arvore);                           // Recebe os comandos de adição, remoção e busca.
    destroi_arvore(arvore);                                     // Libera a memória.
    printf("Sistema encerrado.");
    return 0;
}