#include <stdio.h>
#include <string.h>

#define max_doencas 150
#define max_medicos 50
#define max_pacientes 100   /* Máximo de pacientes. */
#define max 300   /* Máximo de comandos*/
#define max_nome 31   /* Tamanho máximo de caracteres.*/
#define max_cid 7   /* Tamanho máximo do cid. */
#define max_crm 7   /* Tamanho máximo do crm. */

void diferenciando_comandos (int i, char lista_pessoas[max][max_nome], char lista_cid [max][max_cid], char lista_crm[max][max_crm], int lista_posicao[max], int posicao);

void excluindo_pacientes (char lista_todos_pacientes[max][max_nome], char lista_cid_corrigida [max][max_cid], char lista_crm[max][max_crm], char lista_pacientes_excluidos[max][max_nome], char lista_final_pacientes[max][max_nome], char lista_final_cid [max][max_cid], char lista_final_crm[max][max_crm]);

void corrigindo_informacoes (char lista_todos_pacientes[max][max_nome], char lista_todos_cid [max][max_cid], char lista_pacientes_alterados [max][max_nome], char lista_cid_alterados [max][max_cid], char lista_cid_corrigida [max][max_cid], int lista_posicao_registrados[max], int lista_posicao_alterados[max]);

void carregar_doencas(int *quantia_doencas, char nome_doenca[max_doencas][max_doencas], char codigo_doenca[max_doencas][max_doencas]);

void carregar_medicos(int *quantia_medicos, char nome_medico[max_medicos][max_doencas], char codigo_medico[max_medicos][max_doencas]);

void encontrar_doenca(int quantia_doencas, char nome_doenca[max_doencas][max_doencas], char codigo_doenca[max_doencas][max_doencas], char lista_final_cid[max][max_cid], int i, char doenca[max_doencas]);

void encontrar_medico(int quantia_medicos, char nome_medico[max_medicos][max_doencas], char codigo_medico[max_medicos][max_doencas], char lista_final_crm[max][max_cid], int i, char medico[max_doencas]);

int main ( ) {

int quantia_doencas = 0, quantia_medicos = 0;
    char doenca[max_doencas] = {0};
    char medico[max_doencas] = {0};
    int quantidade_pacientes = 0;   /* Quantos pacientes poderão ser atendidos no dia */
    int i = 0, j = 0, k = 0, l = 0;
    char abrir[max_nome] = {0};
    char nome_doenca[max_doencas][max_doencas] = {0};
    char codigo_doenca[max_doencas][max_doencas] = {0};
    char nome_medico[max_medicos][max_doencas] = {0};
    char codigo_medico[max_medicos][max_doencas] = {0};
    char comando[max_nome] = {0};
    char lista_todos_pacientes[max][max_nome] = {0};
    char lista_todos_cid[max][max_cid] = {0};
    char lista_todos_crm[max][max_crm] = {0};
    int lista_posicao_registrados[max] = {0};
    int lista_posicao_alterados[max] = {0};
    char lista_pacientes_alterados[max][max_nome] = {0};
    char lista_cid_alterados[max][max_cid] = {0};
    char lista_cid_corrigida[max][max_cid] = {0};
    char lista_pacientes_excluidos[max][max_nome] = {0};
    char lista_final_pacientes[max][max_nome] = {0};
    char lista_final_cid[max][max_cid] = {0};
    char lista_final_crm[max][max_crm] = {0};

    carregar_doencas(&quantia_doencas, nome_doenca, codigo_doenca);
    carregar_medicos(&quantia_medicos, nome_medico, codigo_medico);

    scanf ("%s %d", abrir, &quantidade_pacientes);   // Registra a quantidade de pacientes que poderão ser atendidos no dia.

    while (1) {   // Ou seja, enquanto for verdadeiro, o código deve continuar sendo lido.

        scanf("%s", comando);   // Leitura do comando.

        if (strcmp(comando, "fechar") == 0) break;   // Se o comando for "fechar", o código não deve continuar sendo lido.

        else if (strcmp(comando, "registrar") == 0) {   // Quando o comando for "registrar"
            diferenciando_comandos(i, lista_todos_pacientes, lista_todos_cid, lista_todos_crm, lista_posicao_registrados, l);
            i++;
        }
        else if (strcmp(comando, "alterar") == 0){   // Quando o comando for "alterar".
            diferenciando_comandos(j, lista_pacientes_alterados, lista_cid_alterados, NULL, lista_posicao_alterados, l);
            j++;
        }
        else {   // Quando o comando for "retirar".
            diferenciando_comandos(k, lista_pacientes_excluidos, NULL, NULL, NULL, l);
            k++;
        }
        l++;

    }
    
    corrigindo_informacoes (lista_todos_pacientes, lista_todos_cid, lista_pacientes_alterados, lista_cid_alterados, lista_cid_corrigida, lista_posicao_registrados, lista_posicao_alterados);
    excluindo_pacientes (lista_todos_pacientes, lista_cid_corrigida, lista_todos_crm, lista_pacientes_excluidos, lista_final_pacientes, lista_final_cid, lista_final_crm);

    for (i = 0; i < quantidade_pacientes && i < max_pacientes; i++){
        if (strcmp(lista_final_pacientes[i], "") == 0)
            break;
        encontrar_doenca (quantia_doencas, nome_doenca, codigo_doenca, lista_final_cid, i, doenca);
        encontrar_medico (quantia_medicos, nome_medico, codigo_medico, lista_final_crm, i, medico);
        printf("%s atendido por %s: %s\n", lista_final_pacientes[i], medico, doenca);
    }
    return 0;
}

