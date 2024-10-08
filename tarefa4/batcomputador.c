#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define max 10            // Máximo de caracteres que a função chamada possui no nome.
#define tamanho_inicial 8 // Tamanho inicial do vetor.

typedef struct Vetor
{
    int *valores;            // Números que serão armazenados.
    int posicoes_usadas;     // Indica quantas posições de fato estão sendo usadas.
    int posicoes_reservadas; // Indica com qual tamanho o vetor foi alocado.
} *vetor_dinamico;

vetor_dinamico criar_vetor();                                     // Essa função cria o vetor.
void batalloc(vetor_dinamico batvetor);                           // Faz a alocação dos elementos do vetor.
int espaco_vazio(vetor_dinamico batvetor, int quantidade, int i); // Analisa se tem um espaço vazio que possa ser usado.
void expandir_vetor(vetor_dinamico batvetor);                     // Dobra o tamanho do vetor quando necessário.
void batfree(vetor_dinamico batvetor);                            // Libera o espaço.
int diminuir_vetor(vetor_dinamico batvetor);                      // Diminui pela metade o tamanho do vetor quando necessário.
void batprint(vetor_dinamico batvetor);                           // Imprime os elementos indicados.
void batuso(vetor_dinamico batvetor);                             // Mostra quanto do "espaço" do vetor está sendo usado.
void limparfuncao(char *funcao);                                  // Limpa o nome da função chamada (apenas para deixar mais organizado).
void destruir_vetor(vetor_dinamico batvetor);                     // Destroi o vetor no final do código.

int main()
{
    char funcao[max]; // Qual o nome da função que será chamada pelo Batman.
    int operacoes;    // Quantidade de comandos que serão inseridos.
    scanf("%d", &operacoes);

    vetor_dinamico batvetor = criar_vetor(); // Cria o vetor que será utilizado no Bat-Computador.

    for (int i = 0; i < operacoes; i++)
    {
        scanf("%s", funcao);
        if (strcmp(funcao, "bat-alloc") == 0) // Indica que a operação é a de alocação.
            batalloc(batvetor);
        else if (strcmp(funcao, "bat-free") == 0) // Indica que a operação é a de remoção.
            batfree(batvetor);
        else if (strcmp(funcao, "bat-print") == 0) // Indica que a operação é a de impressão.
            batprint(batvetor);
        else
            batuso(batvetor); // Indica que a operação é a de contabilizar o espaço usado.
        limparfuncao(funcao); // Limpa o nome salvo na variável "função".
    }
    destruir_vetor(batvetor); // Destroi o vetor quando ele acaba de ser usado.
    return 0;
}

vetor_dinamico criar_vetor()
{ // Essa função cria o vetor que será usado ao longo do código.
    int posicao_elemento = 0;
    vetor_dinamico batvetor = (vetor_dinamico)malloc(sizeof(struct Vetor)); // Indica o tamanho do vetor.
    batvetor->valores = malloc(tamanho_inicial * sizeof(int));              // Tamanho dados cada elemento;
    batvetor->posicoes_usadas = 0;                                          // O tamanho usado começa como zero, já que nada foi inserido.
    batvetor->posicoes_reservadas = tamanho_inicial;                        // Tamanho reservado começa sendo 8, como indicado pelo enunciado.
    for (posicao_elemento = 0; posicao_elemento < tamanho_inicial; posicao_elemento++)
        batvetor->valores[posicao_elemento] = 0; // Inicializo o vetor com todos os elementos nulos.
    return batvetor;
}

void limparfuncao(char *funcao)
{
    for (int i = 0; i < max; i++)
        funcao[i] = '\0'; // Define todos os caracteres da string como '\0'.
}

int espaco_vazio(vetor_dinamico batvetor, int quantidade, int posicao)
{
    if (quantidade == 0) // Isso indica que tem como armazenar sem aumentar o vetor, já que a quantidade de elementos que faltam ser armazenados chegou a 0 (não tem mais nenhum).
        return posicao;  // Número da posição
    else if (quantidade != 0 && posicao >= batvetor->posicoes_reservadas)
    {                             // Se ainda estiver faltando elementos a serem armazenados e a posição for maior ou igual ao limite reservado.
        expandir_vetor(batvetor); // Dobra o tamanho do vetor.
        return (espaco_vazio(batvetor, quantidade - 1, posicao + 1));
    }
    else if (batvetor->valores[posicao] == 0)                         // Realiza uma recursão para avaliar se cabem todos os elementos, já que nessa posição analisada cabe.
        return (espaco_vazio(batvetor, quantidade - 1, posicao + 1)); // Checa se na próxima posição cabe.
    else
        return -1; // Se a posição analisada está preenchida e a quantidade que falta para armazenar elementos é maior que 0 (falta colocar elementos).
}

