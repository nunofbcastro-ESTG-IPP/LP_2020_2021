#include <stdio.h>
#include <stdlib.h>
#include "irs.h"
#include "funcoes.h"
#include "input.h"
#include "funcionario.h"
#include <limits.h>

/**
 * Função utilizada para atualizar um determinado ficheiro de IRS.
 * @param irs - apontador onde se encontram guardados os dados relativos à tabela de IRS.
 * @param contador - valor correspondente ao número de linhas com dados do IRS que irão ser guardados no ficheiro IRS.
 * @param nomeFicheiro - valor correspondente ao nome do ficheiro onde será guardada a informação do IRS.
 */
void atualizarFicheiroIRS(IRS *irs, int contador, char *nomeFicheiro) {
    FILE *fp;
    fp = fopen(nomeFicheiro, "w");
    if (fp == NULL) {
        puts("Erro ao criar/alterar ficheiro.\n");
    }else{
        fprintf(fp, "%d\n", contador);
        for (int i = 0; i < contador; i++) {
            fprintf(fp, "%f %f %f %f %f %f %f\n", irs[i].salario, irs[i].percentagem[0], irs[i].percentagem[1], irs[i].percentagem[2], irs[i].percentagem[3], irs[i].percentagem[4], irs[i].percentagem[5]);
        }
    }
    fclose(fp);
}

/**
 * Função utilizada para importar os dados de um determinado ficheiro de IRS.
 * @param irs - apontador onde serão guardados os dados relativos à tabela de IRS.
 * @param contador - valor correspondente ao número de linhas com dados do IRS que irão ser importadas no ficheiro IRS.
 * @param tam - valor correspondente ao limite máximo de dados de IRS.
 * @param nomeFicheiro - valor correspondente ao nome do ficheiro onde será guardada a informação do IRS.
 */
void carregarDadosFicheiroIRS(IRS **irs, int *contador, int *tam, char *nomeFicheiro) {
    FILE *fp;
    fp = fopen(nomeFicheiro, "r");
    if (fp == NULL) {
        puts("Erro ao abrir ficheiro do IRS");
    }
    fscanf(fp, "%d", contador);
    if (contador > 0) {
        *irs = (IRS*) calloc(*contador + 5, sizeof (IRS));
        if (irs != NULL) {
            *tam = *contador + 5;
            for (int i = 0; i < *contador; i++) {
                fscanf(fp, "%f %f %f %f %f %f %f\n", &(*irs)[i].salario, &(*irs)[i].percentagem[0], &(*irs)[i].percentagem[1]
                        , &(*irs)[i].percentagem[2], &(*irs)[i].percentagem[3], &(*irs)[i].percentagem[4], &(*irs)[i].percentagem[5]);
            }
        } else {
            *contador = 0;
        }
    }
    fclose(fp);
}

/**
 * Função utilizada listar todos os dados do IRS (utilizada para testes).
 * @param irs - apontador onde se encontram guardados os dados relativos à tabela de IRS.
 * @param contador - valor correspondente ao número de linhas com dados do IRS.
 * @param mensagem - valor correspondente à mensagem a ser mostrada antes da listagem dos dados do IRS.
 */
void listarIRS(IRS *irs, int contador, char* mensagem) {
    printf("%s\n", mensagem);
    printf("---------------------------------------------------------------------------------------\n");
    printf("|  Remuneração  | 0 Filhos | 1 Filho | 2 Filhos | 3 Filhos | 4 Filhos | 5 ou + Filhos |\n");
    printf("---------------------------------------------------------------------------------------\n");
    for (int i = 0; i < contador; i++) {
        printf("| %12.2f€ | %7.2f%% | %6.2f%% | %7.2f%% | %7.2f%% | %7.2f%% | %12.2f%% |\n", irs[i].salario, irs[i].percentagem[0]*100, irs[i].percentagem[1]*100, irs[i].percentagem[2]*100, irs[i].percentagem[3]*100, irs[i].percentagem[4]*100, irs[i].percentagem[5]*100);
        printf("---------------------------------------------------------------------------------------\n");
    }
}

