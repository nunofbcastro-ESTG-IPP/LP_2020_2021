#ifndef IRC_H
#define IRC_H

#define INC 5

#define FicheiroCasadoUnico           "./src/CasadosDois.txt"
#define FicheiroCasadoDois            "./src/CasadoUnico.txt"
#define FicheiroNaoCasado             "./src/NaoCasado.txt"

#define ERRO_PESQUISA_SALARIO         "Salário não encontrado."
#define MSG_OBTER_REMUNERACAO         "Insira o valor da renumeração mensal: "
#define MSG_OBTER_REMUNERACAO_ALT     "Insira o valor limite da renumeração mensal que quer alterar: "
#define MIN_REMUNERACAO               0
#define MSG_OBTER_PERCENTAGEM         "Insira o valor percentual do IRS correspondente ao número de filhos [%.2f - %.2f]: "

typedef struct {
    float salario;
    float percentagem[6];
} IRS;

typedef struct {
    IRS *casadoUnicoIRS;
    int contadorCasadoUnicoIRS;
    int tamcontadorCasadoUnicoIRS;

    IRS *casadoDoisIRS;
    int contadorCasadoDoisIRS;
    int tamcontadorCasadoDoisIRS;

    IRS *solteiroIRS;
    int contadorSolteiroIRS;
    int tamcontadorSolteiroIRS;
} IRSDados;

void atualizarFicheiroIRS(IRS *irs, int contador, char *nomeFicheiro);
void carregarDadosFicheiroIRS(IRS **irs, int *contador, int *tam, char *nomeFicheiro);
void listarIRS(IRS *irs, int contador, char* mensagem);
void adicionarTabelaIRS(IRS **irs, int *contador, int *tam);
void alterarTabelaIRS(IRS **irs, int *contador);
void eliminarTabelaIRS(IRS **irs, int *contador);
float getIrs(IRSDados *irsdados,float salario, int nFilhos, int estadoCivil);

#endif /* IRC_H */