void batalloc(vetor_dinamico batvetor)
{
    int quantidade, posicao = 0;
    int ultima_posicao, numero;
    scanf("%d", &quantidade);

    do
    {
        ultima_posicao = espaco_vazio(batvetor, quantidade + 1, posicao); // Analisa onde que tem espaços vazios em que eu possa colocar os números.
        posicao++;
    } while (ultima_posicao == -1); // Enquanto não encontrar um local.

    if (posicao - 1 < 0 || posicao - 1 >= batvetor->posicoes_reservadas)
    { // Houve algum erro!! Posição não corresponde ao tamanho do vetor!!
        fprintf(stderr, "Erro: Índice fora dos limites na alocação\n");
        exit(EXIT_FAILURE); // Preciso parar de operar o código, já que teve algum erro.
    }

    batvetor->valores[posicao - 1] = quantidade; // O primeiro elemento que vai ser escrito é o que simboliza a quantidade de próximos elementos.
    batvetor->posicoes_usadas++;                 // Aumenta uma posição usada.

    printf("%d\n", (posicao - 1)); // Imprime em que posição essa informação foi armazenada

    for (int j = 0; j < quantidade; j++)
    {
        if (posicao >= batvetor->posicoes_reservadas) // Se não couber, aumentar o vetor.
            expandir_vetor(batvetor);
        scanf("%d", &numero);
        batvetor->valores[posicao + j] = numero; // Registra qual é a posição de cada elemento.
        batvetor->posicoes_usadas++;             // Mostra que armazenou mais um número.
    }
}

void expandir_vetor(vetor_dinamico batvetor)
{
    int i;
    int novo_tamanho = batvetor->posicoes_reservadas * 2; // Eu preciso dobrar o tamanho do meu vetor quando não couberem novos elementos.
    int *novo_vetor = (int *)malloc(novo_tamanho * sizeof(int));

    if (novo_vetor == NULL)

    { // Se o vetor for vazio, dará erro.
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE); // Preciso paraaar de operar o código, já que teve algum erro.
    }

    for (i = 0; i < batvetor->posicoes_reservadas; i++)
    { // Copiar os valores do vetor antigo para o novo vetor expandido.
        novo_vetor[i] = batvetor->valores[i];
    }

    for (i = batvetor->posicoes_reservadas; i < novo_tamanho; i++)
    { // Inicializar as novas posições com 0.
        novo_vetor[i] = 0;
    }

    free(batvetor->valores); // Liberar o vetor antigo e apontar para o novo vetor.
    batvetor->valores = novo_vetor;
    batvetor->posicoes_reservadas = novo_tamanho;
}

void batfree(vetor_dinamico batvetor)
{
    int posicao, i;
    scanf("%d", &posicao);

    if (posicao < 0 || posicao >= batvetor->posicoes_reservadas || batvetor->valores[posicao] == 0)
    { // Houve algum erro!! Posição não corresponde ao tamanho do vetor!!
        printf("Erro: Posição inválida ou já liberada\n");
        return;
    }

    int quantidade = batvetor->valores[posicao]; // QUantidade de elementos que serão liberados.

    for (i = 0; i <= quantidade; i++)
    {                                       // Libera a posição onde a quantidade está armazenada e os próximos valores.
        batvetor->valores[posicao + i] = 0; // Marca as posições como liberadas (valor 0).
        batvetor->posicoes_usadas--;        // Atualiza o número de posições usadas.
    }
    if (batvetor->posicoes_reservadas >= 16 && batvetor->posicoes_usadas <= (batvetor->posicoes_reservadas / 4))
    { // O tamanho mínimo do meu vetor é 8, e não posso estar usando mais de 1/4 do espaço.
        diminuir_vetor(batvetor);
    }
}

int diminuir_vetor(vetor_dinamico batvetor)
{
    int posicao; // Posição do meu elemento.

    for (int depoisquarto = (batvetor->posicoes_reservadas / 4) + 1; depoisquarto < batvetor->posicoes_reservadas; depoisquarto++)
    { // Preciso checar se tem algum número depois de 1/4 do espaço do vetor. Se tiver, não posso diminuir o espaço.
        if (batvetor->valores[depoisquarto] != 0)
            return 0; // Não posso diminuir o espaço.
    }

    int novo_tamanho = batvetor->posicoes_reservadas / 2; // Novo tamanho do vetor.
    int *novo_vetor = (int *)malloc(novo_tamanho * sizeof(int));

    if (novo_vetor == NULL)
    { // Se o vetor for vazio, dará erro.
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE); // Preciso paraaar de operar o código, já que teve algum erro.
    }

    for (posicao = 0; posicao < novo_tamanho; posicao++) // Copiar os valores da metade usada para o novo vetor.
        novo_vetor[posicao] = batvetor->valores[posicao];

    free(batvetor->valores); // Liberar o vetor antigo e apontar para o novo vetor
    batvetor->valores = novo_vetor;
    batvetor->posicoes_reservadas = novo_tamanho;
    return 1;
}

void batprint(vetor_dinamico batvetor)
{ // Imprimo os valores que foram pedidos.
    int posicao = 0;
    int i;
    scanf("%d", &posicao);
    int quantidade = batvetor->valores[posicao]; // A quantidade é o número registrado naquela posição indicada.
    for (i = 1; i < quantidade; i++)
    {
        printf("%d ", batvetor->valores[posicao + i]);
    }
    printf("%d\n", batvetor->valores[posicao + quantidade]);
}

void batuso(vetor_dinamico batvetor)
{
    printf("%d de %d\n", batvetor->posicoes_usadas, batvetor->posicoes_reservadas); // Apenas imprimo o quanto foi usado das minhas posições reservadas.
}

void destruir_vetor(vetor_dinamico batvetor)
{ // Para não ficar gastando a memória, devo destruir o vetor.
    if (batvetor != NULL)
    { // Para não liberar duas vezes algo que já foi liberado.
        free(batvetor->valores);
        free(batvetor);
    }
}