/**
 * Função utilizada para pesquisar uma remuneração mensal da tabela de IRS.
 * @param irs - apontador onde estão armazenados os salários da tabela de IRS.
 * @param contador - valor correspondente ao número de linhas existentes na tabela de IRS.
 * @param remuneracao - valor correspondente ao salário a ser procurado na tabela de IRS.
 * @param inicio - valor correspondente à primeira posição do apontador.
 * @param fim - valor correspondente à última posição do apontador.
 * @return indice do salário (caso seja encontrado) ou -1 (caso não seja encontrado).
 */
int pesquisarSalarioAlterar(IRS *irs, int contador, float remuneracao, int inicio, int fim) {
    if (fim >= inicio) {
        int meio = inicio + ((fim - inicio) / 2);

        if (irs[meio].salario == remuneracao) {
            return meio;
        }else if(meio == (contador - 1) && irs[meio].salario < remuneracao){
            return meio;
        }

        return (irs[meio].salario > remuneracao ) ?
                pesquisarSalarioAlterar(irs, contador, remuneracao, inicio, meio - 1) :
                pesquisarSalarioAlterar(irs, contador, remuneracao, meio + 1, fim);
    }

    return -1;
}

/**
 * Função utilizada para pesquisar uma remuneração mensal da tabela de IRS.
 * @param irs - apontador onde estão armazenados os salários da tabela de IRS.
 * @param remuneracao - valor correspondente ao salário a ser procurado na tabela de IRS.
 * @param inicio - valor correspondente à primeira posição do apontador.
 * @param fim - valor correspondente à última posição do apontador.
 * @return indice do salário (caso seja encontrado) ou -1 (caso não seja encontrado).
 */
int pesquisarSalario(IRS *irs, float remuneracao, int inicio, int fim) {            
    if (fim >= inicio) {
        int meio = inicio + ((fim - inicio) / 2);

        if (irs[meio].salario == remuneracao) {
            return meio;
        }

        return (irs[meio].salario > remuneracao) ?
                pesquisarSalario(irs, remuneracao, inicio, meio - 1) :
                pesquisarSalario(irs, remuneracao, meio + 1, fim);
    }

    return -1;
}

/**
 * Função utilizada para ordenar a tabela de IRS pela remuneração mensal.
 * @param irs - apontador onde estão armazenados os salários da tabela de IRS.
 * @param inicio - valor correspondente à primeira posição do apontador.
 * @param fim - valor correspondente à última posição do apontador.
 */
void ordenarSalarios(IRS *irs, int inicio, int fim) {
    int i, j, pivot;
    IRS temp;

    if (inicio < fim) {
        pivot = inicio;
        i = inicio;
        j = fim;

        while (i < j) {
            while (irs[i].salario <= irs[pivot].salario && i < fim)
                i++;
            while (irs[j].salario > irs[pivot].salario)
                j--;
            if (i < j) {
                temp = irs[i];
                irs[i] = irs[j];
                irs[j] = temp;
            }
        }

        temp = irs[pivot];
        irs[pivot] = irs[j];
        irs[j] = temp;
        ordenarSalarios(irs, inicio, j - 1);
        ordenarSalarios(irs, j + 1, fim);

    }
}

/**
 * Função utilizada para adicionar uma linha de dados da tabela de IRS.
 * @param irs - apontador onde serão guardados os dados relativos à tabela de IRS.
 * @param contador - valor correspondente ao número de linhas com dados do IRS.
 * @param tam - valor correspondente ao limite máximo de dados de IRS.
 */
