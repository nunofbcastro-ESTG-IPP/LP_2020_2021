#include <stdio.h>
#include <time.h>
#include <ctype.h> 
#include <stdlib.h>
#include "funcoes.h"
#include "irs.h"
#include "segurancaSocial.h"

/**
 * Função utilizada para contar o número de digitos de um número.
 * @param n - valor correspondente ao número a ser verificado.
 * @return número de digitos que o número recebido possui.
 */
int numero_digitos(int n) {
    int c = 0;
    do {
        c++;
        n = n / 10;
    } while (n != 0);
    return c;
}

/**
 * Função utilizada para retornar os primeiros n digitos de um número.
 * @param n - valor correspondente ao número a ser verificado.
 * @param nd - valor correspondente à quantidade de digitos a verificar.
 * @return valor correspondente aos primeiros digitos de um número.
 */
int primeirosDigitos(int n, int nd) {
    nd = numero_digitos(n) - nd;
    for (int i = 0; i < nd; i++) {
        n = n / 10;
    }
    return n;
}

/**
 * Função utilizada para verificar se os 2 primeitos digitos são de um número de telemóvel nacional.
 * @param numero - valor correspondente ao número de telemóvel a ser verificado.
 * @return 1 (caso seja válido) ou 0 (caso não seja válido).
 */
int verifica_Telemovel(int numero) {
    int n = primeirosDigitos(numero, 2);
    if (n == 96 || n == 91 || n == 92 || n == 93) {
        return 1;
    }
    return 0;
}

/**
 * Função utilizada para parar o programa até que o utilizador pressione uma tecla que irá limpar o ecrã e fazer o programa continuar.
 */
void limpar() {
    printf("\nPressione uma tecla para continuar ...");
    getchar();
    system("clear");
}

/**
 * Função baseada na deste site https://www.marceloweb.info/verificar-se-o-ano-e-bissexto-em-c/
 * Função utilizada para verificar se um determinado ano é bissexto.
 * @param ano - valor correspondente ao ano a ser verificado.
 * @return 1 (caso seja bissexto) ou 0 (caso não seja bissexto).
 */
