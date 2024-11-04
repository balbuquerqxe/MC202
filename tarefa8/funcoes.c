#include "funcoes.h"

/*Organiza a árvore com base nos comandos fornecidos.*/
p_no comandos_arvore(p_no arvore)
{
    char caractere = '\0';
    int continua = 0;
    while (continua == 0) // Enquanto o comando não for de encerramento, continua recebendo comandos.
    {
        scanf(" %c", &caractere); // Comando.
        if (caractere == 'i')
            arvore = insercao(arvore); // Inserção de uma nova cidade.
        else if (caractere == 'b')
        {
            int posicao_x = 0; // Coordenada no eixo X.
            int posicao_y = 0; // Coordenada no eixo Y.
            scanf("%d %d", &posicao_x, &posicao_y);
            busca_ponto(arvore, posicao_x, posicao_y); // Busca cidade pelas suas coordenadas.
        }
        else if (caractere == 'r')
            arvore = remocao(arvore); // Remove cidade pelas suas coordenadas.
        else if (caractere == 'o')
        {
            int raio = 0;     // Valor do raio.
            int centro_x = 0; // Coordenada do centro no eixo X.
            int centro_y = 0; // Coordenada do centro no eixo Y.
            scanf("%d %d %d", &centro_x, &centro_y, &raio);
            printf("Cidades a distancia %d de (%d,%d):", raio, centro_x, centro_y);
            busca_regiao(arvore, raio, centro_x, centro_y); // Busca cidades dentro de uma certa área.
            printf("\n");
        }
        else if (caractere == 's') // Encerra o programa.
            continua = 1;
    }
    return arvore;
}

/* Essa função cria a árvore.*/
p_no cria_arvore(enum tipo_no tipo, int extremo_dir, int extremo_esq, int extremo_baixo, int extremo_cima)
{
    p_no arvore = malloc(sizeof(struct no));
    arvore->extremo_dir = extremo_dir;     // Extremo direito coordenada X.
    arvore->extremo_esq = extremo_esq;     // Extremo esquerdo coordenada X.
    arvore->extremo_baixo = extremo_baixo; // Extremo baixo coordenada Y.
    arvore->extremo_cima = extremo_cima;   // Extremo cima coordenada Y.

    if (tipo == Interno)
    {
        arvore->tipo = Interno;
        arvore->NO = cria_arvore(Vazio, (arvore->extremo_dir + arvore->extremo_esq) / 2, arvore->extremo_esq, (arvore->extremo_cima + arvore->extremo_baixo) / 2, arvore->extremo_cima);  // Região Noroeste.
        arvore->NE = cria_arvore(Vazio, arvore->extremo_dir, (arvore->extremo_dir + arvore->extremo_esq) / 2, (arvore->extremo_cima + arvore->extremo_baixo) / 2, arvore->extremo_cima);  // Região Nordeste.
        arvore->SO = cria_arvore(Vazio, (arvore->extremo_dir + arvore->extremo_esq) / 2, arvore->extremo_esq, arvore->extremo_baixo, (arvore->extremo_cima + arvore->extremo_baixo) / 2); // Região Sudoeste.
        arvore->SE = cria_arvore(Vazio, arvore->extremo_dir, (arvore->extremo_dir + arvore->extremo_esq) / 2, arvore->extremo_baixo, (arvore->extremo_cima + arvore->extremo_baixo) / 2); // Região Sudeste.
        return arvore;
    }
    else if (tipo == Vazio)
    {
        arvore->tipo = Vazio;
        arvore->vazio = 0;
        return arvore;
    }
    else
    {
        arvore->tipo = Ocupado;
        strcpy(arvore->nome, "");
        arvore->posicao_x = 0;
        arvore->posicao_y = 0;
        return arvore;
    }
}

/* Destroi a árvore criada.*/
void destroi_arvore(p_no arvore)
{
    if (arvore == NULL) // Verifica se o nó é NULL antes de tentar acessá-lo.
        return;

    if (arvore->tipo == Interno) // Apenas nós internos possuem filhos que precisam ser destruídos.
    {
        destroi_arvore(arvore->NO); // Destrói sub-região NO
        destroi_arvore(arvore->NE); // Destrói sub-região NE
        destroi_arvore(arvore->SO); // Destrói sub-região SO
        destroi_arvore(arvore->SE); // Destrói sub-região SE
    }

    free(arvore); // Finalmente, libera a memória do nó atual.
}

