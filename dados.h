
#ifndef DADOS_H
#define DADOS_H

#include "funcionario.h"
#include "irs.h"
#include "segurancaSocial.h"

#define INC                            5

#define ficheiroNomeEmpresas           "./src/nomeEmpresas.bin"
#define BASEPASTANAME                  "./src/"
#define BASEFicheiroCasadoUnico        "/CasadosDois.txt"
#define BASEFicheiroCasadoDois         "/CasadoUnico.txt"
#define BASEFicheiroNaoCasado          "/NaoCasado.txt"
#define BASEFicheiroTaxasContributivas "/TaxasContributivas.txt"
#define BASEDADOSNAME                  "/dados.bin"

#define SEMDADOGUAR                    "Sem dados para importar."
#define GUARDADOS_SUCESSO              "Dados guardados com sucesso"
#define IMPORTADOS_SUCESSO             "Dados importados com sucesso."

#define maxPasta                       20
#define maxFILENAME                    37
#define maxComando                     39

typedef struct {
    char nome[20];
} NomeEmpresa;

typedef struct {
    NomeEmpresa *nomesEmpresas;
    int numeroEmpresas;
    int numeroMaxEmpresas;
} NomesEmpresas;

void importarNomesEmpresas(NomesEmpresas *nomesEmpresas, char *ficheiro);
void inserirNomeEmpresaFX(NomesEmpresas *nomesEmpresas, char *ficheiro);
void inserirNomeEmpresa(NomesEmpresas *nomesEmpresas, char *nome);
int guardar(Empresa *empresa, IRSDados *irsdados, NomesEmpresas *nomesEmpresas, TaxasContributivas *taxasContributivas);
void importar(Empresa *empresa, IRSDados *irsdados, NomesEmpresas *nomesEmpresas, TaxasContributivas *taxasContributivas);
void limparDados(Empresa *empresa, IRSDados *irsdados, NomesEmpresas *nomesEmpresas, TaxasContributivas *taxasContributivas, int limparNomesEmpresas);
void exportarRelatorio(Empresa *empresa, IRSDados *irsdados, NomesEmpresas *nomesEmpresas, TaxasContributivas *taxasContributivas);
void importarRelatorio(Empresa *empresa, NomesEmpresas *nomesEmpresas);

#endif /* DADOS_H */

