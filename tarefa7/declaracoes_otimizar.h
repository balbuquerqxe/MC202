#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define a estrutura de cada nó na árvore.
typedef struct no *p_no;
struct no
{              /* Estrtura de cada nó presente na árvore.*/
    char dado; // Caractere armazenado.
    p_no esq;  // Filho esquerdo.
    p_no dir;  // Filho direito.
    p_no pai;  // Pai (lembrar que a raiz não possui pai).
};

// Funções relacionadas à estruturação da árvore.
p_no cria_no(char caractere, p_no esq, p_no dir, p_no pai); /* Cria a árvore*/
p_no distribuicao_arvore(p_no raiz);                        /* Organização de cada caractere na árvore.*/
p_no folha_desocupada(p_no raiz);                           /* Se direciona ao próximo nó que não está completado.*/
p_no encontra_raiz(p_no raiz);                              /* Encontra a raiz principal, a qual não deve possuir pai.*/
void destroi_arvore(p_no raiz);                             /* Destrói a árvore, liberando memória.*/

// Função relacionada à exibição da árvore.
void imprime_arvore(p_no raiz); /*Imprime a árvore na ordem: filho direito, pai, filho esquerdo.*/

// Função relacionada às negações presente na fórmula.
p_no modifica_exclamacao(p_no raiz); /* Retira casos de dupla negação e modifica operadores quando estão sob negação.*/

// Funções relacionadas à simplificação da árvore.
p_no simplifica_expressao(p_no raiz);            /* Evita redundâncias.*/
int subarvores_iguais(p_no folha1, p_no folha2); /* Examina se duas subárvores são iguais.*/