/* Essa função insere uma nova cidade no mapa.*/
p_no insercao(p_no arvore)
{
    int posicao_x = 0; // Coordenada no eixo X.
    int posicao_y = 0; // Coordenada no eixo Y.
    char nome[MAX];    // Nome da cidade.
    scanf("%d %d %s", &posicao_x, &posicao_y, nome);
    printf("Cidade %s inserida no ponto (%d,%d).\n", nome, posicao_x, posicao_y);
    arvore = recursao_insercao(arvore, posicao_x, posicao_y, nome); // Insere cidade recursivamente.
    return arvore;
}

/* Essa função insere recursivamente uma nova cidade no mapa */
p_no recursao_insercao(p_no arvore, int posicao_x, int posicao_y, char nome[MAX])
{
    if (arvore->tipo == Vazio) // Quando não há cidades na região, posso inseri-la.
    {
        arvore->tipo = Ocupado;        // Modifica o tipo da região.
        arvore->posicao_x = posicao_x; // Registra sua coordenada X.
        arvore->posicao_y = posicao_y; // Registra sua coordenada Y.
        strcpy(arvore->nome, nome);    // Registra o nome da cidade.
        return arvore;
    }

    if (arvore->tipo == Ocupado) // Quando há uma cidade na região, preciso subdividir essa região em 4 menores (SO, NO, SE, NE).
    {
        // Cria uma nova região para, assim, podem inserir a cidade.
        p_no regiao = cria_arvore(Interno, arvore->extremo_dir, arvore->extremo_esq, arvore->extremo_baixo, arvore->extremo_cima);

        // Verifique em qual sub-região a cidade antiga deve ser movida.
        if (arvore->posicao_x <= (arvore->extremo_esq + arvore->extremo_dir) / 2)
        {
            if (arvore->posicao_y <= (arvore->extremo_baixo + arvore->extremo_cima) / 2)
                regiao->SO = recursao_insercao(regiao->SO, arvore->posicao_x, arvore->posicao_y, arvore->nome);
            else
                regiao->NO = recursao_insercao(regiao->NO, arvore->posicao_x, arvore->posicao_y, arvore->nome);
        }
        else
        {
            if (arvore->posicao_y <= (arvore->extremo_baixo + arvore->extremo_cima) / 2)
                regiao->SE = recursao_insercao(regiao->SE, arvore->posicao_x, arvore->posicao_y, arvore->nome);
            else
                regiao->NE = recursao_insercao(regiao->NE, arvore->posicao_x, arvore->posicao_y, arvore->nome);
        }

        // Agora, podemos liberar a árvore original.
        destroi_arvore(arvore);

        arvore = regiao; // A árvore agora passa a ser a sub-região.
    }

    if (arvore->tipo == Interno) // Continua a inserção da nova cidade nas sub-regiões.
    {
        if (posicao_x <= (arvore->extremo_esq + arvore->extremo_dir) / 2)
        {
            if (posicao_y <= (arvore->extremo_baixo + arvore->extremo_cima) / 2)
                arvore->SO = recursao_insercao(arvore->SO, posicao_x, posicao_y, nome); // Insere em SO.
            else
                arvore->NO = recursao_insercao(arvore->NO, posicao_x, posicao_y, nome); // Insere em NO.
        }
        else
        {
            if (posicao_y <= (arvore->extremo_baixo + arvore->extremo_cima) / 2)
                arvore->SE = recursao_insercao(arvore->SE, posicao_x, posicao_y, nome); // Insere em SE.
            else
                arvore->NE = recursao_insercao(arvore->NE, posicao_x, posicao_y, nome); // Insere em NE.
        }
    }

    return arvore; // Retorna a árvore modificada.
}

/* Essa função remove uma nova cidade no mapa.*/
p_no remocao(p_no arvore)
{
    int posicao_x = 0; // Coordenada no eixo X.
    int posicao_y = 0; // Coordenada no eixo Y.
    scanf("%d %d", &posicao_x, &posicao_y);
    arvore = recursao_remocao(arvore, posicao_x, posicao_y);
    return arvore;
}

