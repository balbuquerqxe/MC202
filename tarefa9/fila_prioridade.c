#include "fila_prioridade.h"

/* Essa função cria a fila de prioridade.*/
p_fp cria_filaprio(int tamanho)
{
    p_fp fprio = malloc(sizeof(struct fp));      // Aloca fila de prioridade.
    fprio->v = malloc(tamanho * sizeof(objeto)); // Quantos itens no cache.
    fprio->ocupadas = 0;                         // Começa vazia, sem posições ocupadas.
    fprio->tamanho = tamanho;                    // Tamanho do cache.
    return fprio;                                // Devolve a fila de prioridade.
}

/* Essa função insere um elemento na fila de prioridade.*/
void insere(int *armazena_posicao, p_fp fprio, objeto elemento)
{
    fprio->v[fprio->ocupadas] = elemento;                       // Adiciono o elemento na última posição disponível na fila de prioridades.
    armazena_posicao[elemento.codigo_objeto] = fprio->ocupadas; // Armazeno a posição que o elemento foi inserido no cache.
    fprio->ocupadas++;                                          // Acrescento em uma unidade a quantidade ocupada no cache.
    sobe_no_heap(armazena_posicao, fprio, fprio->ocupadas - 1); // Organizo o elemento inserido no cache no heap.
}

/* Essa função sobe na lista de prioridade o objeto inserido, organizando-a.*/
void sobe_no_heap(int *armazena_posicao, p_fp fprio, int k)
{
    if (k > 0 && fprio->v[PAI(k)].chave < fprio->v[k].chave)
    {
        troca(armazena_posicao, &fprio->v[k], &fprio->v[PAI(k)]); // Se o pai for menor, troco com o filho.
        sobe_no_heap(armazena_posicao, fprio, PAI(k));            // Chamo recursivamente para organizar a lista inteira.
    }
}

/* Essa função troca a posição de um objeto com a de outro na lista de prioridade.*/
void troca(int *armazena_posicao, objeto *a, objeto *b)
{
    int auxiliar = armazena_posicao[a->codigo_objeto]; // Auxilia no vetor que armazena a posição no cache de cada objeto.
    objeto t = *a;
    armazena_posicao[a->codigo_objeto] = armazena_posicao[b->codigo_objeto]; // Troca a posição no cache.
    *a = *b;                                                                 // Troca os objetos de posição.
    armazena_posicao[b->codigo_objeto] = auxiliar;                           // Troca a posição no cache.
    *b = t;                                                                  // Troca os objetos de posição.
}

/* Essa função checa se o objeto já esta no cache.*/
int checa_cache(int *armazena_posicao, int *sequencia, int i, int comprimento)
{
    if (armazena_posicao[sequencia[i]] == comprimento) // Se a posição no cache for igual ao comprimento da sequência...
        return 1;                                      //... não encontrou o objeto no cache (retorna 1).
    return 0;                                          // Encontrou o objeto no cache (retorna 0).
}

/* Essa função desce o objeto no heap, mantendo a lista de prioridade organizada.*/
void desce_no_heap(int *armazena_posicao, p_fp fprio, int k)
{
    int maior_filho;
    if (F_ESQ(k) < fprio->ocupadas)
    {
        maior_filho = F_ESQ(k);
        if (F_DIR(k) < fprio->ocupadas &&
            fprio->v[F_ESQ(k)].chave < fprio->v[F_DIR(k)].chave)
            maior_filho = F_DIR(k);
        if (fprio->v[k].chave < fprio->v[maior_filho].chave)
        {
            troca(armazena_posicao, &fprio->v[k], &fprio->v[maior_filho]);
            desce_no_heap(armazena_posicao, fprio, maior_filho);
        }
    }
}

/* Essa função atualiza a posição que o objeto se encontra no cache.*/
int posicao_no_heap(p_fp fprio, int *sequencia, int i, v_t *vetor_tipos, int comprimento)
{
    int posicao_fila; // Posição na fila de prioridade que o objeto se encontra.
    for (posicao_fila = 0; posicao_fila < fprio->ocupadas; posicao_fila++)
        if (fprio->v[posicao_fila].codigo_objeto == sequencia[i]) // Se a informação armazenada for igual ao objeto no momento atual da sequência...
            return posicao_fila;                                  //... retorna a posição na fila de prioridade.
    return 0;
}

/* Essa função libera a fila de prioridades.*/
void destroi_filaprio(p_fp fila)
{
    if (fila != NULL)
    {                  // Verifica se a fila não é nula.
        free(fila->v); // Libera o array de objetos.
        free(fila);    // Libera a estrutura da fila.
    }
}

/* Essa função destroi a fila que armazena as posições de cada tipo de objeto.*/
void destroi_fila(p_fila fila)
{
    p_no atual = fila->ini; // Começa no início da fila
    p_no temp;

    // Libera todos os nós da fila
    while (atual != NULL)
    {
        temp = atual;
        atual = atual->prox;
        free(temp); // Libera o nó atual
    }

    free(fila); // Libera a estrutura da fila
}

/* Realiza todas as mudanças no cache.*/
void modifica_cache(int *armazena_posicao, v_t *vetor_tipos, int *sequencia, p_fp fila_prioridade, int tamanho, int tipos, int comprimento, int mudancas)
{
    int i = 0;
    for (i = 0; i < comprimento; i++)
    {
        objeto item;
        item.codigo_objeto = sequencia[i];             // Será o objeto em uma determinada posição na sequência.
        desenfileira(vetor_tipos[sequencia[i]].lista); // Desenfileira a posição que já passou.

        if (vetor_tipos[sequencia[i]].lista->ini != NULL)                  // Se ainda faltam ocorrências desse objeto...
            item.chave = vetor_tipos[sequencia[i]].lista->ini->prioridade; //.. a prioridade será a posição da próxima ocorrência.
        else
            item.chave = comprimento;                                      // Caso o objeto não apareça mais, a sua prioridade de remoção será máxima.
        if (checa_cache(armazena_posicao, sequencia, i, comprimento) == 1) // Checa se o objeto está no cache.
        {
            // Se o objeto já estiver no cache...
            if (fila_prioridade->ocupadas < tamanho) // Quando a fila de prioridade não estiver toda ocupada.
            {
                insere(armazena_posicao, fila_prioridade, item); // Insere o objeto na fila de prioridade.
                mudancas++;                                      // Contabiliza uma mudança.
            }
            else // Quando a fila de prioridade já estiver cheia...
            {
                troca(armazena_posicao, &fila_prioridade->v[0], &item); //... troca o objeto da sequência pelo de maior prioridade.
                desce_no_heap(armazena_posicao, fila_prioridade, 0);    // Reorganiza a fila, descendo no heap.
                mudancas++;                                             // Contabiliza uma mudança.
            }
        }
        else // Quando o objeto já estáno cache.
        {
            troca(armazena_posicao, &fila_prioridade->v[armazena_posicao[item.codigo_objeto]], &item); // Troca a prioridade do objeto.
            sobe_no_heap(armazena_posicao, fila_prioridade, armazena_posicao[item.codigo_objeto]);     // Reorganiza a fila, subindo no heap.
        }
    }
    printf("%d\n", mudancas); // Imprime a quantidade de mudanças.
}