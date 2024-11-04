#include "declaracoes_otimizar.h"

p_no retorno_e_liberacao(p_no expressao_retornada, p_no no_liberado, p_no raiz, char valor_retornado)
{
    p_no auxiliar = expressao_retornada; // O que deverá restar na árvore como expressão.

    if (auxiliar == raiz->esq || auxiliar == raiz->dir) // Preciso destruir o resto da árvore (outro lado + raiz).
    {
        destroi_arvore(no_liberado);
        free(raiz);
        return auxiliar;
    }
    else if (valor_retornado == 'F')
    {
        destroi_arvore(raiz);
        return cria_no('F', NULL, NULL, auxiliar);
    }
    else if (valor_retornado == 'T')
    {
        destroi_arvore(raiz);
        return cria_no('T', NULL, NULL, auxiliar);
    }

    return raiz; // Devolve a raiz.
}

p_no simplifica_expressao(p_no raiz) /* Retira possíveis redundâncias presentes na árvore.*/
{
    if (raiz == NULL)
        return raiz; // Chegou ao fim da recursão.

    // Ocorre a simplificação de "dentro" para "fora".
    raiz->esq = simplifica_expressao(raiz->esq);
    raiz->dir = simplifica_expressao(raiz->dir);

    if (raiz->dado == '&') // Simplificação para "&".
    {
        if (raiz->dir->dado == 'T') // Se o lado direito for verdadeiro, expressão se reduz para o outro lado.
            return retorno_e_liberacao(raiz->esq, raiz->dir, raiz, '\0');

        else if (raiz->esq->dado == 'T') // Se o lado esquerdo for verdadeiro, expressão se reduz para o outro lado.
            return retorno_e_liberacao(raiz->dir, raiz->esq, raiz, '\0');

        else if (raiz->dir->dado == 'F' || raiz->esq->dado == 'F') // Se o lado direito for falso, a expressão é falsa. Idem para lado esquerdo
            return retorno_e_liberacao(raiz->pai, raiz, raiz, 'F');

        else if (subarvores_iguais(raiz->dir, raiz->esq) == 1) // Se os dois lados forem iguais, simplifica para um dos lados.
            return retorno_e_liberacao(raiz->esq, raiz->dir, raiz, '\0');
    }
    else if (raiz->dado == '|') // Simplificação para "|".
    {
        if (raiz->dir->dado == 'T' || raiz->esq->dado == 'T') // Se o lado direito for verdadeiro, a expressão é verdadeira. Idem para lado esquerdo
            return retorno_e_liberacao(raiz->pai, raiz, raiz, 'T');

        else if (raiz->dir->dado == 'F') // Se o lado direito for falso, simplifica para o lado esquerdo
            return retorno_e_liberacao(raiz->esq, raiz->dir, raiz, '\0');

        else if (raiz->esq->dado == 'F') // Se o lado esquerdo for falso, simplifica para o lado direito
            return retorno_e_liberacao(raiz->dir, raiz->esq, raiz, '\0');

        else if (subarvores_iguais(raiz->dir, raiz->esq) == 1) // Se os dois lados forem iguais, simplifica para qualquer um dos lados
            return retorno_e_liberacao(raiz->esq, raiz->dir, raiz, '\0');
    }
    else if (raiz->dado == '!') // Simplificação para "!".
    {
        if (raiz->esq->dado == 'T') // O verdadeiro se torna falso.
            return retorno_e_liberacao(raiz->pai, raiz, raiz, 'F');

        else if (raiz->esq->dado == 'F') // O falso se torna verdadeiro.
            return retorno_e_liberacao(raiz->pai, raiz, raiz, 'T');
    }
    return raiz; // Se não houver simplificação possível, retorna a raiz sem modificá-la.
}

int subarvores_iguais(p_no folha1, p_no folha2)
{
    if (folha1 == NULL && folha2 == NULL) // Se as duas folhas forem "NULL", as subárvores chegaram ao final e são iguais.
        return 1;

    if (folha1 == NULL || folha2 == NULL) // Se apenas uma folha for "NULL", uma subárvore chegou ao final e a outra não (são diferentes).
        return 0;

    if (folha1->dado != folha2->dado) // Se os dados das folhas forem diferentes, as subárvores são diferentes.
        return 0;

    /* Demoramos muito nessa parte: precisamos checar se a subárvore1 é a mesma que a subárvore2. A questão é que,
    igual na matemática, não importa a ordem dos operadores. Logo, precisamos pensar nos casos que as subárvores
    são iguais mas possuem ramificações invertidas.*/
    return (subarvores_iguais(folha1->esq, folha2->esq) && subarvores_iguais(folha1->dir, folha2->dir)) || (subarvores_iguais(folha1->esq, folha2->dir) && subarvores_iguais(folha1->dir, folha2->esq));
}