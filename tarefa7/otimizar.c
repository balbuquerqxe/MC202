#include "declaracoes_otimizar.h"

int main()
{
    p_no raiz = cria_no('?', NULL, NULL, NULL); // Crio a raiz da árvore, a qual deve ser liberada no final.
    raiz = distribuicao_arvore(raiz);           // Faço a distribuição da árvore a partir de cada caractere.
    imprime_arvore(raiz);                       // Imprimo a estrutura da árvore na ordem filho esquerdo, pai, filho direito.
    printf("\n");
    raiz = modifica_exclamacao(raiz); // Modifico a árvore para os casos que possuem dupla negação.
    imprime_arvore(raiz);             // Imprimo a estrutura da árvore após modificá-la.
    printf("\n");
    raiz = simplifica_expressao(raiz); // Simplifico a expressão.
    imprime_arvore(raiz);              // Imprimo a estrutura da árvore após simplificá-la.
    destroi_arvore(raiz);
    return 0;
}