void encontrar_doenca(int quantia_doencas, char nome_doenca[max_doencas][max_doencas], char codigo_doenca[max_doencas][max_doencas], char lista_final_cid[max][max_cid], int i, char doenca[max_doencas]) {
    int k;
    for (k = 0; k < quantia_doencas; k++)
        if (strcmp(codigo_doenca[k], lista_final_cid[i]) == 0)
            strcpy(doenca, nome_doenca[k]);
        
}

void encontrar_medico(int quantia_medicos, char nome_medico[max_medicos][max_doencas], char codigo_medico[max_medicos][max_doencas], char lista_final_crm[max][max_cid], int i, char medico[max_doencas]) {
    int k;
    for (k = 0; k < quantia_medicos; k++)
        if (strcmp(codigo_medico[k], lista_final_crm[i]) == 0)
            strcpy(medico, nome_medico[k]);
}

void carregar_doencas(int *quantia_doencas, char nome_doenca[max_doencas][max_doencas], char codigo_doenca[max_doencas][max_doencas]) {
    int i;
    FILE *pdoenca = fopen("dados/doencas.txt", "r");
    if (pdoenca == NULL) {
        perror("Erro ao abrir o arquivo de doenças");
        return;
    }
    fscanf(pdoenca, "%d", quantia_doencas);
    for (i = 0; i < *quantia_doencas; i++) {
        fscanf(pdoenca, " %s %[^\n]", codigo_doenca[i], nome_doenca[i]);
    }
    fclose(pdoenca);
}

void carregar_medicos(int *quantia_medicos, char nome_medico[max_medicos][max_doencas], char codigo_medico[max_medicos][max_doencas]) {
    int i;
    FILE *pmedico = fopen("dados/medicos.txt", "r");
    if (pmedico == NULL) {
        perror("Erro ao abrir o arquivo de médicos");
        return;
    }
    fscanf(pmedico, "%d", quantia_medicos);
    for (i = 0; i < *quantia_medicos; i++) {
        fscanf(pmedico, " %s %s", codigo_medico[i], nome_medico[i]);
    }
    fclose(pmedico);
}

void diferenciando_comandos (int i, char lista_pessoas[max][max_nome], char lista_cid [max][max_cid], char lista_crm[max][max_crm], int lista_posicao[max], int posicao){
    scanf(" %s", lista_pessoas[i]);
    if (lista_cid != NULL)
        scanf(" %s", lista_cid[i]);
    if (lista_crm != NULL)
        scanf(" %s", lista_crm[i]);
    if (lista_posicao != NULL)
        lista_posicao[i] = posicao;
}

void corrigindo_informacoes (char lista_todos_pacientes[max][max_nome], char lista_todos_cid [max][max_cid], char lista_pacientes_alterados [max][max_nome], char lista_cid_alterados [max][max_cid], char lista_cid_corrigida [max][max_cid], int lista_posicao_registrados[max], int lista_posicao_alterados[max]){
    int i, j;

    for (i = 0; i < max && strcmp(lista_todos_pacientes[i], "") != 0; i++)   // Enquanto a lista de todos os pacientes não for vazia.
        for (j = 0; j < max && (strcmp(lista_pacientes_alterados[j], "") != 0); j++)   // Enquanto a lista dos pacientes com dados alterados não for vazia.
                    if (strcmp(lista_todos_pacientes[i], lista_pacientes_alterados[j]) == 0) {   // Se os nomes forem os mesmos, isso significa que temos que alterar uma das informações do paciente.
                        if (lista_posicao_registrados[i] < lista_posicao_alterados[j])   // Ou seja, apenas se foi pedido para alterar uma informação fornecida anteriormente (não muda o que foi registrado depois de pedir alteração).
                            strcpy(lista_cid_corrigida[i], lista_cid_alterados[j]);   // Alterando o cid do paciente.
                    }
                
    for (i = 0; i < max && strcmp(lista_todos_pacientes[i], "") != 0; i++)
        if (strcmp(lista_cid_corrigida[i], "") == 0)   // Se a lista corrigida estiver com dados vazios, iso significa que não haviam alterações a serem feitas em alguns casos.
            strcpy(lista_cid_corrigida[i], lista_todos_cid[i]);
}

void excluindo_pacientes (char lista_todos_pacientes[max][max_nome], char lista_cid_corrigida [max][max_cid], char lista_todos_crm[max][max_crm], char lista_pacientes_excluidos[max][max_nome], char lista_final_pacientes[max][max_nome], char lista_final_cid [max][max_cid], char lista_final_crm[max][max_crm]){
    int i, j;
    int k = 0;
    int excluido_usado[max] = {0};   // Indicará se já foi usado para retirar alguém.

    for (i = 0; (i < max && strcmp(lista_todos_pacientes[i], "") != 0); i++){   // Enquanto a lista de todos os pacientes não for vazia.
        int flag = 0;   // Irá registrar se o nome foi retirado em algum momento.
        for (j = 0; j < max && strcmp(lista_pacientes_excluidos[j], "") != 0; j++)   // Enquanto a lista dos pacientes excluídos não for vazia.
            if ((strcmp(lista_todos_pacientes[i], lista_pacientes_excluidos[j]) == 0) && excluido_usado[j] != 1){   // Se os nomes forem os mesmos, isso significa que temos que excluir o paciente.
                flag = 1;
                excluido_usado[j] = 1;
                break;
            }
        if (flag == 0){
            strcpy(lista_final_pacientes[k], lista_todos_pacientes[i]);   // Registrando os nomes dos pacientes que restaram.
            strcpy(lista_final_cid[k], lista_cid_corrigida[i]);   // Registrando o cid dos pacientes que restaram.
            strcpy(lista_final_crm[k], lista_todos_crm[i]);   // Registrando o crm dos pacientes que restaram.
            k++;
        }
    }
}