int verificaAnoBissexto(int ano) {
    if (ano % 400 == 0) {
        return 1;
    } else if ((ano % 4 == 0) && (ano % 100 != 0)) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * Função utilizada para obter o número de dias de um mês.
 * @param mes - valor correspondente ao mês do qual se pretende obter o numero de dias.
 * @param ano - valor correspondente ao ano do qual se pretende obter o número de dias de um mês.
 * @return valor correspondente ao número de dias do mês pretendido.
 */
int getNumeroDiasMes(int mes, int ano) {
    if (verificaAnoBissexto(ano) == 0) {
        int diasMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        return diasMes[mes - 1];
    } else {
        int diasMes[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        return diasMes[mes - 1];
    }
}

/**
 * Função baseada na resposta do user3386109 neste site https://stackoverflow.com/questions/28520421/c-comma-in-ternary-statement
 * Função utilizada para obter o dia da semana.
 * @param dia - valor correspondente ao dia do qual se pretende obter o dia da semana.
 * @param mes - valor correspondente ao mes do qual se pretende obter o dia da semana.
 * @param ano - valor correspondente ao ano do qual se pretende obter o dia da semana.
 * @return valor entre 0 e 6: 0 (Domingo), 6 (Sexta).
 */
int getDiaSemana(int dia, int mes, int ano) {
    if (mes < 3) {
        dia = dia + ano;
        ano--;
    } else {
        dia = dia + ano - 2;
    }
    return ((23 * mes / 9) + dia + 4 + ano / 4 - ano / 100 + ano / 400) % 7;
}

/**
 * Função utilizada para obter o número de dias de fim de semana de um mês.
 * @param mes - valor correspondente ao mês do qual se pretende obter o numero de dias de fim de semana.
 * @param ano - valor correspondente ao ano do qual se pretende obter o numero de dias de fim de semana.
 * @return valor correspondente ao número de dias de fim de semana de um mês.
 */
int getDiasFinsSemana(int mes, int ano) {
    int c = 0;
    for (int i = 1; i <= getNumeroDiasMes(mes, ano); i++) {
        if (getDiaSemana(i, mes, ano) == 0 || getDiaSemana(i, mes, ano) == 6) {
            c++;
        }
    }
    return c;
}

/**
 * Função utilizada para verificar se uma data de nascimento é válida.
 * @param dia - valor correspondente ao dia de nascimento.
 * @param mes - valor correspondente ao mês de nascimento.
 * @param ano - valor correspondente ao ano de nascimento.
 * @return 1 (caso seja válida) ou 0 (caso não seja válida).
 */
int verificaDataNascimento(int dia, int mes, int ano) {
    if (ano < getAnoAtual() - 100 || ano > getAnoAtual() - 16 || mes < 1 || mes > 12 || dia < 1 || dia > 31) {
        return 0;
    } else if (verificaAnoBissexto(ano) == 0) {
        int diasMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (dia <= diasMes[mes - 1]) {
            return 1;
        } else {
            return 0;
        }
    } else {
        int diasMes[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (dia <= diasMes[mes - 1]) {
            return 1;
        } else {
            return 0;
        }
    }
}

/**
 * Função utilizada para obter o ano atual, através da utilização da libraria "time.h".
 * @return valor correspondente ao ano atual.
 */
int getAnoAtual() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_year + 1900;
}

/**
 * Função utilizada para verificar se uma data é válida.
 * @param dia - valor correspondente ao dia de nascimento.
 * @param mes - valor correspondente ao mês de nascimento.
 * @param ano - valor correspondente ao ano de nascimento.
 * @return 1 (caso seja válida) ou 0 (caso não seja válida).
 */
int verificaDataSaida(int dia, int mes, int ano) {
    if (ano < getAnoAtual() - 100 || mes < 1 || mes > 12 || dia < 1 || dia > 31) {
        return 0;
    } else if (verificaAnoBissexto(ano) == 0) {
        int diasMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (dia <= diasMes[mes - 1]) {
            return 1;
        } else {
            return 0;
        }
    } else {
        int diasMes[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (dia <= diasMes[mes - 1]) {
            return 1;
        } else {
            return 0;
        }
    }
}

/**
 * Função utilizada para transformar todos os carateres de uma string em letras minúsculas.
 * @param s - valor correspondente à string a ser transformada.
 */
void minuscula(char *s) {
    for (int i = 0; s[i] != '\0'; i++) {
        s[i]=tolower(s[i]);
    }
}

/**
 * Função utilizada para obter o tamanho de uma string.
 * @param s - valor correspondente à string a verificada.
 * @return valor correspondente ao tamanho da string.
 */
int tamanhoString(char *s) {
    int i;
    for (i = 0; s[i] != '\0'; i++);
    return i;
}

/**
 * Função utilizada para comparar duas strings.
 * @param s1 - valor correspondente à primeira string.
 * @param s2 - valor correspondente à segunda string.
 * @return 1 (caso as strings sejam iguais) ou -1 (caso as strings sejam diferentes).
 */
int verificaString(char *s1, char *s2) {
    int n = tamanhoString(s1);
    if (n == tamanhoString(s2)) {
        for (int i = 0; i < n; i++) {
            if (s1[i] != s2[i]) {
                return -1;
            }
        }
        return 1;
    }
    return -1;
}

/**
 * Função utilizada para obter uma palavra de uma string.
 * @param s1 - apontador onde se encontra a palavra a ser retirada
 * @param s2 - apontador onde vai ser guardada a palavra
 * @param posicaoPalavra - valor correspondente à posição da palavra.
 */
void getPalavra(char *s1, char *s2, int posicaoPalavra) {
    int palavra = 0, i, j;
    for (i = 0; posicaoPalavra - 1 != palavra; i++) {
        if (s1[i] == ' ') {
            palavra++;
        }
    }
    for (j = 0; s1[i] != '\0' && s1[i] != ' '; j++, i++) {
        s2[j] = s1[i];
    }
    s2[j] = '\0';
}

/**
 * Função utilizada para contar as palavras de uma string.
 * @param string - apontador onde se encontra a string a ser verificada.
 * @return valor correspondente ao número de palavras.
 */
int contarPalavras(char *string) {
    int c = 0;
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == ' ' && string[i + 1] != '\0' && i != 0) {
            c++;
        }
    }
    return c + 1;
}

/**
 * Função utilizada para procurar um conjunto de palavras dentro de outra string.
 * @param frase - apontador onde se encontra a string onde é pesquisada o conjunto de palavras.
 * @param verifica - apontador onde se encontra a string com o conjunto de palavras.
 * @return 1 (caso a string verifica exista na string frase) ou 0 (caso a string verifica não exista na string frase).
 */
int verificarPalavras(char *frase, char *verifica) {
    minuscula(frase);
    minuscula(verifica);
    int npFrase = contarPalavras(frase), npVerifica = contarPalavras(verifica);
    int retorno = 0, j = 0;
    if (npFrase >= npVerifica) {
        char s1[20], s2[20];
        getPalavra(verifica, s2, 1);
        for (int i = 1; i <= npFrase && j <= npVerifica; i++) {
            getPalavra(frase, s1, i);
            if (verificaString(s1, s2) == 1) {
                j++;
                if (j < npVerifica) {
                    getPalavra(verifica, s2, j + 1);
                }
            }
        }
        if (j == npVerifica) {
            retorno = 1;
        }
    }
    return retorno;
}

/**
 * Função baseada na deste site http://devfuria.com.br/logica-de-programacao/strings-concatenar/
 * Função utilizada para juntar duas strings.
 * @param s1 - apontador onde se encontra a primeira string e onde será guardada a junção das duas strings.
 * @param s2 - apontador onde se encontra a segunda string.
 */
void juntar2Strings(char *s1, char *s2) {
    int i, j;
    for (i = 0; s1[i] != '\0'; ++i);
    for (j = 0; s2[j] != '\0'; ++j, ++i) {
        s1[i] = s2[j];
    }
    s1[i] = '\0';
}

/**
 * Função baseada na deste site http://devfuria.com.br/logica-de-programacao/strings-concatenar/
 * Função utilizada para juntar quatro strings.
 * @param s1 - apontador onde se encontra a primeira string e onde será guardada a junção das quatro strings.
 * @param s2 - apontador onde se encontra a segunda string.
 * @param s3 - apontador onde se encontra a terceira string.
 * @param s4 - apontador onde se encontra a quarta string.
 */
void juntar4Strings(char *s1, char *s2, char *s3, char *s4) {
    int i, j;
    for (i = 0; s1[i] != '\0'; ++i);
    for (j = 0; s2[j] != '\0'; ++j, ++i) {
        s1[i] = s2[j];
    }
    for (j = 0; s3[j] != '\0'; ++j, ++i) {
        s1[i] = s3[j];
    }
    for (j = 0; s4[j] != '\0'; ++j, ++i) {
        s1[i] = s4[j];
    }
    s1[i] = '\0';
}

/**
 * Função utilizada para calcular a idade de um funcionário.
 * @param mes - valor correspondente ao mês de nascimento.
 * @param ano - valor correspondente ao ano de nascimento.
 * @param mesAtual - valor correspondente ao mês do processamento do salário.
 * @param anoAtual - valor correspondente ao ano do processamento do salário.
 * @return valor correspondente à idade do funcionário.
 */
int idadeFimMes(int mes, int ano, int mesAtual, int anoAtual) {
    if (mesAtual < mes) {
        return anoAtual - ano - 1;
    } else {
        return anoAtual - ano;
    }
}

/**
 * Função utilizada para obter a taxa contributiva a ser utilizada por um funcionário.
 * @param taxasContributivas - apontador onde se encontram os dados das taxas contributivas.
 * @param funcionario  - apontador onde se encontra guardado o funcionário.
 * @param idade  - valor correspondente à idade do funcionário.
 * @param anosTrabalho - valor correspondente aos anos de trabalho do funcionário na empresa.
 * @return valor correspondente ao índice da taxa a ser utilizada.
 */
int getTaxaContributiva(TaxasContributivas *taxasContributivas, Funcionario *funcionario, int idade, int anosTrabalho) {
    for (int i = 0; i < taxasContributivas->numeroTaxasContributivas; i++) {
        if (taxasContributivas->taxasContributivas[i].cargo == funcionario->cargo) {
            if (taxasContributivas->taxasContributivas[i].anosEmpresa == -1 && taxasContributivas->taxasContributivas[i].idade == -1) {
                return i;
            } else if (taxasContributivas->taxasContributivas[i].anosEmpresa == -1 && taxasContributivas->taxasContributivas[i].idade <= idade
                    && taxasContributivas->taxasContributivas[i].sinal == 1) {
                return i;
            } else if (taxasContributivas->taxasContributivas[i].anosEmpresa == -1 && taxasContributivas->taxasContributivas[i].idade > idade
                    && taxasContributivas->taxasContributivas[i].sinal == 2) {
                return i;
            } else if (taxasContributivas->taxasContributivas[i].idade == -1 && taxasContributivas->taxasContributivas[i].anosEmpresa <= anosTrabalho
                    && taxasContributivas->taxasContributivas[i].sinal == 1) {
                return i;
            } else if (taxasContributivas->taxasContributivas[i].idade == -1 && taxasContributivas->taxasContributivas[i].anosEmpresa > anosTrabalho
                    && taxasContributivas->taxasContributivas[i].sinal == 2) {
                return i;
            }
        }
    }
    return -1;
}