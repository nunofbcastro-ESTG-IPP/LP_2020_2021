#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "funcoes.h"
#include "irs.h"

/*
 * Esta classe foi-nos fornecida pelo professor Óscar de Fundamentos de programação.
 * Além das funções fornecidas por ele adicionamos outra que precisava-mos ao longo do projeto.
 */

/**
 * Função utilizada para limpar o buffer do teclado.
 */
void cleanInputBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

/**
 * Função utilizada para leitura de valores inteiros.
 * @param minValor - valor correspondente ao limite mínimo a ser inserido.
 * @param maxValor - valor correspondente ao limite máximo a ser inserido.
 * @param msg - valor correspondente à mensagem a ser mostrada antes da leitura do valor inteiro.
 * @return valor inteiro inserido após verificação do mesmo.
 */
int obterInteiro(int minValor, int maxValor, char *msg) {
    int valor;
    printf(msg);
    while (scanf("%d", &valor) != 1 || valor < minValor || valor > maxValor) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return valor;
}

/**
 * Função utilizada para leitura de valores reais.
 * @param minValor - valor correspondente ao limite mínimo a ser inserido.
 * @param maxValor - valor correspondente ao limite máximo a ser inserido.
 * @param msg - valor correspondente à mensagem a ser mostrada antes da leitura do valor real.
 * @return valor real inserido após verificação do mesmo.
 */
float obterFloat(float minValor, float maxValor, char *msg) {
    float valor;
    printf(msg);
    while (scanf("%f", &valor) != 1 || valor < minValor || valor > maxValor) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return valor;
}

/**
 * Função utilizada para leitura de valores double.
 * @param minValor - valor correspondente ao limite mínimo a ser inserido.
 * @param maxValor - valor correspondente ao limite máximo a ser inserido.
 * @param msg - valor correspondente à mensagem a ser mostrada antes da leitura do valor double.
 * @return valor double inserido após verificação do mesmo.
 */
double obterDouble(double minValor, double maxValor, char *msg) {
    double valor;
    printf(msg);
    while (scanf("%lf", &valor) != 1 || valor < minValor || valor > maxValor) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return valor;
}

/**
 * Função utilizada para leitura de carateres.
 * @param msg - valor correspondente à mensagem a ser mostrada antes da leitura do carater.
 * @return carater inserido.
 */
char obterChar(char *msg) {
    char valor;
    printf(msg);
    valor = getchar();
    cleanInputBuffer();
    return valor;
}

/**
 * Função utilizada para leitura de strings.
 * @param string - apontador onde será guardada a string.
 * @param tamanho - valor correspondente ao tamanho máximo que a string pode ter.
 * @param msg - valor correspondente à mensagem a ser mostrada antes da leitura da string.
 */
void lerString(char *string, unsigned int tamanho, char *msg) {
    printf(msg);
    while(fgets(string, tamanho, stdin) != NULL && string[0]=='\n'){
        puts(VALOR_INVALIDO);
        printf(msg);
    }
    unsigned int len = strlen(string) - 1;
    if (string[len] == '\n') {
        string[len] = '\0';
    } else {
        cleanInputBuffer();
    }
}

/**
 * Função utilizada para leitura do número de telemóvel.
 * @param msg - valor correspondente à mensagem a ser mostrada antes da leitura do número de telemóvel.
 * @return número de telemóvel inserido após a verificação do mesmo.
 */
int obterTelemovel(char *msg) {
    int valor;
    printf(msg);
    while (scanf("%d", &valor) != 1 || verifica_Telemovel(valor) == 0 || numero_digitos(valor) != 9) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return valor;
}

/**
 * Função utilizada para leitura do número de telefone.
 * @param msg - valor correspondente à mensagem a ser mostrada antes da leitura do número de telefone.
 * @return número de telefone inserido após a verificação do mesmo.
 */
int obterTelefone(char *msg) {
    int valor;
    printf(msg);
    while (scanf("%d", &valor) != 1 || primeirosDigitos(valor, 1) != 2 || numero_digitos(valor) != 9) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return valor;
}

/**
 * Função utilizada para leitura da data de nascimento.
 * @param dataNasc - apontador onde será guardada a data de nascimento.
 * @param msg - valor correspondente à mensagem a ser mostrada antes da leitura da data de nascimento.
 */
void obterDataNacimento(Data *dataNasc, char *msg) {
    printf(msg);
    while (scanf("%d/%d/%d", &dataNasc->dia, &dataNasc->mes, &dataNasc->ano) != 3 || verificaDataNascimento(dataNasc->dia, dataNasc->mes, dataNasc->ano) != 1) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
}

/**
 * Função utilizada para alteração da data de nascimento.
 * @param dataNasc - apontador onde será guardada a data de nascimento.
 * @param dataEntrada - apontador que contém a data de entrada na empresa, utilizada para a realização de verificações.
 * @param msg - valor correspondente à mensagem a ser mostrada antes da leitura da data de nascimento.
 */
