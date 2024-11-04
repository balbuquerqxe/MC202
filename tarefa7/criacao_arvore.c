#include "declaracoes_otimizar.h"

p_no cria_no(char caractere, p_no esq, p_no dir, p_no pai) /* Cria um nó da árvore.*/
{
	/* Quando não sabemos qual é o operador ou expressão da árvore/ sub-árvore
	(já que lemos da esquerda para direita), optei por preencher o nó com um "?",
	indicando que um futuro dado desconhecido ocupará aquele lugar (fica mais
	fácil de acessá-lo corretamente).*/

	p_no r = malloc(sizeof(struct no)); // Aloca na memória.
	r->dado = caractere;				// Informação contida na folha.
	r->esq = esq;						// Dado esquerdo.
	r->dir = dir;						// Dado direito.
	r->pai = pai;
	return r;
}

p_no distribuicao_arvore(p_no raiz) /* Organiza os caracteres pela árvore.*/
{
	char caractere = '\0';
	int codigo = 0;
	codigo = scanf("%c", &caractere); // Escaneia cada caractere da fórmula inserida.

	if (caractere == '\n' || caractere == '\0' || codigo == EOF) // Indica que a fórmula chegou ao seu fim, terminando a construção da árvore.
		return raiz;											 // Retorna a raiz da árvore e para de executar a função.

	if (raiz == NULL) // Se a raiz for NULL, chegamos na última folha da árvore, precisando "voltar" ao pai.
		return NULL;  // Retorna NULL se a raiz for vazia.

	if (caractere == '(') // "(" possui a função de criar um nó que depois terá seu dado preenchido.
	{
		p_no folha = cria_no('?', NULL, NULL, raiz); // ERRO // Cria um nó que possui informação desconhecida, a qual será completada depois.

		/* Optei por utilizar o caractere "?" para demarcar os nós que ainda esperam receber uma
		informação,como um operador ou expressão, facilitando a sua busca nas horas necessárias.
		Ou seja, "?" indica que ainda falta preencher aquele nó com algo, o que ocorrerá depois.*/

		if (folha == NULL)
			return NULL; // Verifica se a alocação foi bem-sucedida.

		destroi_arvore(raiz->esq);
		raiz->esq = folha;				// Define que o próximo caractere será o filho esquerdo.
		distribuicao_arvore(raiz->esq); // ERRO // Continua a construção da árvore a partir da folha.
		return raiz;					// Retorna raiz.
	}
	if (caractere == ')') // ")" Possui a função de voltar ao pai, já que aquela ramificação não terá mais nenhum dado adicionado.
	{
		if (raiz->pai != NULL)				// Volta ao pai para continuar a estruturar o resto da fórmula na árvore.
			distribuicao_arvore(raiz->pai); // ERRO
		return raiz;
	}
	if (caractere == '&' || caractere == '|') // Quando forem operadores, eles serão inseridos como dados no nó indicado na árvore.
	{
		raiz = folha_desocupada(raiz); // Encontra o nó desocupado mais próximo para colocar o operador.
		if (raiz == NULL)
			return NULL; // Verifica se folha_desocupada retornou NULL, ou seja, deu algo errado e não tem onde adicioná-lo.

		raiz->dado = caractere;						 // Define o operador no nó.
		p_no folha = cria_no('?', NULL, NULL, raiz); // ERRO // Cria um novo nó para o filho direito (já que eu escaneio a fórmula da esquerda para direita).

		if (folha == NULL)
			return NULL; // Verifica se a alocação foi bem-sucedida.

		destroi_arvore(raiz->dir);
		raiz->dir = folha; // Indica que o próximo nó será o filho direito da raiz que contém o operador.

		distribuicao_arvore(folha); // ERRO // Continua a construção da árvore a partir da folha.

		return raiz; // Retorna raiz.
	}
	if (caractere == '!') // Quando for uma negação, "!" será inserido no nó e possuirá um único filho (escolhi ser sempre o filho esquerdo).
	{
		raiz = folha_desocupada(raiz); // Garante que será o próximo nó desocupado.

		if (raiz == NULL)
			return NULL; // Verifica se folha_desocupada retornou NULL.

		raiz->dado = caractere; // Define o operador "!" no nó.

		p_no folha = cria_no('?', NULL, NULL, raiz); // Cria um nó filho esquerdo para o "!" (nesse caso, possuirá apenas o filho esquerdo).

		if (folha == NULL)
			return NULL; // Verifica se a alocação foi bem-sucedida.

		destroi_arvore(raiz->esq);
		raiz->esq = folha; // Indica que o nó criado é o filho esquero da raiz.

		distribuicao_arvore(folha); // ERRO // Continua a construção da árvore a partir da folha.
		return raiz;				// Retorna raiz.
	}
	else // Ocorrerá quando o caractere inserido for uma letra minúscula.
	{
		raiz = folha_desocupada(raiz); // Encontra o nó para colocar a letra minúscula (operado).
		if (raiz == NULL)
			return NULL; // Verifica se folha_desocupada retornou NULL.

		raiz->dado = caractere;				// Coloca a letra no nó.
		if (raiz->pai != NULL)				// Verifica se a raiz possui um pai.
			distribuicao_arvore(raiz->pai); // ERRO // Volta ao pai após inserir o operando (essa ramificação da árvore chegou ao fim)
		return raiz;						// Retorna raiz.
	}

	return raiz; // Retorna raiz.
}

