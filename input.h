#ifndef INPUT_H
#define INPUT_H

#include "funcionario.h"
#include "irs.h"

#define VALOR_INVALIDO                "O valor inserido é inválido."
#define SALARIO_EXISTENTE             "O salário inserido já existe."

int obterInteiro(int minValor, int maxValor, char *msg);

float obterFloat(float minValor, float maxValor, char *msg);

double obterDouble(double minValor, double maxValor, char *msg);

char obterChar(char *msg);

void lerString(char *string, unsigned int tamanho, char *msg);

int obterTelefone(char *msg);

int obterTelemovel(char *msg);

void obterDataNacimento(Data *data, char *msg);

void obterDataNacimento_Alterar(Data *data, Data *dataEntrada, char *msg);

void obterDataEntrada(Data *dataEntrada, Data *dataNasc, char *msg);

void obterDataSaida(Data *dataSaida, int ano, int mes, char *msg);

void obterSalario(IRS *irs, int contador, char *msg);

float obterSalarioAlterar(float minValor, char *msg);

float obterIRS_Percentagem(float minValor, float maxValor, char *msg);

int obterAnoFaltas(Funcionario *funcionario, char *msg);

#endif /* INPUT_H */

