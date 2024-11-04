#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define MAX 11 // Máximo de caracteres no nome da cidade.

typedef struct no *p_no; // Define a estrutura de cada nó da árvore.

// Lista os tipos de nós.
enum tipo_no
{
    Interno,
    Vazio,
    Ocupado
};

// Estrutura do nó.
struct no
{
    int extremo_dir;   // Extremo direito coordenada X.
    int extremo_esq;   // Extremo esquerdo coordenada X.
    int extremo_baixo; // Extremo baixo coordenada Y.
    int extremo_cima;  // Extremo cima coordenada Y.

    enum tipo_no tipo; // Tipo de nó da árvore.

    union
    {
        struct
        {
            p_no NO;
            p_no NE;
            p_no SO;
            p_no SE;
        }; // Estrutura do nó interno.
        struct
        {
            int vazio;
        }; // Estrutura do nó vazio.
        struct
        {
            char nome[MAX];
            int posicao_x;
            int posicao_y;
        }; // Estrutura do nó ocupado.
    };
};

/* Funções auxiliares.*/
p_no cria_arvore(enum tipo_no tipo, int extremo_dir, int extremo_esq, int extremo_baixo, int extremo_cima); // Cria a árvore.
p_no comandos_arvore(p_no arvore);                                                                          // Recebe comandos para modificar a árvore ou buscar cidades.
void destroi_arvore(p_no arvore);                                                                           // Destroi a árvore.

/* Funções de inserção de uma cidade no mapa.*/
p_no insercao(p_no arvore);                                                        // Insere cidade.
p_no recursao_insercao(p_no arvore, int posicao_x, int posicao_y, char nome[MAX]); // Insere recursivamente a cidade.

/* Funções de remoção de uma cidade do mapa.*/
p_no remocao(p_no arvore);                                        // Remove uma cidade.
p_no recursao_remocao(p_no arvore, int posicao_x, int posicao_y); // Remove recursivamente a cidade.
p_no regiao_vazia(p_no arvore);                                   // Modifica o tipo de nó da região quando ela se encontra vazia ou só com uma cidade.

/* Funções relacionadas à busca de cidades.*/
void busca_ponto(p_no arvore, int posicao_x, int posicao_y);             // Busca cidade a partir de suas coordenadas.
void busca_regiao(p_no arvore, int raio, int centro_x, int centro_y);    // Busca cidade dentro de um raio determinado.
double distancia(p_no arvore, int centro_x, int centro_y);               // Calcula a distância entre a cidade e o centro.
int verificar_regiao(p_no arvore, int raio, int centro_x, int centro_y); // Verifica se naquela região podem haver cidades dentro do raio.