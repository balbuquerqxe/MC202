#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cobra_implementacao.h"

struct pedaco_cobra /* Registra as informações de um segmento da cobra.*/
{
    int linha;           // Qual linha se encontra.
    int coluna;          // Qual coluna se encontra.
    p_pedaco_cobra prox; // Aponta para o próximo nó.
    p_pedaco_cobra ant;  // Aponta para o nó anterior.
};

struct cobra /* Registra qual é o primeiro e o último segmento da cobra.*/
{
    p_pedaco_cobra cabeca; // Registra qual é a cabeça (se fosse uma fila, seria o último inserido).
    p_pedaco_cobra fim;    // Registra qual é o fim (se fosse uma fila, seria o primeiro).
};

char **alocacao_matriz(int *total_colunas, int *total_linhas) /* Aloca a matriz.*/
{
    int linhas, colunas, i,j;
    scanf("%d %d", &linhas, &colunas);               // Registra o número de linhas e de colunas.
    char **matriz = malloc(linhas * sizeof(char *)); // Ponteiro da matriz que será criada.
    for (i = 0; i < linhas; i++) {
        matriz[i] = (char *)malloc(colunas * sizeof(char));
        for (j = 0; j < colunas; j++)
            matriz[i][j] = '_';
    }
    *total_linhas = linhas;   // Registra na variável global (para ser acessado pelas outras funções).
    *total_colunas = colunas; // Registr na variável global (para ser acessado pelas outras funções).
    return matriz;            // Retorna a matriz, agora, alocada.
}

void cria_matriz(char **p_matriz, int total_colunas, int total_linhas, p_cobra cobra) /* Essa função completa os espaços da matriz.*/
{
    int i, j;
    for (i = 0; i < total_linhas; i++)
        for (j = 0; j < total_colunas; j++)
            if (p_matriz[i][j] != '*') // Se a posição não tiver fruta, será, inicialmente, vazia.
                p_matriz[i][j] = '_';  // Mostra que está vazia/ sem cobra.

    p_pedaco_cobra segmento = cobra->fim; // Analisa as posições ocupadas pela cobra até chegar na sua cabeça.

    while (segmento != NULL)
    {
        p_matriz[segmento->linha][segmento->coluna] = '#'; // Insere a cobra na matriz.
        segmento = segmento->prox;                         // Parte para o próximo segmento.
    }
    free(segmento); // Destroi o segmento para não ocupar espaço na memória.
}

void imprime_matriz(char **p_matriz, int total_colunas, int total_linhas) /* Essa função imprime a matriz com as posições vazias, frutas e cobra.*/
{
    int i, j;
    for (i = 0; i < total_linhas; i++)
    {
        for (j = 0; j < total_colunas; j++)
            printf("%c ", p_matriz[i][j]);
        printf("\n"); // Precisa pular linha no final.
    }
}

void destroi_matriz(char **p_matriz, int i) /* Essa função destroi a matriz.*/
{
    for (int j = 0; j < i; j++)
        free(p_matriz[j]); // Libera a memória alocada até o momento que falhou.
    free(p_matriz);
}

void comando_deslocamento(char **p_matriz, int total_colunas, int total_linhas, p_cobra cobra, int *continua, char comando[MAX_COMANDO]) /* Possibilita o deslocamento da cobra.*/
{
    int linha_cabeca, coluna_cabeca;                                                        // Define as novas coordenadas da cabeça da cobra.
    linha_cabeca = correcao_posicao_linha(total_linhas, cobra->cabeca->linha, comando);     // Precisa corrigir quando passa da margem.
    coluna_cabeca = correcao_posicao_coluna(total_colunas, cobra->cabeca->coluna, comando); // Precisa corrigir quando passa da margem.

    if (p_matriz[linha_cabeca][coluna_cabeca] != '#') // Se o lugar da nova cabeça não é cobra, o jogo continua.
    {
        cobra->cabeca = aumenta_cobra(linha_cabeca, coluna_cabeca, cobra); // A cabeça se desloca na matriz.
        // Se, anteriormente, a cobra só possuia um segmento, o fim da cobra tem que apontar para a nova cabeça.
        if (cobra->cabeca->ant->linha == cobra->fim->linha && cobra->cabeca->ant->coluna == cobra->fim->coluna)
            cobra->fim->prox = cobra->cabeca;
        // Se a cobra se deslocou e não comeu a fruta, o seu fim precisa ser mudado.
        if (p_matriz[linha_cabeca][coluna_cabeca] == '_')
            cobra->fim = muda_fim(cobra);

        cria_matriz(p_matriz, total_colunas, total_linhas, cobra); // Modifica a matriz após o deslocamento.
        imprime_matriz(p_matriz, total_colunas, total_linhas);     // Imprime a matriz após o deslocamento.
        printf("\n");
        *continua = checa_vitoria(p_matriz, total_colunas, total_linhas); // Verifica se a cobra completou toda a matriz (vitória).
    }
    else // Se a cobra "bateu" no seu corpo, o jogo chega ao seu fim.
    {
        *continua = 0;         // Modifica o ponteiro para terminar o loop.
        printf("GAME OVER\n"); // Fim.
    }
}

