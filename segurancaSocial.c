#include <stdio.h>
#include <stdlib.h>
#include "segurancaSocial.h"
#include "input.h"

/**
 * Função utilizada para importar a informação das taxas contributivas de um ficheiro.
 * @param taxasContributivas - apontador onde irão ficar guardadas os dados das taxas contributivas.
 * @param nomeFicheiro - valor correspondente ao nome do ficheiro onde se encontra guardada a informação.
 */
void carregarDadosFicheiroTaxasContributivas(TaxasContributivas *taxasContributivas, char *nomeFicheiro) {
    FILE *fp = fopen(nomeFicheiro, "r");
    if (fp == NULL) {
        puts("Erro ao abrir ficheiro.");
    }
    fscanf(fp, "%d\n", &taxasContributivas->numeroTaxasContributivas);
    if (taxasContributivas->numeroTaxasContributivas > 0) {
        taxasContributivas->taxasContributivas = (TaxaContributiva*) calloc(taxasContributivas->numeroTaxasContributivas + 5, sizeof (TaxaContributiva));
        if (taxasContributivas->taxasContributivas != NULL) {
            taxasContributivas->maxTaxasContributivas = taxasContributivas->numeroTaxasContributivas + 5;
            for (int i = 0; i < taxasContributivas->numeroTaxasContributivas; i++) {
                fscanf(fp, "%[^/]/%f/%f/%f/%d/%d/%d/%d\n", 
                        &taxasContributivas->taxasContributivas[i].texto, 
                        &taxasContributivas->taxasContributivas[i].EntidadeEmpregadora,
                        &taxasContributivas->taxasContributivas[i].Trabalhador, 
                        &taxasContributivas->taxasContributivas[i].Global,
                        &taxasContributivas->taxasContributivas[i].cargo,
                        &taxasContributivas->taxasContributivas[i].sinal,
                        &taxasContributivas->taxasContributivas[i].idade,
                        &taxasContributivas->taxasContributivas[i].anosEmpresa);
            }
        } else {
            puts("Erro ao alocar memória nas Taxas Contributivas");
            taxasContributivas->numeroTaxasContributivas = 0;
        }
    }
    fclose(fp);
}

/**
 * Função utilizada para armazenar a informação das taxas contributivas num ficheiro.
 * @param taxasContributivas - apontador onde se encontram os dados das taxas contributivas.
 * @param nomeFicheiro - valor correspondente ao nome do ficheiro onde serão armazenadas as informações.
 */
void guardarDadosFicheiroTaxasContributivas(TaxasContributivas *taxasContributivas, char *nomeFicheiro) {
    FILE *fp;
    fp = fopen(nomeFicheiro, "w");
    if (fp == NULL) {
        puts("Erro ao abrir ficheiro.");
    }
    fprintf(fp, "%d", taxasContributivas->numeroTaxasContributivas);
    for (int i = 0; i < taxasContributivas->numeroTaxasContributivas; i++) {
        fprintf(fp, "\n%s/%f/%f/%f/%d/%d/%d/%d", 
                taxasContributivas->taxasContributivas[i].texto,
                taxasContributivas->taxasContributivas[i].EntidadeEmpregadora,
                taxasContributivas->taxasContributivas[i].Trabalhador,
                taxasContributivas->taxasContributivas[i].Global,
                taxasContributivas->taxasContributivas[i].cargo,
                taxasContributivas->taxasContributivas[i].sinal,
                taxasContributivas->taxasContributivas[i].idade,
                taxasContributivas->taxasContributivas[i].anosEmpresa);
    }
    fclose(fp);
}

/**
 * Função utilizada para listar uma taxa contributiva.
 * @param taxaContributiva - apontador onde se encontram os dados da taxa contributiva.
 */
void listaTaxaContributiva(TaxaContributiva *taxaContributiva){    
    printf("\nTaxa Contrivutiva %s",taxaContributiva->texto);
    if(taxaContributiva->idade != -1){
        if(taxaContributiva->sinal == 1){
            printf("\nEsta taxa é para pessoa com idade superior ou igual a %d", taxaContributiva->idade);
        }else{
            printf("\nEsta taxa é para pessoa com idade inferior a %d", taxaContributiva->idade);
        }
    }else if(taxaContributiva->anosEmpresa != -1){
        if(taxaContributiva->sinal == 1){
            printf("\nEsta taxa é para pessoa com idade superior ou igual a %d", taxaContributiva->anosEmpresa);
        }else{
            printf("\nEsta taxa é para pessoa com idade inferior a %d", taxaContributiva->anosEmpresa);
        }
    }
    switch (taxaContributiva->cargo) {
        case Empregado:
            printf("\nCargo: Empregado");
            break;
        case Chefe:
            printf("\nCargo: Chefe");
            break;
        case Administrador:
            printf("\nCargo: Administrador");
            break;
    }
    printf("\nPercentagem Entidade Empregadora: %.2f%%", taxaContributiva->EntidadeEmpregadora * 100);
    printf("\nPercentagem Trabalhador: %.2f%%", taxaContributiva->Trabalhador * 100);
    printf("\nPercentagem Global: %.2f%%", taxaContributiva->Global * 100);    
}