void adicionarTabelaIRS(IRS **irs, int *contador, int *tam) {
    int remuneracao, x;
    IRS *novo;
    if (*contador == *tam) {
        novo = (IRS*) realloc(*irs, sizeof (IRS) * (*tam + INC));
        if (novo == NULL) {
            puts("Erro ao alocar memória no IRS");
        } else {
            tam += INC;
            *irs = novo;
        }
    }
    obterSalario(*irs, *contador, MSG_OBTER_REMUNERACAO);
    remuneracao = (*irs)[*contador].salario;
    (*contador)++;
    ordenarSalarios(*irs, 0, (*contador)-1);
    x = pesquisarSalario(*irs, remuneracao, 0, (*contador)-1);

    if (x == -1) {
        puts(ERRO_PESQUISA_SALARIO);
    } else {
        for (int i = 0; i < 6; i++) {
            if (i == 5) {
                printf("\nNúmero de filhos 5 ou mais\n");
            } else {
                printf("\nNúmero de filhos %d\n", i);
            }
            if (x == 0) {
                (*irs)[x].percentagem[i] = (obterIRS_Percentagem(0, ((*irs)[x + 1].percentagem[i] * 100), MSG_OBTER_PERCENTAGEM) / 100);
            } else if (x == (*contador)-1) {
                (*irs)[x].percentagem[i] = (obterIRS_Percentagem(((*irs)[x - 1].percentagem[i] * 100), 100, MSG_OBTER_PERCENTAGEM) / 100);
            } else {
                (*irs)[x].percentagem[i] = (obterIRS_Percentagem(((*irs)[x - 1].percentagem[i] * 100), ((*irs)[x + 1].percentagem[i] * 100), MSG_OBTER_PERCENTAGEM) / 100);
            }
        }
    }
}

/**
 * Função utilizada para alterar o valor da remuneração mensal.
 * @param irs - apontador onde serão guardados os dados relativos à tabela de IRS.
 * @param index - valor correspondente ao índice da linha de IRS a ser alterada.
 * @param contador - valor correspondente ao número de linhas do ficheiro do IRS.
 */
void alterarIRSSalario(IRS *irs, int index, int contador){
    if (index == 0) {
        irs[index].salario = (obterFloat(0, irs[index+1].salario - 1, MSG_OBTER_REMUNERACAO));
    } else if (index == contador) {
        irs[index].salario = (obterFloat(irs[index-1].salario, INT_MAX, MSG_OBTER_REMUNERACAO));
    } else {
        irs[index].salario = (obterFloat(irs[index-1].salario, irs[index+1].salario -1, MSG_OBTER_REMUNERACAO));
    }
}

/**
 * Função utilizada para alterar o valor decimal correspondente às percentagens do IRS.
 * @param irs - apontador onde serão guardados os dados relativos à tabela de IRS.
 * @param index - valor correspondente ao índice da linha de IRS a ser alterada.
 * @param contador - valor correspondente ao número de linhas do ficheiro do IRS.
 */
void alterarIRSPercentagens(IRS *irs, int index, int contador){
    for (int i = 0; i < 6; i++) {
        if (i == 5) {
            printf("\nNúmero de filhos 5 ou mais\n");
        } else {
            printf("\nNúmero de filhos %d\n", i);
        }
        if (index == 0) {
            irs[index].percentagem[i] = (obterIRS_Percentagem(0, (irs[index+1].percentagem[i] * 100), MSG_OBTER_PERCENTAGEM) / 100);
        } else if (index == contador - 1) {
            irs[index].percentagem[i] = (obterIRS_Percentagem((irs[index-1].percentagem[i] * 100), 100, MSG_OBTER_PERCENTAGEM) / 100);
        } else {
            irs[index].percentagem[i] = (obterIRS_Percentagem((irs[index-1].percentagem[i] * 100), (irs[index+1].percentagem[i] * 100), MSG_OBTER_PERCENTAGEM) / 100);
        }
    }
}

/**
 * Função utilizada para alterar uma linha de dados da tabela de IRS.
 * @param irs - apontador onde se encontram guardados os dados relativos à tabela de IRS.
 * @param contador - valor correspondente ao número de linhas com dados do IRS.
 */
