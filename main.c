/*!
 * @mainpage LP_G13_Projeto
 * @version 1
 * @author Jorge Correia - 8200592 e Nuno Castro - 8200591\n
 * Turma: LEI1T1-B\n
 * Grupo: 13\n
 * Disciplina: Laboratório de Programação\n
 * Ano Letivo: 2020/2021
 */

/*
 * A classe input.h foi-nos fornecida pelo professor Óscar de Fundamentos de programação, além das funções fornecidas por ele adicionamos outra que precisava-mos ao longo do projeto.
 * Quando aparecem pesquisas são baseadas na pesquisa binaria do professor Óscar.
 * Quando aparecer a função ordenar nos usamos como base uma da internet(https://beginnersbook.com/2015/02/quicksort-program-in-c/).
 */

#include <stdio.h>
#include <stdlib.h>
#include "funcionario.h"
#include "funcoes.h"
#include "input.h"
#include "irs.h"
#include "dados.h"
#include "segurancaSocial.h"

#define PROJETO                       "Projeto AC - Grupo 13"

/**
 * Função utilizada como menu para as funcionalidades da gestão dos funcionários.
 * @param empresa - apontador onde se encontram guardados os funcionários.
 */
void MenuGestaoFuncionarios(Empresa *empresa) {
    int c = 0;
    int op;
    
    do {
        printf("\nMenu de gestão de funcionários");
        printf("\n1 - Inserir funcionário");
        printf("\n2 - Editar funcionário");
        printf("\n3 - Remover funcionário");
        printf("\n4 - Listar todos os funcionarios"); 
        printf("\n\t\t0 - Voltar");
        printf("\n------------------------------------------------------------");
        printf("\nFuncionários: %d", empresa->nFuncionarios);

        op = obterInteiro(0, 4, MSG_OBTER_OPCAO);
        switch (op) {
            case 1:
                system("clear");
                inserirFuncionarios(empresa);
                limpar();
                break;
            case 2:
                system("clear");
                atualizarFuncionarios(empresa);
                limpar();
                break;
            case 3:
                system("clear");
                eliminarFuncionarios(empresa);
                limpar();
                break;
            case 4:
                system("clear");
                listaFuncionarios(empresa);
                limpar();
                break;
            case 0:
                c = 1;
                break;
        }
    } while (c == 0);
}

/**
 * Função utilizada como menu para as funcionalidades da gestão do IRS.
 * @param irsdados - apontador onde se encontram guardados dados do IRS.
 * @param msg - valor correspondente à mensagem relativa à tabela de IRS escolhida no menu "MenuGestaoTabelasIRS".
 * @param n - valor correspondente ao ficheiro selecionado.
 */
void MenuGestaoIRS(IRSDados *irsdados, char *msg, int n) {
    int c = 0;
    int op;
    do {
        printf("\nMenu IRS - tabela %s", msg);
        printf("\n1 - Adicionar");
        printf("\n2 - Alterar");
        printf("\n3 - Eliminar");
        printf("\n4 - Listar");
        printf("\n\t\t0 -Voltar");
        printf("\n------------------------------------------------------------");

        op = obterInteiro(0, 4, MSG_OBTER_OPCAO);
        switch (op) {
            case 1:
                system("clear");
                if (n == 1) {
                    adicionarTabelaIRS(&irsdados->solteiroIRS, &irsdados->contadorSolteiroIRS, &irsdados->tamcontadorSolteiroIRS);
                } else if (n == 2) {
                    adicionarTabelaIRS(&irsdados->casadoUnicoIRS, &irsdados->contadorCasadoUnicoIRS, &irsdados->tamcontadorCasadoUnicoIRS);
                } else {
                    adicionarTabelaIRS(&irsdados->casadoDoisIRS, &irsdados->contadorCasadoDoisIRS, &irsdados->tamcontadorCasadoDoisIRS);
                }
                limpar();
                break;
            case 2:
                system("clear");
                if (n == 1) {
                    alterarTabelaIRS(&irsdados->solteiroIRS, &irsdados->contadorSolteiroIRS);
                } else if (n == 2) {
                    alterarTabelaIRS(&irsdados->casadoUnicoIRS, &irsdados->contadorCasadoUnicoIRS);
                } else {
                    alterarTabelaIRS(&irsdados->casadoDoisIRS, &irsdados->contadorCasadoDoisIRS);
                }
                limpar();
                break;
            case 3:
                system("clear");
                if (n == 1) {
                    eliminarTabelaIRS(&irsdados->solteiroIRS, &irsdados->contadorSolteiroIRS);
                } else if (n == 2) {
                    eliminarTabelaIRS(&irsdados->casadoUnicoIRS, &irsdados->contadorCasadoUnicoIRS);
                } else {
                    eliminarTabelaIRS(&irsdados->casadoDoisIRS, &irsdados->contadorCasadoDoisIRS);
                }
                limpar();
                break;
            case 4:
                system("clear");
                if (n == 1) {
                    listarIRS(irsdados->solteiroIRS, irsdados->contadorSolteiroIRS, "Listagem Tabela não casado");
                } else if (n == 2) {
                    listarIRS(irsdados->casadoUnicoIRS, irsdados->contadorCasadoUnicoIRS, "Listagem Tabela casado unico titular");
                } else {
                    listarIRS(irsdados->casadoDoisIRS, irsdados->contadorCasadoDoisIRS, "Listagem Tabela casado dois titulares");
                }
                limpar();
                break;
            case 0:
                c = 1;
                break;
        }
    } while (c == 0);
}

