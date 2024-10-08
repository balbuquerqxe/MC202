#include <stdio.h>

/* Devo criar um programa que veja a probabilidade de Maria chegar em João*/

double probabilidade_cada_caso (int quantidade_jogadas, int distancia);

int main () {
    int quantidade_jogadas, distancia;   // Quantas vezes João pode jogar o dado e distância entre os dois.
    scanf("%d %d", &quantidade_jogadas, &distancia);
    
    double probabilidade = probabilidade_cada_caso (quantidade_jogadas, distancia);   // Como eu entro em uma "árvore de possibilidades", eu só preciso usar recursão. 
    printf ("%.3f\n", probabilidade);
    
    return 0;
}

double probabilidade_cada_caso (int quantidade_jogadas, int distancia) {
    int face;   // Qual foi a face que caiu do dado, podendo, assim, variar de 1 a 6.
    
    if ((quantidade_jogadas <= 0 && distancia != 0) || (distancia < 0))   // Isso significa que a Maria não conseguiu chegar no Pedro.
            return 0.0;
    
    if (quantidade_jogadas >= 0 && distancia == 0)   // Quando sobrou jogadas ou foi exatamente a quantidade certa de jogadas e Maria chegou no Pedro.
            return 1.0;

    double soma = 0.0;
    for (face = 1; face <= 6; face ++)   // Precisa testar cada uma das faces do dado.
        soma += (1.0/6.0) * probabilidade_cada_caso (quantidade_jogadas - 1, distancia - face);   // Vou somando as probabilidades (que são sempre multiplicadas por 1/6, já que é 1 de 6 faces do dado).
    return soma;
}