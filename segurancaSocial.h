#ifndef SEGURANCASOCIAL_H
#define SEGURANCASOCIAL_H

#define INC                                5
#define MSG_OBTER_INFORMACAO               "Mensagem de Informação da Taxa:"
#define MSG_OBTER_P_ENTIDADE_EMPREGADORA   "Percentagem Entidade Empregadora:"
#define MSG_OBTER_P_TRABALHADOR            "Percentagem Trabalhador:"
#define MSG_ALTERAR_TAXA                   "Selecione a taxa que pretende atualizar:"


#define ficheiroTaxasContributiva "./src/TaxasContributivas.txt"

typedef struct {
    char texto[80];
    float EntidadeEmpregadora;
    float Trabalhador;
    float Global;
    
    int cargo;
    int sinal;
    int idade;
    int anosEmpresa;
} TaxaContributiva;

typedef struct {
    TaxaContributiva *taxasContributivas;
    int maxTaxasContributivas;
    int numeroTaxasContributivas;
} TaxasContributivas;

void carregarDadosFicheiroTaxasContributivas(TaxasContributivas *taxasContributivas, char *nomeFicheiro);
void guardarDadosFicheiroTaxasContributivas(TaxasContributivas *taxasContributivas, char *nomeFicheiro);
void listarTaxasContributivas(TaxasContributivas *taxasContributivas);
void adicionarTaxaContributiva(TaxasContributivas *taxasContributivas);
void atualizarTaxaContributiva(TaxasContributivas *taxasContributivas);
void listaTaxaContributiva(TaxaContributiva *taxaContributiva);

#endif /* SEGURANCASOCIAL_H */