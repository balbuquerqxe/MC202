#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define max 20

typedef struct lista_ligada *p_sequencia;

struct lista_ligada
{
    char letra[2];    // Alocação correta para um caractere e o terminador '\0'
    int posicao;      // Indica qual é a sua posição.
    p_sequencia prox; // Aponta para o próximo núcleo-base.
};

p_sequencia cria_lista();
p_sequencia insere_base(p_sequencia dna);
p_sequencia modifica_ordem(p_sequencia nova_base);
p_sequencia exclui_base(p_sequencia base, int posicao_excluida, int comando);
p_sequencia diminui_posicao(p_sequencia base);
p_sequencia inversao(p_sequencia base, int inicio, int fim);
p_sequencia armazena_base(p_sequencia base, int sentido);
p_sequencia transposicao(p_sequencia dna, int inicio, int fim, int quantidade_casas);
p_sequencia copia_base(p_sequencia original);
void imprime(p_sequencia dna, int tamanho, int inicio);
void destroi_lista(p_sequencia dna);
void limpa_comando(char *comando);

int main()
{
    int rodar_codigo = 1;
    int quantidade_bases = 0;
    char comando[max] = "";         // Instrução passada pelo usuário.
    p_sequencia dna = cria_lista(); // Lista vazia.

    while (rodar_codigo == 1) // Enquanto for "1", o código deve rodar.
    {
        scanf(" %s", comando); // Leitura do comando.

        if (strcmp(comando, "inserir") == 0) // Caso o comando seja "inserir".
        {
            dna = insere_base(dna); // Função irá modificar a variável DNA, implemenando-a.
            quantidade_bases += 1;  // Mais uma base no DNA.
        }
        else if (strcmp(comando, "remover") == 0) // Caso o comando seja "remover".
        {
            int posicao_excluida;
            scanf(" %d", &posicao_excluida); // Registra qual posição deve ser excluída.

            dna = exclui_base(dna, posicao_excluida, 1);
            /* Observação: o valor 1 é utilizado para diferenciar o prósito da função "exclui_base".
            Quando for 1: o comando do usuário era de remoção.
            Quando for 0: o comando do usuário era de transposição. */

            quantidade_bases -= 1; // Diminui a quantidade de bases no DNA.
        }
        else if (strcmp(comando, "inverter-prefixo") == 0) // Caso o comando seja "inverter-prefixo".
        {
            int tamanho;
            scanf(" %d", &tamanho); // Quantas bases devem ser invertidas.
            printf("prefixo");
            imprime(dna, tamanho, 0);            // Imprime as bases antes da inversão.
            dna = inversao(dna, 0, tamanho - 1); // Modifica a variável DNA para que tenha as bases invertidas.
            printf(" ->");
            imprime(dna, tamanho, 0); // Imprime as bases após a inversão.
            printf("\n");
        }
        else if (strcmp(comando, "inverter-sufixo") == 0) // Caso o comando seja "inverter-sufixo".
        {
            int tamanho;
            scanf(" %d", &tamanho); // Quantas bases devem ser invertidas.
            printf("sufixo");
            imprime(dna, quantidade_bases, quantidade_bases - tamanho);            // Imprime as últimas bases do DNA (serão invertidas).
            dna = inversao(dna, quantidade_bases - tamanho, quantidade_bases - 1); // Modifica a variável DNA.
            printf(" ->");
            imprime(dna, quantidade_bases, quantidade_bases - tamanho); // Imprime as bases após a inversão.
            printf("\n");
        }
        else if (strcmp(comando, "transpor") == 0) // Caso o comando seja "transpor".
        {
            int inicio, fim, quantidade_casas;
            scanf(" %d %d %d", &inicio, &fim, &quantidade_casas); // A partir de qual base, até qual, número de posições deslocadas.
            printf("subsequencia");
            dna = transposicao(dna, inicio, fim, quantidade_casas);              // Modifica DNA.
            imprime(dna, fim + quantidade_casas + 1, inicio + quantidade_casas); // Imprime as bases que serão deslocadas.
            if (quantidade_casas > 0)
                printf(" >> %d", quantidade_casas); // Se o deslocamento for para direita.
            else
            {
                quantidade_casas = -quantidade_casas;
                printf(" << %d", quantidade_casas); // Se o deslocamento dor para esquerda.
            }
            printf("\n");
        }
        else if (strcmp(comando, "imprimir") == 0) // Caso o comando seja "imprimir".
        {
            printf("sequencia");
            imprime(dna, quantidade_bases, 0);
            printf("\n");
        }

        else if (strcmp(comando, "sair") == 0) // Caso o comando seja "sair".
            rodar_codigo = 0;                  // Fim do código.

        limpa_comando(comando); // Eu sei que não há necessidade, já que ocorre automaticamente. Porém, prefiro deixar sempre "limpo".
    }

    destroi_lista(dna); // Libera a memória alocada.
    return 0;
}