void alterarTabelaIRS(IRS **irs, int *contador) {
    int remuneracao, index;

    remuneracao = obterSalarioAlterar((*irs)[0].salario, MSG_OBTER_REMUNERACAO_ALT);
    index = pesquisarSalarioAlterar(*irs, *contador, remuneracao, 0, (*contador)-1);
    if (index == -1) {
        puts(ERRO_PESQUISA_SALARIO);
    } else {
        printf("O que pretende alterar:");
        printf("\n1 - Remuneração mensal");
        printf("\n2 - Percentagens");
        printf("\n3 - Ambas as opções\n");
        switch (obterInteiro(1, 3, MSG_OBTER_OPCAO)) {
            case 1:
                alterarIRSSalario(*irs, index, *contador);
                break;
            case 2:
                alterarIRSPercentagens(*irs, index, *contador);
                break;
            case 3:
                alterarIRSSalario(*irs, index, *contador);
                alterarIRSPercentagens(*irs, index, *contador);
                break;
        }
    }
}

/**
 * Função utilizada para apagar uma linha de dados da tabela de IRS.
 * @param irs  - apontador onde se encontram guardados os dados do IRS.
 */
void apagarDadosIRS(IRS *irs) {
    irs->salario = 0;
    for (int i = 0; i < 6; i++) {
        irs->percentagem[i] = 0;
    }
}

/**
 * Função utilizada para verificar se um valor de IRS existe e caso exista, chamar a função "apagarDadosIRS".
 * @param irs  - apontador onde se encontram guardados os dados do IRS.
 * @param contador - valor correspondente ao número de linhas com dados do IRS.
 */
void eliminarTabelaIRS(IRS **irs, int *contador) {
    int remuneracao, x, i;

    remuneracao = obterSalarioAlterar((*irs)[0].salario, MSG_OBTER_REMUNERACAO_ALT);
    x = pesquisarSalarioAlterar(*irs, *contador, remuneracao, 0, (*contador)-1);
    if (x == -1) {
        puts(ERRO_PESQUISA_SALARIO);
    } else {
        for (i = x; i < (*contador - 1); i++) {
            (*irs)[i] = (*irs)[i + 1];
        }
        apagarDadosIRS(&(*irs)[i]);
        (*contador)--;
        (*irs)[*contador - 1].salario = (*irs)[*contador - 2].salario;
    }
}

/**
 * Função utilizada para obter um valor da tabela do IRS.
 * @param irs - apontador onde se encontram guardados os dados relativos à tabela de IRS.
 * @param contador - valor correspondente ao número de linhas existentes no ficheiro de IRS correspondente.
 * @param salario - valor correspondente ao valor do salário a ser pesquisado na tabela de IRS.
 * @param nFilhos - valor correspondente ao número de filhos a ser pesquisado na tabela de IRS.
 * @return valor correspondente a um valor da tabela do IRS.
 */
float getIrsFinal(IRS *irs, int contador, float salario, int nFilhos){
    for(int i=0; i<contador; i++){
        if(i < contador-1){
            if(irs[i].salario > salario){
                if(nFilhos<5){                  
                    return irs[i].percentagem[nFilhos];
                }else{ 
                    return irs[i].percentagem[5];
                }
            } 
        }else{
            if(nFilhos<5){                       
                return irs[i].percentagem[nFilhos];
            }else{   
                return irs[i].percentagem[5];
            }            
        }
    }
}

/**
 * Função utilizada para verificar o estado civil recebido como parâmetro e chamar a função "getIrsFinal".
 * @param irsdados - apontador onde se encontram guardados os dados relativos à tabela de IRS.
 * @param salario - valor correspondente ao valor do salário a ser pesquisado na tabela de IRS.
 * @param nFilhos - valor correspondente ao número de filhos a ser pesquisado na tabela de IRS.
 * @param estadoCivil - valor correspondente ao estado civil a ser processado.
 * @return valor correspondente ao retorno da função "getIrsFinal".
 */
float getIrs(IRSDados *irsdados, float salario, int nFilhos, int estadoCivil){
    switch(estadoCivil){
        case Divorciado:
        case Solteiro:
            return getIrsFinal(irsdados->solteiroIRS, irsdados->contadorSolteiroIRS, salario, nFilhos);
        case Casado:
            return getIrsFinal(irsdados->casadoUnicoIRS, irsdados->contadorCasadoUnicoIRS, salario, nFilhos);
        default:
            return getIrsFinal(irsdados->casadoDoisIRS, irsdados->contadorCasadoDoisIRS, salario, nFilhos);
    }
}