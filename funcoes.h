#ifndef FUNCOES_H
#define FUNCOES_H

#include "segurancaSocial.h"
#include "funcionario.h"

int primeirosDigitos(int n, int nd);
int numero_digitos(int n);
void limpar();
int verificaAnoBissexto(int ano);
int verificaData(int dia, int mes, int ano);
int getAnoAtual();
int getNumeroDiasMes(int mes, int ano);
int verifica_Telemovel(int numero);
int verificaDataNascimento(int dia, int mes, int ano);
int verificarPalavras(char *frase, char *verifica);
void juntar2Strings(char *s1, char *s2);
void juntar4Strings(char *s1, char *s2, char *s3, char *s4);
int verificaString(char *s1, char *s2);
int getDiasFinsSemana(int mes, int ano) ;
int getTaxaContributiva(TaxasContributivas *taxasContributivas, Funcionario *funcionario, int idade,int anosTrabalho);
int idadeFimMes(int mes, int ano, int mesAtual, int anoAtual);
int verificaDataSaida(int dia, int mes, int ano);

#endif /* FUNCOES_H */

