# include <stdio.h>

# define maximo 100

void leitura_matriz (int matriz[maximo][maximo], int n_linhas, int n_colunas);
void minimo_linha (int matriz[maximo][maximo], int n_linhas, int n_colunas);
int maximo_coluna (int matriz[maximo][maximo], int n_linhas, int y_menor_linha, int i, int existencia_sela_horizontal);
void imprime_ponto (int matriz[maximo][maximo],int i, int y_menor_linha, int existencia_sela_horizontal, int existencia_sela_vertical);
void sem_sela ();

int main () {
    int matriz[maximo][maximo],n_linhas, n_colunas;
    scanf("%d %d", &n_linhas, &n_colunas);

    leitura_matriz (matriz, n_linhas, n_colunas);
    minimo_linha (matriz, n_linhas, n_colunas);

    return 0;
}

void leitura_matriz (int matriz[maximo][maximo], int n_linhas, int n_colunas) {
    int i, j;

    for (i = 0; i < n_linhas; i++)   // Assim, irá escanear a primeira linha inteira, depois a segunda...
        for (j = 0; j < n_colunas; j++)
            scanf ("%d", &matriz[i][j]);
}

void minimo_linha (int matriz[maximo][maximo], int n_linhas, int n_colunas){
    int i, j, menor_linha, y_menor_linha;
    int ponto_sela_achado = 1;

    for (i = 0; i < n_linhas; i ++) {
        menor_linha = matriz[i][0];
        y_menor_linha = 0;
        int existencia_sela_horizontal = 0;   // Verifica se a sela pode existir na linha (se não for igual a nenhum número da linha e menor).
        
        for (j = 1; j < n_colunas; j ++)   // Aqui, estaremos armazenando qual é o menor número da linha e o comparando.
            if (matriz[i][j] < menor_linha) {
                menor_linha = matriz[i][j];
                y_menor_linha = j;
                existencia_sela_horizontal = 0;
            } else if (matriz[i][j] == menor_linha)
                existencia_sela_horizontal = 1;
            
        if (maximo_coluna (matriz, n_linhas, y_menor_linha, i, existencia_sela_horizontal) == 0){   // Após encontrar o menor número da linha, deemos compará-lo com os outros presentes na coluna para saber se é o maior.
            ponto_sela_achado = 0;
        }
    }
    if (ponto_sela_achado == 1)
        sem_sela ();
}

int maximo_coluna (int matriz[maximo][maximo], int n_linhas, int y_menor_linha, int i, int existencia_sela_horizontal){
    int k;
    int maior_coluna = matriz[0][y_menor_linha];
    int existencia_sela_vertical = 0;   // Verifica se a sela pode existir na coluna (se não for igual a nenhum número da coluna e maior).

    for (k = 1; k < n_linhas; k ++)
        if (maior_coluna < matriz[k][y_menor_linha]) {
            maior_coluna = matriz[k][y_menor_linha];
            existencia_sela_vertical = 0;

        } else if (matriz[k][y_menor_linha] == maior_coluna)
            existencia_sela_vertical = 1;
            
    if ((maior_coluna == matriz[i][y_menor_linha]) && (existencia_sela_horizontal == 0 && existencia_sela_vertical == 0)){   // Se o número for o maior da coluna, isso significa que encontramos a sela.
            imprime_ponto (matriz, i, y_menor_linha, existencia_sela_horizontal, existencia_sela_vertical);
            return 0;   // Indica ter encontrado um ponto sela.
    }
    return 1;   // Não encontrou um ponto de sela.            
}

void imprime_ponto (int matriz[maximo][maximo],int i, int y_menor_linha, int existencia_sela_horizontal, int existencia_sela_vertical) {
    printf ("(%d, %d) eh ponto de sela com valor %d\n", i, y_menor_linha, matriz[i][y_menor_linha]);
}

void sem_sela () {
    printf ("nao existe ponto de sela\n");

}