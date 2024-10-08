#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* O meu programa estará dividido em três partes principais, uma para cada forma de prepararmos os dados.*/

void lendo_matriz(float **p, int colunas, int linhas);
void liberando_matriz(float **p, int linhas);
int media(float **p, int colunas, int linhas);
int sem_estrategia(float **p, int colunas, int linhas);
int janela_estrategia(float **p, int colunas, int linhas);
int normal_estrategia(float **p, int colunas, int linhas);
void destroi_matriz(float **p, int i);

int main() {
    int colunas, linhas, i;

    // Leitura da dimensão (colunas) e do número de pontos (linhas).
    scanf("%d %d", &colunas, &linhas);

    float **p = malloc(linhas * sizeof(float *));   // Ponteiro da matriz que será criada.
    
    if (p == NULL) {
        return 1;   // Indica que houve um erro na alocação.
    }
    
    for (i = 0; i < linhas; i++) {
        p[i] = (float *) malloc(colunas * sizeof(float));
        if (p[i] == NULL) {
            destroi_matriz(p, i);
            return 1;   // Indica que houve um erro na alocação.
        }
    }
    
    lendo_matriz(p, colunas, linhas);

    if (sem_estrategia(p, colunas, linhas) == 1)  // Indica que houve erro em algum momento do processo.
        return 1;

    if (janela_estrategia(p, colunas, linhas) == 1)   // Indica que houve erro em algum momento do processo.
        return 1;

    if (normal_estrategia(p, colunas, linhas) == 1)   // Indica que houve erro em algum momento do processo.
        return 1;

    liberando_matriz(p, linhas);   // Libera o espaço usado na memória pela matriz.
    return 0;
}

void lendo_matriz(float **p, int colunas, int linhas) {   // Essa função lerá/ guardará todos os elementos da matriz.
    int i, j;
    for (i = 0; i < linhas; i++)
        for (j = 0; j < colunas; j++)
            scanf("%f", &p[i][j]);
}

void liberando_matriz(float **p, int linhas) {   // Essa função libera o espaço ocupado por uma matriz.
    int i;
    for (i = 0; i < linhas; i++)
        free(p[i]);
    free(p);
}

int media(float **p, int colunas, int linhas) {   // Realiza a média entre os elementos das colunas.
    int i, j;
    float *coluna = malloc(colunas * sizeof(float));  // Armazena a soma final de cada coluna.
    float *soma = malloc(colunas * sizeof(float));    // Resultado da soma de todas as linhas de uma coluna.

    if (coluna == NULL || soma == NULL) {
        free(coluna);
        free(soma);
        return 1;   // Indica que houve um erro na alocação.
    }

    for (j = 0; j < colunas; j++) {
        soma[j] = 0.0;
        for (i = 0; i < linhas; i++) 
            soma[j] += p[i][j];
        coluna[j] = soma[j] / linhas;
        printf("%f ", coluna[j]);  // Imprime a média.
    }

    printf("\n");
    free(coluna);   // Libera o espaço usado na memória para armazenar o centroide de cada coluna.
    free(soma);   // Libera o espaço usado na memória para armazenar as somas de cada coluna.
    return 0;
}

int sem_estrategia (float **p, int colunas, int linhas) {   // Como sem estratégia não muda nada, será apenas realizar uma média.
    printf("nenhum: ");
    
    if (media (p, colunas, linhas) == 1)
        return 1;
    return 0;
}

