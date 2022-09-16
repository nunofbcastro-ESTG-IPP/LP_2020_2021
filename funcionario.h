#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include "segurancaSocial.h"
#include <limits.h>
#include "irs.h"

#define INC                           5

#define ERRO_FUNCIONARIO_NAO_EXISTE   "O funcionario não existe na lista."
#define ERRO_LISTA_VAZIA              "A lista de funcionarios está vazia."
#define ERRO_FUNCIONARIO_EXISTE       "O código de funcionário já se encontra atribuído."
#define ERRO_FUNCIONARIO_ELIMINADO    "O funcionário já não se encontra na empresa."
#define SUCESS_FUNCIONARIO            "Funcionario inserido com sucesso"

#define MIN_COD_FUNCIONARIO           0
#define MAX_COD_FUNCIONARIO           INT_MAX
#define MSG_OBTER_COD_FUNCIONARIO     "Insira um código de funcionário: "

#define MAX_NOME_FUNCIONARIO          50
#define MSG_OBTER_NOME                "Insira o nome do funcionario: "
#define MSG_ESCOLHER_NOME             "Qual é o funcionário que pertende visualizar:"

#define MSG_OBTER_NUM_TELEFONE        "Insira o telefone do funcionário: "

#define MSG_OBTER_NUM_TELEMOVEL       "Insira o telemovel do funcionário: "

#define MIN_ESTADO_CIVIL              0
#define MAX_ESTADO_CIVIL              3
#define MSG_OBTER_ESTADO_CIVIL        "Insira o estado civil do funcionário (0 - Solteiro, 1 - Casado, 2 - Divorciado, 3 - Viuvo): "

#define MIN_NUM_FILHOS                0
#define MAX_NUM_FILHOS                20
#define MSG_OBTER_NUM_FILHOS          "Insira o número de filhos dependentes do funcionário: "

#define MIN_CARGO                     0
#define MAX_CARGO                     2
#define MSG_OBTER_CARGO               "Insira o cargo do funcionário (0 - Empregado, 1 - Chefe, 2 - Administrador): "

#define MSG_OBTER_DATA_NASC           "Insira a data de nascimento (dia/mes/ano): "
#define MSG_OBTER_DATA_ENTRADA        "Insira a data de entrada da empresa (dia/mes/ano): "
#define MSG_OBTER_DATA_SAIDA          "Insira a data de saida da empresa (dia/mes/ano): "
#define MIN_DIA                       0
#define MAX_DIA                       31

#define MIN_MES                       1
#define MAX_MES                       12

#define MIN_ANO                       1990
#define MAX_ANO                       2021
#define MSG_OBTER_OPCAO               "\nOpção: "

#define MIN_VALOR_HORA                5
#define MAX_VALOR_HORA                100
#define MSG_OBTER_VALOR_HORA          "Insira o valor que o empregado ganha à hora: "

#define MSG_MEDIA_FALTAS              "O funcionário %s tem uma média de %.2f %% faltas no ano %d"
#define MSG_NUM_DIAS_DEVIA_TRAB       "Insira o número de dias que o trabalhador devia trabalhar: "
#define MSG_NUM_DIAS_TRAB             "Insira o número de dias que trabalhou: "
#define MSG_NUM_DIAS_COMPLETOS        "Insira o número de dias completos que trabalhou: "
#define MSG_NUM_DIAS_FIM_SEMANA       "Insira o número de dias que trabalhou ao fim de semana: "
#define MSG_OBTER_MESES_INSERIR       "\nNúmero de meses que pertende inserir: "
#define MSG_DADOS_ANO_PREENCHIDOS     "\nJá inseriu todos os dados desse ano."
#define MSG_ALTERAR_DADOS_ANO         "\nInsira o ano que pertende alterar: "
#define MSG_INSIRA_ANO                "Insira o ano que pertende ver:"
#define MSG_SEM_GASTOS_ANO            "\nA empresa não teve gastos no ano %d"
#define MSG_GASTOS_ANO                "\nGastos do ano %d: %.2f"
#define MSG_INSIRA_MES                "\nInsira o mês que pertende ver:"
#define MSG_SEM_GASTOS_MES            "\nA empresa não teve gastos no mês %d do ano %d"
#define MSG_GASTOS_MES                "\nGastos do mês %d do ano %d: %.2f"
#define MSG_SEM_DADOS                 "\nSem dados."

typedef struct {
    int Mes;
    int nMaxDias;
    int nDiasCompletos;
    int nMeiosDias;
    int nDiasFimSemana;
    int nDiasTrabalhados;
    int nFaltas;
    float salarioBase;
    float salarioFinal;
    float almoco;
    float bonus;
    float irs;
    float segurancaSocial;
    float segurancaSocialPatronal;
} Mes;

typedef struct {
    Mes *meses;
    int ano;
    int numeroMeses;
    int tamMeses;
} Ano;

typedef struct {
    Ano *anos;
    int numeroAnos;
    int tamAnos;
} Trabalho;

typedef enum {
    Solteiro, Casado, Divorciado, Viuvo
} EstadoCivil;

typedef enum {
    Empregado, Chefe, Administrador
} Cargo;

typedef struct {
    int dia, mes, ano;
} Data;

typedef struct {
    int codigoFuncionario;
    char nome[MAX_NOME_FUNCIONARIO];
    int numeroTelefone;
    int numeroTelemovel;
    EstadoCivil estadoCivil;
    int numeroFilhosDependentes;
    Cargo cargo;
    //Salario
    Trabalho trabalho;
    float valorHora;
    float valorSubsidioAlimentacao;
    //FimSalario
    Data dataNascimento;
    Data dataEntradaEmpresa;
    Data dataSaidaEmpresa;
} Funcionario;

typedef struct {
    int nFuncionarios;
    int maxFuncionarios;
    int idEmpresa;
    Funcionario *funcionarios;
} Empresa;

//funcionario
void inserirFuncionarios(Empresa *empresa);
void atualizarFuncionarios(Empresa *empresa);
void eliminarFuncionarios(Empresa *empresa);
void pesquisarFuncionarioCodigo(Empresa *empresa);
void pesquisarFuncionarioNome(Empresa *empresa);
void listaFuncionarios(Empresa *empresa);
void listaFuncionariosAtuais(Empresa *empresa);
void listaFuncionariosEliminados(Empresa *empresa);
void armazenaDados(Empresa *empresa, char *ficheiro);
void importaDados(Empresa *empresa, char *ficheiro);
int procurarFuncionarios(Empresa *empresa, int codigo, int inicio, int fim);
void mediaFaltas(Empresa *empresa);
void pesquisarTaxaFuncionario(TaxasContributivas *taxasContributivas, Empresa *empresa);

//salario
void inserirTrabalho(Empresa *empresa, IRSDados *irsdados, TaxasContributivas *taxasContributivas);
void listarTrabalho(Empresa *empresa);
int listarGastosMes(Empresa *empresa);
int listarGastosAno(Empresa *empresa);
int procurarAnoTrabalho(Funcionario *funcionario, int ano, int inicio, int fim);
void listarFuncValorHora(Empresa *empresa);
int getTaxaContributiva(TaxasContributivas *taxasContributivas, Funcionario *funcionario, int idade, int anosTrabalho);
int verificaAnoMes(Empresa *empresa, int ano, int mes);
int procurarMesTrabalho(Ano *ano, int mes, int inicio, int fim);
void adicionarAno(Funcionario *funcionario, int *idAno, int ano);
void ordenarPorMesTrabalho(Mes *meses, int inicio, int fim);

#endif /* FUNCIONARIO_H */