void obterDataNacimento_Alterar(Data *dataNasc, Data *dataEntrada, char *msg) {
    printf(msg);
    while (scanf("%d/%d/%d", &dataNasc->dia, &dataNasc->mes, &dataNasc->ano) != 3 || verificaDataNascimento(dataNasc->dia, dataNasc->mes, dataNasc->ano) != 1 || (dataEntrada->ano - dataNasc->ano) < 16) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
}

/**
 * Função utilizada para leitura da data de entrada na empresa.
 * @param dataEntrada - apontador onde será guardada a data de entrada na empresa.
 * @param dataNasc - apontador que contém a data de nascimento, utilizada para a realização de verificações.
 * @param msg - valor correspondente à mensagem a ser mostrada antes da leitura da data de entrada na empresa.
 */
void obterDataEntrada(Data *dataEntrada, Data *dataNasc, char *msg) {
    printf(msg);
    while (scanf("%d/%d/%d", &dataEntrada->dia, &dataEntrada->mes, &dataEntrada->ano) != 3 || (dataEntrada->ano - dataNasc->ano) < 16 || verificaDataNascimento(dataNasc->dia, dataNasc->mes, dataNasc->ano) != 1 ) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
}

/**
 * Função utilizada para leitura da data de saida da empresa.
 * @param dataSaida - apontador onde será guardada a data de saida da empresa.
 * @param dataEntrada - apontador que contém a data de entrada na empresa, utilizada para a realização de verificações.
 * @param msg - valor correspondente à mensagem a ser mostrada antes da leitura da data de saida da empresa.
 */
void obterDataSaida(Data *dataSaida, int ano, int mes, char *msg) {
    printf(msg);
    while (scanf("%d/%d/%d", &dataSaida->dia, &dataSaida->mes, &dataSaida->ano) != 3 || dataSaida->ano < ano || (dataSaida->ano == ano && dataSaida->mes < mes) 
            || verificaDataSaida(dataSaida->dia, dataSaida->mes, dataSaida->ano) != 1 ) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
}

/**
 * Função utilizada para leitura da remuneração mensal da tabela de IRS.
 * @param irs - apontador onde será guardado o salário da tabela de IRS.
 * @param contador - valor correspondente ao número de linhas existentes na tabela de IRS.
 * @param msg - valor correspondente à mensagem a ser mostrada antes da leitura do salário.
 */
void obterSalario(IRS *irs, int contador, char *msg) {
    int c = 0, erro;

    do {
        c = 1;
        puts(msg);
        erro = scanf("%f", &irs[contador].salario);
        cleanInputBuffer();
        if (irs[contador].salario > 0) {
            for (int i = 0; i < contador; i++) {
                if (irs[contador].salario == irs[i].salario) {
                    c = 0;
                    puts(VALOR_INVALIDO);
                }
            }
        } else {
            c = 0;
            printf("\n\n");
            puts(VALOR_INVALIDO);
        }
    } while (erro != 1 || c == 0);
}

/**
 * Função utilizada para leitura do salário limite da tabela de IRS.
 * @param minValor - valor correspondente ao limite mínimo a ser inserido.
 * @param msg - valor correspondente à mensagem a ser mostrada antes da leitura do salário.
 * @return valor real inserido (correspodente ao salário) após verificação do mesmo.
 */
float obterSalarioAlterar(float minValor, char *msg) {
    float valor;
    puts(msg);
    while (scanf("%f", &valor) != 1 || valor < minValor) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        puts(msg);
    }
    cleanInputBuffer();
    return valor;
}

/**
 * Função utilizada para leitura do valor percentual do IRS correspondente ao número de filhos.
 * @param minValor  - valor correspondente ao limite mínimo a ser inserido.
 * @param maxValor  - valor correspondente ao limite máximo a ser inserido.
 * @param msg - valor correspondente à mensagem a ser mostrada antes da leitura do valor percentual do IRS.
 * @return valor real inserido (correspodente ao valor percentual do IRS) após verificação do mesmo.
 */
float obterIRS_Percentagem(float minValor, float maxValor, char *msg) {
    float valor;
    printf(msg, minValor, maxValor);
    while (scanf("%f", &valor) != 1 || valor < minValor || valor > maxValor) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(msg, minValor, maxValor);
    }
    cleanInputBuffer();
    return valor;
}

/**
 * Função utilizada para obter o índice de um ano após verificação que este existe.
 * @param funcionario - apontador onde se encontram guardados os dados do funcionário.
 * @param msg - valor correspondente à mensagem a ser mostrada antes da leitura do ano.
 * @return valor inteiro correspondente ao índice do ano inserido.
 */
int obterAnoFaltas(Funcionario *funcionario, char *msg){
    int ano, idAno;
    printf("%s",msg);
    while (scanf("%d", &ano) != 1 || (idAno = procurarAnoTrabalho(funcionario, ano, 0, funcionario->trabalho.numeroAnos - 1)) == -1) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(msg);
    }
    return idAno;
}