/**
 * Função utilizada para verificar se existem taxas contributivas e caso existam, chamar a função "listaTaxaContributiva".
 * @param taxasContributivas - apontador onde se encontram os dados das taxas contributivas.
 */
void listarTaxasContributivas(TaxasContributivas *taxasContributivas) {
    printf("\nSeguranca Social Taxas:");
    if (taxasContributivas->numeroTaxasContributivas > 0) {
        for (int i = 0; i < taxasContributivas->numeroTaxasContributivas; i++) {
            listaTaxaContributiva(&taxasContributivas->taxasContributivas[i]);
            printf("\n---------------------------------------------------------");
        }
    }
}

/**
 * Função utilizada para inserir uma restrição de idade.
 * @param taxaContributiva - apontador onde se encontram os dados da taxa contributiva.
 */
void inserirTaxaContributivaIdade(TaxaContributiva *taxaContributiva){
    printf("O criterio vai ser:");
    printf("\n1 - Idade Superior ou igual");
    printf("\n2 - Idade Inferior\n");
    taxaContributiva->sinal = obterInteiro(1, 2, MSG_OBTER_OPCAO);
    taxaContributiva->idade = obterFloat(16, 100, "Idade necessária para a taxa atuar: ");
    taxaContributiva->anosEmpresa = -1;
}

/**
 * Função utilizada para inserir uma restrição de antiguidade na empresa numa taxa contributiva.
 * @param taxaContributiva - apontador onde se encontram os dados da taxa contributiva.
 */
void inserirTaxaContributivaTempoEmp(TaxaContributiva *taxaContributiva){
    printf("O criterio vai ser:");
    printf("\n1 - Tempo na empresa  Superior ou igual");
    printf("\n2 - Tempo na empresa Inferior\n");
    taxaContributiva->sinal = obterInteiro(1, 2, MSG_OBTER_OPCAO);
    taxaContributiva->idade = -1;
    taxaContributiva->anosEmpresa = obterFloat(0, 100, "Quantidade de anos de trabalho necessários para a taxa atuar: ");
}

/**
 * Função utilizada para obter as taxas contributivas em percentagem de uma taxa contributiva.
 * @param taxaContributiva - apontador onde se encontram os dados da taxa contributiva.
 */
void inserirTaxaContributivaPercentagens(TaxaContributiva *taxaContributiva){
    taxaContributiva->EntidadeEmpregadora = obterFloat(0, 100, MSG_OBTER_P_ENTIDADE_EMPREGADORA) / 100;
    taxaContributiva->Trabalhador = obterFloat(0, 100, MSG_OBTER_P_TRABALHADOR) / 100;
    taxaContributiva->Global = taxaContributiva->Trabalhador + taxaContributiva->EntidadeEmpregadora;
}

/**
 * Função utilizada para ordenar as taxas contributivas por ordem ao valor da taxa contributiva global.
 * @param taxasContributivas - apontador onde se encontram os dados das taxas contributivas.
 * @param inicio - valor correspondente à primeira posição do apontador.
 * @param fim - valor correspondente à última posição do apontador.
 */
void orderTaxasContributivas(TaxasContributivas *taxasContributivas, int inicio, int fim) {
    int i, j, pivot;
    TaxaContributiva temp;
    if (inicio < fim) {
        pivot = inicio;
        i = inicio;
        j = fim;
        while (i < j) {
            while (taxasContributivas->taxasContributivas[i].Global <= taxasContributivas->taxasContributivas[pivot].Global && i < fim)
                i++;
            while (taxasContributivas->taxasContributivas[j].Global > taxasContributivas->taxasContributivas[pivot].Global)
                j--;
            if (i < j) {
                temp = taxasContributivas->taxasContributivas[i];
                taxasContributivas->taxasContributivas[i] = taxasContributivas->taxasContributivas[j];
                taxasContributivas->taxasContributivas[j] = temp;
            }
        }

        temp = taxasContributivas->taxasContributivas[pivot];
        taxasContributivas->taxasContributivas[pivot] = taxasContributivas->taxasContributivas[j];
        taxasContributivas->taxasContributivas[j] = temp;
        orderTaxasContributivas(taxasContributivas, inicio, j - 1);
        orderTaxasContributivas(taxasContributivas, j + 1, fim);

    }
}

/**
 * Função utilizada para inserir uma nova taxa contributiva.
 * @param taxasContributivas - apontador onde se encontram os dados das taxas contributivas.
 */