p_no folha_desocupada(p_no raiz) /* Verifica se um nó da árvore está desocupado (ou seja, com "?", esperando um dado).*/
{
	if (raiz == NULL) // Se a raiz for NULL, não há como subir na árvore (já chegou na raiz principal).
		return NULL;  // Retorna NULL.

	if (raiz->dado != '?')					// Se o nó já estiver ocupado, sobe para o pai.
		return folha_desocupada(raiz->pai); // Subo para o pai.
	return raiz;							// Caso o nó esteja desocupado, retornamos esse nó;
}

p_no encontra_raiz(p_no raiz) /* Encontra a raiz principal da árvore, a qual não possui pai.*/
{
	if (raiz->pai != NULL) // Se possuir pai, não é a raiz principal ainda.
		encontra_raiz(raiz->pai);
	return raiz; // Indica ter encontrado a raiz e deve retorná-la.
}

void imprime_arvore(p_no raiz) /* Imprime a árvore e os parênteses necessários na ordem correta.*/
{
	if (raiz != NULL)
	{
		if (raiz->dado == '&' || raiz->dado == '|')
		{
			printf("(");			   // Abre parênteses.
			imprime_arvore(raiz->esq); // Visita o filho esquerdo.
			printf("%c", raiz->dado);  // Imprime o operador.
			imprime_arvore(raiz->dir); // Visita o filho direito.
			printf(")");			   // Fecha parênteses.
		}
		else if (raiz->dado == '!')
		{
			printf("%c", raiz->dado);  // Imprime o "!" antes do filho, algo importante, já que com operadores é ao contrário.
			imprime_arvore(raiz->esq); // Visita o filho esquerdo (já que o direito será NULL).
		}
		else if (raiz->dado == '?') // O "?" não deve ser impresso.
		{
			imprime_arvore(raiz->esq); // Passo a verificar se a raiz esquerda possui dados.
			imprime_arvore(raiz->dir); // Passo a verificar se a raiz direita possui dados.
		}
		else
			printf("%c", raiz->dado); // Imprime o caractere.
	}
}

void destroi_arvore(p_no raiz)
{
	if (raiz == NULL) // Fim.
		return;		  // Atua como se fosse um breakpoint".

	// Destrói as subárvores esquerda e direita.
	destroi_arvore(raiz->esq);
	destroi_arvore(raiz->dir);

	free(raiz); // Libera o nó atual (após destruir suas subárvores).
}