p_no recursao_remocao(p_no arvore, int posicao_x, int posicao_y)
{
    if (arvore->tipo == Vazio) // Verifica se a árvore é nula antes de acessar.
        return arvore;

    if ((arvore->tipo == Ocupado) && (arvore->posicao_x == posicao_x) && (arvore->posicao_y == posicao_y)) // Quando há apenas uma cidade na região filtrada, ela será a removida.
    {
        printf("Cidade %s removida do ponto (%d,%d).\n", arvore->nome, arvore->posicao_x, arvore->posicao_y);
        arvore->tipo = Vazio;
        return arvore;
    }

    if (arvore->tipo == Interno) // Continua a remoção da cidade nas sub-regiões.
    {
        if (posicao_x <= (arvore->extremo_esq + arvore->extremo_dir) / 2)
        {
            if (posicao_y <= (arvore->extremo_baixo + arvore->extremo_cima) / 2)
                arvore->SO = recursao_remocao(arvore->SO, posicao_x, posicao_y); // Remoção em SO.
            else
                arvore->NO = recursao_remocao(arvore->NO, posicao_x, posicao_y); // Remoção em NO.
        }
        else
        {
            if (posicao_y <= (arvore->extremo_baixo + arvore->extremo_cima) / 2)
                arvore->SE = recursao_remocao(arvore->SE, posicao_x, posicao_y); // Remoção em SE.
            else
                arvore->NE = recursao_remocao(arvore->NE, posicao_x, posicao_y); // Remoção em NE.
        }

        // Após a remoção, verifica se todas as sub-regiões estão vazias e atualiza a árvore.
        arvore = regiao_vazia(arvore);
    }
    return arvore; // Retorna a árvore atualizada.
}

/* Esa função ransforma um nó interno em vazio ou ocupado.*/
p_no regiao_vazia(p_no arvore)
{
    if (arvore == NULL || arvore->tipo != Interno)
        return arvore;

    // Verifica se todas as sub-regiões são vazias.
    if (arvore->SO->tipo == Vazio && arvore->SE->tipo == Vazio && arvore->NO->tipo == Vazio && arvore->NE->tipo == Vazio)
    {
        destroi_arvore(arvore->SO);
        destroi_arvore(arvore->SE);
        destroi_arvore(arvore->NO);
        destroi_arvore(arvore->NE);

        p_no cidade_removida = cria_arvore(Vazio, arvore->extremo_dir, arvore->extremo_esq, arvore->extremo_baixo, arvore->extremo_cima);
        free(arvore);
        return cidade_removida;
    }

    int ocupadas = 0; // Contador para verificar quantas sub-regiões estão ocupadas.
    int vazio = 0;
    p_no auxiliar = NULL; // Armazena as informações da região não vazia.

    // Verificação para cada sub-região.
    if (arvore->SE->tipo == Ocupado)
    {
        ocupadas++;
        auxiliar = arvore->SE;
    }
    else if (arvore->SO->tipo == Ocupado)
    {
        ocupadas++;
        auxiliar = arvore->SO;
    }
    else if (arvore->NE->tipo == Ocupado)
    {
        ocupadas++;
        auxiliar = arvore->NE;
    }
    else if (arvore->NO->tipo == Ocupado)
    {
        ocupadas++;
        auxiliar = arvore->NO;
    }

    if (arvore->SE->tipo == Vazio)
    {
        vazio++;
    }
    else if (arvore->SO->tipo == Vazio)
    {
        vazio++;
    }
    else if (arvore->NE->tipo == Vazio)
    {
        vazio++;
    }
    else if (arvore->NO->tipo == Vazio)
    {
        vazio++;
    }

    // Se apenas uma sub-região está ocupada, substitui a árvore por ela (muda o nó para "Ocupado").
    if (ocupadas == 1 && vazio == 3)
    {
        p_no novo_no = cria_arvore(Ocupado, arvore->extremo_dir, arvore->extremo_esq, arvore->extremo_baixo, arvore->extremo_cima);

        // Copia os dados do nó auxiliar.
        novo_no->posicao_x = auxiliar->posicao_x;
        novo_no->posicao_y = auxiliar->posicao_y;
        strcpy(novo_no->nome, auxiliar->nome);

        destroi_arvore(arvore); // Libera a árvore antiga e retornar o novo nó.
        return novo_no;
    }
    return arvore; // Retorna a árvore original se houver mais de uma região ocupada.
}