p_sequencia cria_lista()
{
    return NULL; // Cria uma lista vazia.
}

void destroi_lista(p_sequencia dna)
{
    if (dna != NULL) // Se a lista ligada não for vazia...
    {
        destroi_lista(dna->prox); //... devemos liberar seu espaço e o próximo nó.
        free(dna);
    }
}

void limpa_comando(char *comando)
{
    /* Não há necessidade dessa função, mas eu prefiro para que todos os
    caracteres da função sejam sempre '\0', sem sobrar nenhum "lixo". */

    for (int i = 0; i < max; i++)
        comando[i] = '\0'; // Define todos os caracteres da string como '\0'.
}

p_sequencia insere_base(p_sequencia dna)
{
    p_sequencia nova_base = malloc(sizeof(struct lista_ligada)); // Alocação dinâmica para a nova base.

    if (nova_base == NULL)
    {
        fprintf(stderr, "Erro de alocação de memória\n");
        exit(1); // Fim do programa em caso de erro de alocação (não é possível continuar).
    }

    scanf(" %1s %d", nova_base->letra, &nova_base->posicao); // Leitura da letra e da posição.
    printf("%1s inserido em %d\n", nova_base->letra, nova_base->posicao);
    nova_base->prox = dna;           // Indica que o próximo nó será o DNA (insere na lista ligada).
    dna = modifica_ordem(nova_base); // Modifica a ordem para a posição ser sempre crescente.

    return dna;
}

p_sequencia modifica_ordem(p_sequencia base)
{
    p_sequencia anterior = base;
    p_sequencia atual = base->prox;
    p_sequencia seguinte = NULL;

    if (atual != NULL) // Se o atual fosse NULL, não haveria um próximo.
        seguinte = atual->prox;

    if (atual == NULL || atual->posicao > anterior->posicao) // Indica que a ordem já está correta.
        return anterior;

    else if (anterior->posicao == atual->posicao) // Indica que todos precisam andar uma posição para a direita.
    {
        atual->posicao += 1;
        anterior->prox = modifica_ordem(atual);
        return anterior;
    }
    else if (atual->posicao < anterior->posicao) // Indica que ainda não chegou no lugar que deve ser inserido.
    {
        p_sequencia auxiliar; // Crio o auxiliar para conseguir armazenar as informações do nó "anterior".

        atual->prox = anterior;    // O seguinte do atual será o anterior.
        anterior->prox = seguinte; // O próximo do anterior será o seguinte.
        auxiliar = anterior;
        anterior = atual;                       // Modifica o nome.
        atual = auxiliar;                       // Modifica o nome.
        anterior->prox = modifica_ordem(atual); // Realiza recursão para organizar o resto da lista.
        return anterior;
    }

    return 0;
}

p_sequencia exclui_base(p_sequencia base, int posicao_excluida, int comando)
{
    if (base == NULL)
    {
        return NULL; // Lista vazia, nada a excluir.
    }

    p_sequencia anterior = NULL;
    p_sequencia atual = base;

    if (posicao_excluida == 0) // Remove o primeiro nó (posição 0).
    {
        if (comando == 1) //
            printf("%1s removido de %d\n", atual->letra, posicao_excluida);
        p_sequencia nova_base = atual->prox; // Aponta para o próximo nó.
        free(atual);                         // Libera a memória do nó removido.
        return diminui_posicao(nova_base);   // Ajusta as posições e retorna a nova base.
    }

    while (atual != NULL && atual->posicao != posicao_excluida) // Percorre a lista até encontrar o nó na posição a ser excluída.
    {
        anterior = atual;
        atual = atual->prox;
    }

    if (comando == 1) // Ou seja, o propósito da função era somente excluir uma base.
        printf("%1s removido de %d\n", atual->letra, posicao_excluida);

    if (atual != NULL) // Se encontrou o nó a ser removido.
    {
        anterior->prox = atual->prox; // Remove o nó da lista.
        free(atual);                  // Libera a memória do nó removido.
    }

    return diminui_posicao(base); // Ajusta as posições dos nós seguintes.
}

