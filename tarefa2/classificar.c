#include <stdio.h>
#include <string.h>

#define maximo_pacientes 100
#define maximo_caracteres 31   // No caso, serão 30; porém, temos que considerar o "nulo" no final.

void le_pacientes (char lista_pacientes[maximo_pacientes][maximo_caracteres], int quantidade_nomes);

void homonimos (char lista_pacientes[maximo_pacientes][maximo_caracteres], int quantidade_nomes, char palavra_buscada[maximo_caracteres]);

void parentes (char lista_pacientes[maximo_pacientes][maximo_caracteres], int quantidade_nomes, char palavra_buscada[maximo_caracteres]);

void imprime_pacientes (char lista_pacientes[maximo_pacientes][maximo_caracteres], int i);

int main () {
    int quantidade_nomes;
    char lista_pacientes[maximo_pacientes][maximo_caracteres], tematica[maximo_caracteres], palavra_buscada [maximo_caracteres];

    // Registra os nomes dos pacientes e a sua quantidade.
    scanf ("%d", &quantidade_nomes);   // Quantos pacientes foram, de fato, atendidos no dia.
    le_pacientes (lista_pacientes, quantidade_nomes);

    // Comando de busca (homonimos ou parentes).
    scanf (" %s %s", tematica, palavra_buscada);

    // Análise do que foi pedido (homonimos ou parentes).
    if (tematica[0] == 'h')   // Indica que o pedido de busca foi de homonimos.
        homonimos (lista_pacientes, quantidade_nomes, palavra_buscada);
    else
        parentes (lista_pacientes, quantidade_nomes, palavra_buscada);

    return 0;
}

void le_pacientes (char lista_pacientes[maximo_pacientes][maximo_caracteres], int quantidade_nomes){
    int i, j;

    for (i = 0; i < quantidade_nomes; i++){
        char nome_paciente[maximo_caracteres];   // Sempre "zerando" ao iniciar a leitura de um novo nome.

        scanf(" %s", nome_paciente);   // Passando o nome digitado para a variável.
        
        for (j = 0; j < maximo_caracteres; j++)
            lista_pacientes[i][j] = nome_paciente[j];   // Registrando o nome do paciente em uma lista.
    }
}

void homonimos (char lista_pacientes[maximo_pacientes][maximo_caracteres], int quantidade_nomes, char palavra_buscada[maximo_caracteres]) {
    int i;

    for (i = 0; i < quantidade_nomes; i++) {   // Irá passar por cada um dos nomes.

        int possibilidade = 0;   // Indica haver chance de ser homonimo.
        int j = 0;
        
        while (possibilidade == 0 && j< maximo_caracteres && lista_pacientes[i][j] != '_'){
            if (palavra_buscada[j] == lista_pacientes[i][j]){
                possibilidade = 0;   // Se as letras estão coencidindo, o programa deve continuar analisando as próximas.
                j++;
            } else
                possibilidade = 1;   // Pula para o próximo nome.
        }

        if (possibilidade == 0 && lista_pacientes[i][j] == '_' && palavra_buscada[j] == '\0')   // Indica que ambas as palavras chegaram ao seu fim.
            imprime_pacientes (lista_pacientes, i);   // Imprime o nome que for homonimo.
    }
}

void parentes (char lista_pacientes[maximo_pacientes][maximo_caracteres], int quantidade_nomes, char palavra_buscada[maximo_caracteres]){
    int i;

    for (i = 0; i < quantidade_nomes; i++) {   // Irá passar por cada um dos nomes.

        int j = 0;
        
        while (lista_pacientes[i][j] != '_')   // Está "pulando" as letras que compõem o nome para, assim, chegar no sobrenome.
            j++;
        
        j++;   // Posição da primeira letra do sobrenome.


        int possibilidade = 0;   // Indica haver chance de ser homonimo.
        int k = 0;

        while (palavra_buscada[k] != '\0' && lista_pacientes[i][j] != '\0'){
            if (palavra_buscada[k] == lista_pacientes[i][j]){
                j++;
                k++;
            } else {
                possibilidade = 1;   // Pula para o próximo nome.
                break;
            }   
        }
        
        if (possibilidade == 0)
            imprime_pacientes (lista_pacientes, i);   // Imprime o sobrenome que for comum.
    }
}

void imprime_pacientes (char lista_pacientes[maximo_pacientes][maximo_caracteres], int i) {
    
    printf("%s \n", lista_pacientes[i]);   // Imprime o sobrenome que for comum.
}