/**
 * Função utilizada como menu para escolher o ficheiro de IRS a utilizar (ficheiro não casado, ficheiro casado unico titular e casado dois titulares.)
 * @param irsdados - apontador onde se encontram guardados dados do IRS.
 */
void MenuGestaoTabelasIRS(IRSDados *irsdados) {
    int c = 0;
    int op;
    do {
        printf("\nMenu de gestão do IRS");
        printf("\n1 - Tabela não casado");
        printf("\n2 - Tabela casado unico titular");
        printf("\n3 - Tabela casado dois titulares");
        printf("\n\t\t0 -Voltar");
        printf("\n------------------------------------------------------------");

        op = obterInteiro(0, 3, MSG_OBTER_OPCAO);
        switch (op) {
            case 1:
                system("clear");
                MenuGestaoIRS(irsdados, "não casado", op);
                system("clear");
                break;
            case 2:
                system("clear");
                MenuGestaoIRS(irsdados, "casado unico titular", op);
                system("clear");
                break;
            case 3:
                system("clear");
                MenuGestaoIRS(irsdados, "casado dois titulares", op);
                system("clear");
                break;
            case 0:
                c = 1;
                break;
        }
    } while (c == 0);
}

/**
 * Função utilizada como menu para as funcionalidades da gestão das taxas contributivas.
 * @param taxasContributivas - apontador onde se encontram guardados dados das taxas contributivas.
 */
void MenuGestaoSegurancaSocial(TaxasContributivas *taxasContributivas) {
    int c = 0;
    int op;
    do {
        printf("\nMenu de gestão da segurança social");
        printf("\n1 - Criar");
        printf("\n2 - Alterar");
        printf("\n3 - Listar");
        printf("\n\t\t0 -Voltar");
        printf("\n------------------------------------------------------------");

        op = obterInteiro(0, 3, MSG_OBTER_OPCAO);
        switch (op) {
            case 1:
                system("clear");
                adicionarTaxaContributiva(taxasContributivas);
                limpar();
                break;
            case 2:
                system("clear");
                atualizarTaxaContributiva(taxasContributivas);
                limpar();
                break;
            case 3:
                system("clear");
                listarTaxasContributivas(taxasContributivas);
                limpar();
                break;
            case 0:
                c = 1;
                break;
        }
    } while (c == 0);
}

/**
 * Função utilizada como menu para as funcionalidades do processamento do salário.
 * @param empresa - apontador onde se encontram guardados os funcionários.
 * @param irsdados - apontador onde se encontram guardados dados do IRS.
 * @param taxasContributivas - apontador onde se encontram guardados dados das taxas contributivas.
 * @param nomesEmpresas - apontador onde se encontram guardados os nomes das empresas.
 */