int janela_estrategia(float **p, int colunas, int linhas) {   // Modifica as coordenadas dos pontos.
    int i, j;
    float *min_coluna = malloc(colunas * sizeof(float));   // Precisa ser ponteiro para, assim, ser dinâmico e gastar menos espaço da memória.
    float *max_coluna = malloc(colunas * sizeof(float));   // Precisa ser ponteiro para, assim, ser dinâmico e gastar menos espaço da memória.
    float **nova_matriz = malloc(linhas * sizeof(float *));   // Precisa ser ponteiro para, assim, ser dinâmico e armazenar os elementos com as novas coordenadas da matriz.
    
    if (min_coluna == NULL || nova_matriz == NULL || max_coluna == NULL) {
        free(min_coluna);
        free(max_coluna);
        free(nova_matriz);
        return 1;   // Indica que houve um erro na alocação.
    }

    for (i = 0; i < linhas; i++) {
        nova_matriz[i] = (float *) malloc(colunas * sizeof(float));
        if (nova_matriz[i] == NULL) {
            destroi_matriz (nova_matriz, i);
            free(min_coluna);
            free(max_coluna);
            return 1;   // Indica que houve um erro na alocação.
        }
    }

    printf("janela: ");

    for (j = 0; j < colunas; j++)
        for (i = 0; i < linhas; i++) {
            if (i == 0)
                min_coluna[j] = max_coluna[j] = p[0][j];   // Busca encontrar o valor máximo e mínimo de cada coluna.
            if (p[i][j] > max_coluna[j])
                max_coluna[j] = p[i][j];
            if (p[i][j] < min_coluna[j])
                min_coluna[j] = p[i][j];
        }

    for (i = 0; i < linhas; i++)
        for (j = 0; j < colunas; j++) {
            if ((max_coluna[j]-min_coluna[j]) == 0)
                nova_matriz[i][j] = 0.000;   // Para não falar que deu erro, já que o número não pode ser dividido por zero.
            else
                nova_matriz[i][j] = (2.0*(p[i][j]-min_coluna[j])/(max_coluna[j]-min_coluna[j]))-1.0;   // Transformação do elemento conforme novo sistema de coordenadas.
        }

    if (media(nova_matriz, colunas, linhas) == 1) {
        liberando_matriz(nova_matriz, linhas);
        free(min_coluna);
        free(max_coluna);
        return 1;   // Indica que houve um erro no processamento.
    }

    // Liberar memória alocada.
    free(min_coluna);
    free(max_coluna);;
    liberando_matriz(nova_matriz, linhas);
    return 0;
}

int normal_estrategia(float **p, int colunas, int linhas) {
    int i, j;
    float **nova_matriz = malloc(linhas * sizeof(float *));   // Precisa ser ponteiro para, assim, ser dinâmico e gastar menos espaço da memória.
    float *comprimento = malloc(linhas * sizeof(float));  // Precisa ser ponteiro para, assim, ser dinâmico e gastar menos espaço da memória.
    float *soma = malloc(linhas * sizeof(float)); // Precisa ser ponteiro para, assim, ser dinâmico e gastar menos espaço da memória.

    if (nova_matriz == NULL || comprimento == NULL || soma == NULL) {
        free(nova_matriz); // Libera a memória em caso de falha
        free(comprimento);
        free(soma);
        return 1;   // Indica que houve um erro na alocação.
    }

    printf("normal: ");
    
    // Cálculo dos comprimentos
    for (i = 0; i < linhas; i++){
        soma[i] = 0.0;
        for (j = 0; j < colunas; j++)
            soma[i] += (p[i][j] * p[i][j]);
        comprimento[i] = (float) sqrt(soma[i]);
    }

    // Alocação da nova matriz
    for (i = 0; i < linhas; i++) {
        nova_matriz[i] = (float *) malloc(colunas * sizeof(float));
        if (nova_matriz[i] == NULL) {
            destroi_matriz (nova_matriz, i);
            free(comprimento);
            free(soma);
            return 1;   // Indica que houve um erro no processamento.
        }
    }

    for (i = 0; i < linhas; i++) {
        if (comprimento[i] == 0) {  // Não aceita se o comprimento for zero, já que seria dividido por zero.
            destroi_matriz (nova_matriz, linhas);
            free(comprimento);
            free(soma);
            return 1;   // Indica que houve um erro no processamento.
        }
        for (j = 0; j < colunas; j++)
            nova_matriz[i][j] = p[i][j] / comprimento[i];      // Transformação do elemento conforme novo sistema de coordenadas.
    }
    
    if (media(nova_matriz, colunas, linhas) == 1) {
        liberando_matriz(nova_matriz, linhas);
        return 1;     // Indica que houve erro no processamento.
    }
    
    // Liberar memória alocada
    free(comprimento);
    free(soma);
    liberando_matriz(nova_matriz, linhas);
    return 0;
}

void destroi_matriz(float **p, int i) {
    for (int j = 0; j < i; j++)
        free(p[j]);   // Libera a memória alocada até o momento que falhou.
    free(p);
}