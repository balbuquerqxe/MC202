#include <stdio.h>

#define maximo 1000   // Conforme o enunciado, o maior tamanho da lista é 1000.

void le_numeros (int lista[maximo], int n);   // Lerá os números.

void soma_numeros (int lista[maximo], int n);   // Soma parcial.

void imprime_numeros (int lista[maximo], int n);   // Imprime os números na ordem contrária.

void le_numeros (int lista[maximo], int n) {
    int i;
    for (i = 0; i < n; i++)
        scanf("%d", &lista[i]);   // "Listando" os números inseridos.
}

void soma_numeros (int lista[maximo], int n) {
    int i;
    for (i = 1; i < n; i++)
        lista[i] = lista[i] + lista[i-1];   // A partir do segundo número da lista, ele será a sua soma com o anterior.
}

void imprime_numeros (int lista[maximo], int n) {
    int i;
    for (i = n - 1; i > -1; i--) 
        printf("%d ", lista[i]);
}

int main () {
    
    int n, lista[maximo];   // Quantidade de números que serão inseridos.
    scanf("%d", &n);

    le_numeros(lista, n);
    soma_numeros(lista, n);
    imprime_numeros(lista, n);

    return 0;
}

