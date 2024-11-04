#include "declaracoes_otimizar.h"

p_no modifica_exclamacao(p_no raiz) /* Modifica casos de dupla negação.*/
{
    if (raiz == NULL)
        return raiz; // Chegou ao fim da recursão.

    if (raiz->dado == '!') // Quando o caractere for de negação.
    {
        p_no prox = raiz->esq;

        if (prox->dado == '&') // Inverte o operador "&"" para "|".
        {
            prox->dado = '|';      // Realiza troca.
            prox->pai = raiz->pai; // Corta o "!" da árvore.
            if (raiz->pai != NULL)
            {
                if (raiz->pai->esq == raiz) // Se "!" era filh esquerdo...
                    raiz->pai->esq = prox;  // ... o próximo será filho esquerdo.
                else
                    raiz->pai->dir = prox; // Caso contrário, será o filho direito.
            }
            free(raiz);
            p_no temp_esq = prox->esq;
            p_no temp_dir = prox->dir;

            prox->esq = cria_no('!', temp_esq, NULL, prox); // Preciso passar a negação ("!") para os próximos nós.
            prox->dir = cria_no('!', temp_dir, NULL, prox); // Preciso passar a negação ("!") para os próximos nós.
            raiz = prox;
        }
        else if (prox->dado == '|') // Inverte o operador "|" para "&".
        {
            prox->dado = '&';      // Realiza troca.
            prox->pai = raiz->pai; // Corta o "!" da árvore.
            if (raiz->pai != NULL)
            {
                if (raiz->pai->esq == raiz) // Se "!" era filh esquerdo...
                    raiz->pai->esq = prox;  // ... o próximo será filho esquerdo.
                else
                    raiz->pai->dir = prox; // Caso contrário, será o filho direito.
            }
            free(raiz);

            prox->esq = cria_no('!', prox->esq, NULL, prox); // Preciso passar a negação ("!") para os próximos nós.
            prox->dir = cria_no('!', prox->dir, NULL, prox); // Preciso passar a negação ("!") para os próximos nós.
            raiz = prox;
        }
        else if (prox->dado == '!') // Remove a dupla negação "!!".
        {
            p_no auxiliar = prox->esq;
            if (raiz->pai != NULL)
            {
                if (raiz->pai->esq == raiz) // Indica ser o filho esquerdo.
                    raiz->pai->esq = auxiliar;
                else
                    raiz->pai->dir = auxiliar; // Indica ser o filho direito.
            }
            auxiliar->pai = raiz->pai; // Atualiza o pai, "pulando" a dupla negação.
            free(raiz);
            free(prox);
            raiz = auxiliar;
            return modifica_exclamacao(raiz); // Precio chamar recursivamente para ter certeza que não tem outro "!".
        }
    }

    // Recursão para garantir que irá passar por todos os nós da árvore.
    raiz->esq = modifica_exclamacao(raiz->esq);
    raiz->dir = modifica_exclamacao(raiz->dir);
    return raiz;
}