/* Essa função busca uma cidade pelas suas coordenadas.*/
void busca_ponto(p_no arvore, int posicao_x, int posicao_y)
{
    if (arvore == NULL)
    {
        printf("Nenhuma cidade encontrada no ponto (%d,%d).\n", posicao_x, posicao_y);
        return;
    }

    if (arvore->tipo == Ocupado && posicao_x == arvore->posicao_x && posicao_y == arvore->posicao_y) // Se as coordenadas coincidirem.
    {
        printf("Cidade %s encontrada no ponto (%d,%d).\n", arvore->nome, posicao_x, posicao_y);
        return;
    }

    if (arvore->tipo == Interno) // Continua a busca nas sub-regiões.
    {
        if (posicao_x <= (arvore->extremo_esq + arvore->extremo_dir) / 2)
        {
            if (posicao_y <= (arvore->extremo_baixo + arvore->extremo_cima) / 2)
                busca_ponto(arvore->SO, posicao_x, posicao_y); // Busca em SO.
            else
                busca_ponto(arvore->NO, posicao_x, posicao_y); // Busca em NO.
        }
        else
        {
            if (posicao_y <= (arvore->extremo_baixo + arvore->extremo_cima) / 2)
                busca_ponto(arvore->SE, posicao_x, posicao_y); // Busca em SE.
            else
                busca_ponto(arvore->NE, posicao_x, posicao_y); // Busca em NE.
        }
    }
    else
    {
        printf("Nenhuma cidade encontrada no ponto (%d,%d).\n", posicao_x, posicao_y); // Se nçao encontrar em nenhuma sub-região, a cidade não existe.
    }
}

/* Essa função busca as cidades dentro de um disco.*/
void busca_regiao(p_no arvore, int raio, int centro_x, int centro_y)
{
    /* Aqui, a primeira coisa que precisamos pensar é na maior coordenada possível
    para um ponto estar nesse raio. Assim, temos que posicao_y <= centro_y + raio
    e posicao_x <= centro_x + raio. */

    if (arvore->tipo == Ocupado)
    {
        if (distancia(arvore, centro_x, centro_y) <= raio)
        {
            printf(" %s", arvore->nome);
            return;
        }
    }

    if (arvore->tipo == Interno) // Continua a remoção da cidade nas sub-regiões (precisa "entrar" nessa região e encontrar a cidade).
    {
        if (verificar_regiao(arvore->SO, raio, centro_x, centro_y) == 1)
            busca_regiao(arvore->SO, raio, centro_x, centro_y);
        if (verificar_regiao(arvore->SE, raio, centro_x, centro_y) == 1)
            busca_regiao(arvore->SE, raio, centro_x, centro_y);
        if (verificar_regiao(arvore->NO, raio, centro_x, centro_y) == 1)
            busca_regiao(arvore->NO, raio, centro_x, centro_y);
        if (verificar_regiao(arvore->NE, raio, centro_x, centro_y) == 1)
            busca_regiao(arvore->NE, raio, centro_x, centro_y);
    }
}

/* Essa função calcula a distância da cidade ao centro do disco.*/
double distancia(p_no arvore, int centro_x, int centro_y)
{
    return sqrt((arvore->posicao_x - centro_x) * (arvore->posicao_x - centro_x) + (arvore->posicao_y - centro_y) * (arvore->posicao_y - centro_y));
}

/* Essa função verifica quais regiões vale a pena checar (tem chances de haver uma cidade).*/
int verificar_regiao(p_no arvore, int raio, int centro_x, int centro_y)
{
    if ((arvore->extremo_esq <= (centro_x + raio)))
        return 1;
    if ((arvore->extremo_esq <= (centro_x - raio)) && ((centro_x - raio) <= arvore->extremo_dir))
        return 1;
    if ((arvore->extremo_baixo <= (centro_y + raio)) && ((centro_y + raio) <= arvore->extremo_cima))
        return 1;
    if ((arvore->extremo_baixo <= (centro_y - raio)) && ((centro_y - raio) <= arvore->extremo_cima))
        return 1;
    return 0;
}