int correcao_posicao_linha(int total, int posicao, char comando[MAX_COMANDO]) /* Indica a nova posição da cabeça e a corrige quando passa da margem.*/
{
    if (strcmp(comando, "a") == 0 || strcmp(comando, "d") == 0) // Permanece na mesma linha.
        return posicao;
    else if (strcmp(comando, "w") == 0) // A cabeça se desloca para cima.
    {
        if ((posicao - 1) >= 0)
            return posicao - 1;
        else
            return total - 1; // Ultrapassou a margem.
    }
    else // A cabeça se desloca para baixo.
    {
        if ((posicao + 1) >= total)
            return 0;
        else
            return posicao + 1; // Ultrapassou a margem.
    }
}

int correcao_posicao_coluna(int total, int posicao, char comando[MAX_COMANDO]) /* Indica a nova posição da cabeça e a corrige quando passa da margem.*/
{
    if (strcmp(comando, "w") == 0 || strcmp(comando, "s") == 0) // Permanece na mesma coluna.
        return posicao;
    else if (strcmp(comando, "a") == 0) // A cabeça se desloca para esquerda.
    {
        if ((posicao - 1) >= 0)
            return posicao - 1;
        else
            return total - 1; // Ultrapassou a margem.
    }
    else // A cabeça se desloca para direita.
    {
        if ((posicao + 1) >= total)
            return 0;
        else
            return posicao + 1; // Ultrapassou a margem.
    }
}

int checa_vitoria(char **p_matriz, int total_colunas, int total_linhas) /* Analisa se toda a matriz foi ocupada pela cobra.*/
{
    int i, j;
    for (i = 0; i < total_linhas; i++)
        for (j = 0; j < total_colunas; j++)
            if (p_matriz[i][j] != '#') // Existe, ainda, espaço vazio ou preenchido por fruta.
                return 1;              // Jogo deve continuar.
    printf("YOU WIN\n");
    return 0; // Fim de jogo, já que a matriz foi inteira preenchida.
}

p_cobra cria_cobra() /* Cria a cobra como vazia.*/
{
    p_cobra c = malloc(sizeof(struct cobra)); // Aloca um espaço na memória para a cobra.
    c->cabeca = NULL;                         // Começa vazia.
    c->fim = NULL;                            // Termina vazia.
    return c;
}

void comando_cobra(char **p_matriz, int total_colunas, int total_linhas, p_cobra cobra, int *continua) /*Insere o primeiro segmento de cobra na matriz.*/
{
    int linha, coluna;
    scanf("%d %d", &linha, &coluna);                           // Indica a posição inicial da cobra.
    cobra->cabeca = cria_pedaco_cobra(linha, coluna);          // Indica a posição inicial da cabeça.
    cobra->fim = cobra -> cabeca;
    cria_matriz(p_matriz, total_colunas, total_linhas, cobra); // Basicamente, insere a cobra na matriz.
}

p_pedaco_cobra cria_pedaco_cobra(int linha, int coluna) /* Cria um "nó" da cobra.*/
{
    p_pedaco_cobra c = malloc(sizeof(struct pedaco_cobra)); // Aloca na memória.
    c->linha = linha;                                       // Começa vazia.
    c->coluna = coluna;                                     // Termina vazia.
    c->prox = NULL;
    c->ant = NULL;
    return c;
}

p_pedaco_cobra aumenta_cobra(int linha, int coluna, p_cobra cobra) /* Aumenta o tamanho da cobra quando ela anda ou come uma fruta.*/
{
    p_pedaco_cobra c = malloc(sizeof(struct pedaco_cobra)); // Será a nova cabeça da cobra.
    c->linha = linha;                                       // Nova posição da cabeça.
    c->coluna = coluna;                                     // Nova posição da cabeça.
    cobra->cabeca->prox = c;                                // A antiga cabeça apontará para a nova cabeça como próxima.
    c->prox = NULL;                                         // A próxima da cabeça nova deve ser NULL.
    c->ant = cobra->cabeca;                                 // O anterior da cabeça nova será a antiga.
    return c;
}

p_pedaco_cobra muda_fim(p_cobra cobra) /* Muda o fim da cobra quando ela se desloca.*/
{
    p_pedaco_cobra auxiliar = cobra->fim->prox;
    auxiliar->ant = NULL;
    free(cobra->fim);
    return auxiliar;
}

void destroi_segmento(p_pedaco_cobra segmento)
{
    if (segmento != NULL)
    {
        destroi_segmento(segmento->prox);
        free(segmento);
    }
}

void destroi_cobra(p_cobra cobra)
{
    if (cobra != NULL)
    {
        destroi_segmento(cobra->fim);
        free(cobra);
    }
}

void comando_fruta(char **p_matriz, int total_colunas, int total_linhas, p_cobra cobra, int *continua) /* Indica a posição da fruta.*/
{
    int linha, coluna;
    scanf("%d %d", &linha, &coluna);                // Posição da fruta na matriz.
    adiciona_desenho(p_matriz, coluna, linha, '*'); // Devemos adicionar o desenho da fruta na matriz.
    imprime_matriz(p_matriz, total_colunas, total_linhas);
    printf("\n");
}

void adiciona_desenho(char **p_matriz, int coluna, int linha, char desenho) /* Essa função adiciona o desenho da fruta na matriz.*/
{
    p_matriz[linha][coluna] = desenho;
}