void adicionarNovaTaxaContributiva(TaxasContributivas *taxasContributivas) {
    lerString(taxasContributivas->taxasContributivas[taxasContributivas->numeroTaxasContributivas].texto, 80, MSG_OBTER_INFORMACAO);

    printf("Tipos de Criterios");
    printf("\n1 - Cargo e Idade");
    printf("\n2 - Cargo e Tempo na empresa\n");
    int tipo = obterInteiro(1, 2, MSG_OBTER_OPCAO);

    taxasContributivas->taxasContributivas[taxasContributivas->numeroTaxasContributivas].cargo = obterInteiro(MIN_CARGO, MAX_CARGO, MSG_OBTER_CARGO);
    if (tipo == 1) {
        inserirTaxaContributivaIdade(&taxasContributivas->taxasContributivas[taxasContributivas->numeroTaxasContributivas]);
    } else {
        inserirTaxaContributivaTempoEmp(&taxasContributivas->taxasContributivas[taxasContributivas->numeroTaxasContributivas]);
    }
    inserirTaxaContributivaPercentagens(&taxasContributivas->taxasContributivas[taxasContributivas->numeroTaxasContributivas]);
    taxasContributivas->numeroTaxasContributivas = taxasContributivas->numeroTaxasContributivas + 1;
    orderTaxasContributivas(taxasContributivas, 0, taxasContributivas->numeroTaxasContributivas - 1);
}

/**
 * Função utilizada para alocar espaços para as taxas contributivas e chamar a função "adicionarNovaTaxaContributiva".
 * @param taxasContributivas - apontador onde se encontram os dados das taxas contributivas.
 */
void adicionarTaxaContributiva(TaxasContributivas *taxasContributivas) {
    if (taxasContributivas->numeroTaxasContributivas == taxasContributivas->maxTaxasContributivas) {
        TaxaContributiva *novo = (TaxaContributiva*) realloc(taxasContributivas->taxasContributivas,
                sizeof (TaxaContributiva) * (taxasContributivas->maxTaxasContributivas + INC));
        if (novo == NULL) {
            puts("Erro ao alocar mais memória nas taxas contributivas.");
        } else {
            taxasContributivas->taxasContributivas = novo;
            taxasContributivas->maxTaxasContributivas += INC;
            adicionarNovaTaxaContributiva(taxasContributivas);
        }
    } else {
        adicionarNovaTaxaContributiva(taxasContributivas);
    }
}

/**
 * Função utilizada para atualizar as taxas contributivas.
 * @param taxasContributivas - apontador onde se encontram os dados das taxas contributivas.
 */
void atualizarTaxaContributiva(TaxasContributivas *taxasContributivas) {
    char texto[2][17] = {"Idade", "Tempo na empresa"};

    printf("\nSegurança Social Taxas:\n");
    if (taxasContributivas->numeroTaxasContributivas > 0) {
        for (int i = 0; i < taxasContributivas->numeroTaxasContributivas; i++) {
            printf("Opção: %d", i + 1);
            listaTaxaContributiva(&taxasContributivas->taxasContributivas[i]);
            printf("\n---------------------------------------------------------\n");
        }
    }
    printf("\n\t\t0 -Voltar");
            printf("\n---------------------------------------------------------\n");
    int p = obterInteiro(0, taxasContributivas->numeroTaxasContributivas, MSG_ALTERAR_TAXA) - 1;
    if(p>-1){
        int tipo = -1;

        if (taxasContributivas->taxasContributivas[p].idade != -1) {
            tipo = 0;
        } else if (taxasContributivas->taxasContributivas[p].anosEmpresa != -1) {
            tipo = 1;
        }

        if (tipo != -1) {
            printf("O que pretende alterar:");
            printf("\n1 - %s", texto[tipo]);
            printf("\n2 - Taxas");
            printf("\n3 - Ambas as opções");
            switch (obterInteiro(1, 3, MSG_OBTER_OPCAO)) {
                case 1:
                    if (tipo == 0) {
                        inserirTaxaContributivaIdade(&taxasContributivas->taxasContributivas[p]);
                    } else {
                        inserirTaxaContributivaTempoEmp(&taxasContributivas->taxasContributivas[p]);
                    }
                    break;
                case 2:
                    inserirTaxaContributivaPercentagens(&taxasContributivas->taxasContributivas[p]);
                    orderTaxasContributivas(taxasContributivas, 0, taxasContributivas->numeroTaxasContributivas - 1);
                    break;
                case 3:
                    if (tipo == 0) {
                        inserirTaxaContributivaIdade(&taxasContributivas->taxasContributivas[p]);
                    } else {
                        inserirTaxaContributivaTempoEmp(&taxasContributivas->taxasContributivas[p]);
                    }
                    inserirTaxaContributivaPercentagens(&taxasContributivas->taxasContributivas[p]);
                    orderTaxasContributivas(taxasContributivas, 0, taxasContributivas->numeroTaxasContributivas - 1);
                    break;
            }
        } else {
            inserirTaxaContributivaPercentagens(&taxasContributivas->taxasContributivas[p]);
            orderTaxasContributivas(taxasContributivas, 0, taxasContributivas->numeroTaxasContributivas - 1);
        }
    }
}

