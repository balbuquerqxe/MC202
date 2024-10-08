#include <stdio.h>
#include <string.h>
# define MAX 401   /* Precisamos considerar o '/0' */

int analise_palindromo (int *k, char palavra [MAX], int inicio, int fim);
int ultimo_caracter (char palavra [MAX]);

/* Devemos criar um programa que chega se uma palavra é quase um palíndromo. */
/* Preciso usar recursão. */

int main () {
    int k;   /* Máximo de caracteres diferentes*/
    char palavra[MAX];
    int fim;
    int inicio = 0;

    scanf("%d %s", &k, palavra);
    fim = ultimo_caracter (palavra);
    analise_palindromo (&k, palavra, inicio, fim);
    
    return 0;
}

int ultimo_caracter (char palavra[MAX]) {
    for (int i = 0; i < MAX; i++)
        if (palavra[i] == '\0') /* Indica que chegou ao último caracter da palavra.*/
            return (i-1);
    return 0;
}

int analise_palindromo (int *k, char palavra[MAX], int inicio, int fim) {

    if (inicio >= fim) {
        printf ("sim\n");
        return 0;
    }

    if (palavra[inicio] != palavra[fim])
        *k = *k - 2;

    if (*k < 0) {
        printf ("nao\n");
        return 0;
    } else
        analise_palindromo (k, palavra, inicio + 1, fim - 1);
    return 0;
}
