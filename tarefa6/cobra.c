#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cobra_implementacao.h"
#define MAX_COMANDO 7

int main()
{
    int total_linhas = 0;
    int total_colunas = 0;
    int continua = 1;
    char **p_matriz;
    p_cobra cobra = cria_cobra(); // Devemos criar a cobra.
    while (continua == 1)
    {
        char comando[MAX_COMANDO] = "";             // Instrução passada pelo usuário.
        scanf(" %s", comando);              // Leitura do comando.
        if (strcmp(comando, "MATRIZ") == 0) // Caso o comando seja "COBRA".
            p_matriz = alocacao_matriz(&total_colunas, &total_linhas);
        else if (strcmp(comando, "COBRA") == 0) // Caso o comando seja "COBRA".
            comando_cobra(p_matriz, total_colunas, total_linhas, cobra, &continua);
        else if (strcmp(comando, "FRUTA") == 0) // Caso o comando seja "FRUTA".
            comando_fruta(p_matriz, total_colunas, total_linhas, cobra, &continua);
        else
            comando_deslocamento(p_matriz, total_colunas, total_linhas, cobra, &continua, comando);
    }
    destroi_matriz(p_matriz, total_linhas);
    destroi_cobra(cobra);
}