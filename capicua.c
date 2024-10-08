#include <stdio.h>

void teste (long k) {

    long original = k;  
    long quociente = k;  
    long resto = 0;

    while (quociente !=0) {
        resto = resto*10 + quociente%10;   // Armazena o número "invertido".
        quociente = quociente/10;

    }

    if (resto == original) {   // Se o número original for igual ao invertido.
        printf ("%ld eh capicua\n", original);
    } else {
        printf ("%ld nao eh capicua\n", original);
    }


}


int main() {
    int n, i; // Quantidade de números digitados.

    scanf("%d",&n);

    for (i = 0; i < n; i++) {
        long k;   // Número que será testado como capicua.
        scanf("%ld", &k);
        teste (k); 
    }    
    
    return 0;
}