p_sequencia diminui_posicao(p_sequencia base)
{
    p_sequencia atual = base;
    int nova_posicao = 0; // Começa em 0 para garantir que o primeiro nó fique com posição 0.

    while (atual != NULL) // Ajusta as posições dos nós a partir do primeiro
    {
        atual->posicao = nova_posicao; // Define a nova posição.
        nova_posicao++;                // Incrementa a posição para o próximo nó.
        atual = atual->prox;
    }

    return base; // Retorna a lista ligada com as posições arrumadas.
}

p_sequencia inversao(p_sequencia base, int inicio, int fim)
{
    if (base == NULL)
    {
        return base; // Caso a lista seja NULL, a sua inversão também será NULL.
    }

    p_sequencia ponteiro_inicio = base; // Encontra o nó correspondente à posição 'inicio'.
    for (int i = 0; i < inicio; i++)
    {
        if (ponteiro_inicio == NULL)
            return base; // Caso a lista termine antes de 'inicio', deve ser mantida igual.
        ponteiro_inicio = ponteiro_inicio->prox;
    }

    p_sequencia ponteiro_fim = base; // Encontra o nó correspondente à posição 'fim'.
    for (int i = 0; i < fim; i++)
    {
        if (ponteiro_fim == NULL)
            return base; // Caso a lista termine antes de 'fim' (importante para os casos de inversão de sufixo).
        ponteiro_fim = ponteiro_fim->prox;
    }

    // Cria uma lista temporária para armazenar as letras das bases que estão entre 'inicio' e 'fim'.
    int tamanho = fim - inicio + 1;
    char letras[10000]; // Lista com as letras.
    p_sequencia temp = ponteiro_inicio;
    for (int i = 0; i < tamanho; i++)
    {
        letras[i] = temp->letra[0]; // Armazena as letras no formato de uma lista encadeada!! (Parte mais difícil do código achei)
        temp = temp->prox;
    }

    temp = ponteiro_inicio;
    for (int i = tamanho - 1; i >= 0; i--) // Reescreve as letras, invertidas, de volta na lista.
    {
        temp->letra[0] = letras[i];
        temp = temp->prox;
    }
    return base; // Retorna a lista com a sequência invertida.
}

p_sequencia armazena_base(p_sequencia base, int sentido)
{
    while (base->posicao != sentido)
        base = base->prox;
    return base;
}

p_sequencia copia_base(p_sequencia base)
{
    p_sequencia copia = malloc(sizeof(struct lista_ligada));
    copia->posicao = base->posicao;
    copia->letra[0] = base->letra[0];
    copia->letra[1] = '\0';
    copia->prox = NULL; // Inicialmente, a cópia não deve apontar para o próximo.
    return copia;
}

p_sequencia transposicao(p_sequencia dna, int inicio, int fim, int quantidade_casas)
{
    for (int i = inicio; i <= fim; i++)
    {
        p_sequencia base_transposta = cria_lista();

        // Armazena a base correta dependendo se o movimento é para a direita ou esquerda.
        if (quantidade_casas > 0)
            base_transposta = armazena_base(dna, inicio); // Desloca para a direita.
        else
            base_transposta = armazena_base(dna, fim); // Desloca para a esquerda.

        p_sequencia copia_base_transposta = copia_base(base_transposta); // Cria uma cópia de base_transposta.

        dna = exclui_base(dna, base_transposta->posicao, 0); // Exclui a base original.
        /* Observação: o valor 0 é utilizado para diferenciar o prósito da função "exclui_base".
        Quando for 1: o comando do usuário era de remoção.
        Quando for 0: o comando do usuário era de transposição. */

        // Ajusta a nova posição, dependendo se o deslocamento é para a direita (+) ou esquerda (-).
        if (quantidade_casas > 0)
        {
            copia_base_transposta->posicao = fim + quantidade_casas; // Desloca para a direita.
        }
        else
        {
            copia_base_transposta->posicao = inicio + quantidade_casas; // Desloca para a esquerda.
        }

        copia_base_transposta->prox = dna;

        dna = modifica_ordem(copia_base_transposta); // Reinsere a base na nova posição.
    }
    return dna;
}

void imprime(p_sequencia dna, int tamanho, int inicio) // Imprime as bases indicadas (desde o início até o fim informado).
{
    while (dna->posicao != inicio)
        dna = dna->prox;
    while (inicio < tamanho)
    {
        printf(" %1s", dna->letra);
        inicio += 1;
        dna = dna->prox;
    }
}