void MenuProcessamentoSalario(Empresa *empresa, IRSDados *irsdados, TaxasContributivas *taxasContributivas, NomesEmpresas *nomesEmpresas) {
    int c = 0;
    int op;
    do {
        printf("\nMenu de processamento do salário");
        printf("\n1 - Calculo do Salario");
        printf("\n2 - Listar Salario");
        printf("\n3 - Exportar Salarios");
        printf("\n4 - Importar Salarios");
        printf("\n\t\t0 - Voltar");
        printf("\n------------------------------------------------------------");

        op = obterInteiro(0, 4, MSG_OBTER_OPCAO);
        switch (op) {
            case 1:
                system("clear");
                inserirTrabalho(empresa, irsdados, taxasContributivas);
                limpar();
                break;
            case 2:
                system("clear");
                listarTrabalho(empresa);
                limpar();
                break;
            case 3:
                system("clear");
                exportarRelatorio(empresa, irsdados, nomesEmpresas, taxasContributivas);
                limpar();
                break;
            case 4:
                system("clear");
                importarRelatorio(empresa, nomesEmpresas);
                limpar();
                break;
            case 0:
                c = 1;
                break;
        }
    } while (c == 0);
}

/**
 * Função utilizada como menu para as funcionalidades de pesquisas relacionadas com os funcionários.
 * @param empresa - apontador onde se encontram guardados os funcionários.
 */
void MenuPesquisaFuncionario(Empresa *empresa) {
    int c = 0;
    int op;
    do {
        printf("\nMenu de pesquisa de funcionario");
        printf("\n1 - Pesquisa Funcionario por codigo"); 
        printf("\n2 - Pesquisar Funcionario por nome");
        printf("\n3 - Listar todos os funcionarios da empresa atualmente"); 
        printf("\n4 - Listar todos os funcionarios que já saíram da empresa");
        printf("\n\t\t0 - Voltar");
        printf("\n------------------------------------------------------------");

        op = obterInteiro(0, 4, MSG_OBTER_OPCAO);
        switch (op) {
            case 1:
                system("clear");
                pesquisarFuncionarioCodigo(empresa);
                limpar();
                break;
            case 2:
                system("clear");
                pesquisarFuncionarioNome(empresa);
                limpar();
                break;
            case 3:
                system("clear");
                listaFuncionariosAtuais(empresa);
                limpar();
                break;
            case 4:
                system("clear");
                listaFuncionariosEliminados(empresa);
                limpar();
                break;
            case 0:
                c = 1;
                break;
        }
    } while (c == 0);
}

/**
 * Função utilizada como menu para as funcionalidades de pesquisas relacionadas com os gastos de uma determinada empresa.
 * @param empresa - apontador onde se encontram guardados os funcionários.
 */
void MenuGastosEmpresa(Empresa *empresa) {
    int c = 0;
    int op;
    do {
        printf("\nMenu de pesquisa de gastos de empresa");
        printf("\n1 - Gastos da empresa por ano"); 
        printf("\n2 - Gastos da empresa por mes"); 
        printf("\n\t\t0 - Voltar");
        printf("\n------------------------------------------------------------");

        op = obterInteiro(0, 2, MSG_OBTER_OPCAO);
        switch (op) {
            case 1:
                system("clear");
                listarGastosAno(empresa);
                limpar();
                break;
            case 2:
                system("clear");
                listarGastosMes(empresa);
                limpar();
                break;
            case 0:
                c = 1;
                break;
        }
    } while (c == 0);
}

/**
 * Função utilizada como menu para as funcionalidades de pesquisas.
 * @param empresa - apontador onde se encontram guardados os funcionários.
 * @param taxasContributivas - apontador onde se encontram guardados dados das taxas contributivas.
 */
void MenuPesquisas(Empresa *empresa, TaxasContributivas *taxasContributivas) {
    int c = 0;
    int op;
    do {
        printf("\nMenu de pesquisas");//FALTA LISTAGEM TABELAS IRS
        printf("\n1 - Pesquisas de Funcionarios"); 
        printf("\n2 - Gastos da empresa"); 
        printf("\n3 - Media de falta de funcionario"); 
        printf("\n4 - Funcionários que ganham mais do que x à hora");
        printf("\n5 - Taxa contributiva que um funcionario usa");
        printf("\n\t\t0 - Voltar");
        printf("\n------------------------------------------------------------");

        op = obterInteiro(0, 5, MSG_OBTER_OPCAO);
        switch (op) {
            case 1:
                system("clear");
                MenuPesquisaFuncionario(empresa);
                system("clear");
                break;
            case 2:
                system("clear");
                MenuGastosEmpresa(empresa);
                system("clear");
                break;
            case 3:
                system("clear");
                mediaFaltas(empresa);
                limpar();
                break;
            case 4:
                system("clear");
                listarFuncValorHora(empresa);
                limpar();
                break;
            case 5:
                system("clear");
                pesquisarTaxaFuncionario(taxasContributivas, empresa);
                limpar();
                break;
            case 0:
                c = 1;
                break;
        }
    } while (c == 0);
}

/**
 * Função utilizada como menu principal.
 * @param empresa - apontador onde se encontram guardados os funcionários.
 * @param irsdados - apontador onde se encontram guardados dados do IRS.
 * @param nomesEmpresas - apontador onde se encontram guardados os nomes das empresas.
 * @param taxasContributivas - apontador onde se encontram guardados dados das taxas contributivas.
 */
void Menu(Empresa *empresa, IRSDados *irsdados, NomesEmpresas *nomesEmpresas, TaxasContributivas *taxasContributivas) {
    int c = 0;
    int op;
    do {//COMENTARIOS ATUALIZADOS (09/01/2021)
        printf("\nMenu");
        printf("\n1 - Gestão de funcionários"); 
        printf("\n2 - Gestão de IRS"); 
        printf("\n3 - Gestão da segurança social"); 
        printf("\n4 - Processamento do salário"); 
        printf("\n5 - Pesquisas"); 
        printf("\n6 - Guardar dados");
        printf("\n7 - Importar dados"); 
        printf("\n\t\t0 - Sair");
        printf("\n------------------------------------------------------------");

        op = obterInteiro(0, 7, MSG_OBTER_OPCAO);
        switch (op) {
            case 1:
                system("clear");
                MenuGestaoFuncionarios(empresa);
                system("clear");
                break;
            case 2:
                system("clear");
                MenuGestaoTabelasIRS(irsdados);
                system("clear");
                break;
            case 3:
                system("clear");
                MenuGestaoSegurancaSocial(taxasContributivas);
                system("clear");
                break;
            case 4:
                system("clear");
                MenuProcessamentoSalario(empresa, irsdados, taxasContributivas, nomesEmpresas);
                system("clear");
                break;
            case 5:
                system("clear");
                MenuPesquisas(empresa, taxasContributivas);
                system("clear");
                break;
            case 6:
                system("clear");
                guardar(empresa, irsdados, nomesEmpresas, taxasContributivas);
                limpar();
                break;
            case 7:
                system("clear");
                importar(empresa, irsdados, nomesEmpresas, taxasContributivas);
                limpar();
                break;
            case 0:
                c = 1;
                break;
        }
    } while (c == 0);
}

/**
 * A função Main é por onde é iniciado o programa.
 */
int main(int argc, char** argv) {
    Empresa empresa = {.nFuncionarios = 0, .maxFuncionarios = 0, .idEmpresa = -1, .funcionarios = NULL};
    IRSDados irsdados = {.casadoUnicoIRS = NULL, .contadorCasadoUnicoIRS = 0, .tamcontadorSolteiroIRS = 0, .casadoDoisIRS = NULL,
        .contadorCasadoDoisIRS = 0, .tamcontadorCasadoUnicoIRS = 0, .solteiroIRS = NULL, .contadorSolteiroIRS = 0, .tamcontadorCasadoDoisIRS = 0};
    NomesEmpresas nomesEmpresas = {.nomesEmpresas = NULL, .numeroEmpresas = 0, .numeroMaxEmpresas = 0};
    TaxasContributivas taxasContributivas = {.maxTaxasContributivas = 0, .numeroTaxasContributivas = 0, .taxasContributivas = NULL};

    importarNomesEmpresas(&nomesEmpresas, ficheiroNomeEmpresas);
    carregarDadosFicheiroTaxasContributivas(&taxasContributivas, ficheiroTaxasContributiva);
    carregarDadosFicheiroIRS(&irsdados.solteiroIRS, &irsdados.contadorSolteiroIRS, &irsdados.tamcontadorSolteiroIRS, FicheiroNaoCasado);
    carregarDadosFicheiroIRS(&irsdados.casadoUnicoIRS, &irsdados.contadorCasadoUnicoIRS, &irsdados.tamcontadorCasadoUnicoIRS, FicheiroCasadoUnico);
    carregarDadosFicheiroIRS(&irsdados.casadoDoisIRS, &irsdados.contadorCasadoDoisIRS, &irsdados.tamcontadorCasadoDoisIRS, FicheiroCasadoDois);

    puts(PROJETO);
    Menu(&empresa, &irsdados, &nomesEmpresas, &taxasContributivas);
    
    limparDados(&empresa, &irsdados, &nomesEmpresas, &taxasContributivas, 1);
    
    return (EXIT_SUCCESS);
}