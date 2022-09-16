#include <stdio.h>
#include <stdlib.h>
#include "funcionario.h"
#include "input.h"
#include "funcoes.h"
#include "dados.h"

#define BonusBaseAntiguidade   0.01
#define BonusBaseIdade         0.05
#define BonusBaseNaoFaltar     0.05

const char meses[12][10] = {"Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};

/**
 * Função utilizada para ordenar os anos de trabalho de um funcionário.
 * @param anos - apontador onde se encontram guardados os anos que um funcionário trabalhou.
 * @param inicio - valor correspondente à primeira posição do apontador.
 * @param fim - valor correspondente à primeira posição do apontador.
 */
void ordenarPorAnoTrabalho(Ano *anos, int inicio, int fim) {
    int i, j, pivot;
    Ano temp;

    if (inicio < fim) {
        pivot = inicio;
        i = inicio;
        j = fim;

        while (i < j) {
            while (anos[i].ano <= anos[pivot].ano && i < fim)
                i++;
            while (anos[j].ano > anos[pivot].ano)
                j--;
            if (i < j) {
                temp = anos[i];
                anos[i] = anos[j];
                anos[j] = temp;
            }
        }

        temp = anos[pivot];
        anos[pivot] = anos[j];
        anos[j] = temp;
        ordenarPorAnoTrabalho(anos, inicio, j - 1);
        ordenarPorAnoTrabalho(anos, j + 1, fim);

    }
}

/**
 * Função utilizada para ordenar os meses de trabalho de um funcionário.
 * @param meses - apontador onde se encontram guardados os meses que um funcionário trabalhou.
 * @param inicio - valor correspondente à primeira posição do apontador.
 * @param fim - valor correspondente à primeira posição do apontador.
 */
void ordenarPorMesTrabalho(Mes *meses, int inicio, int fim) {
    int i, j, pivot;
    Mes temp;

    if (inicio < fim) {
        pivot = inicio;
        i = inicio;
        j = fim;

        while (i < j) {
            while (meses[i].Mes <= meses[pivot].Mes && i < fim)
                i++;
            while (meses[j].Mes > meses[pivot].Mes)
                j--;
            if (i < j) {
                temp = meses[i];
                meses[i] = meses[j];
                meses[j] = temp;
            }
        }

        temp = meses[pivot];
        meses[pivot] = meses[j];
        meses[j] = temp;
        ordenarPorMesTrabalho(meses, inicio, j - 1);
        ordenarPorMesTrabalho(meses, j + 1, fim);

    }
}

/**
 * Função utilizada para procurar se um funcionário trabalhou num determinado ano.
 * @param funcionario - apontador onde se encontra armazenadoguardado o funcionário.
 * @param ano - valor correspondente ao ano a ser procurado.
 * @param inicio - valor correspondente à primeira posição do apontador.
 * @param fim - valor correspondente à última posição do apontador.
 * @return indice do ano (caso seja encontrado), -1 (caso não seja encontrado).
 */
int procurarAnoTrabalho(Funcionario *funcionario, int ano, int inicio, int fim) {
    if (fim >= inicio) {
        int meio = inicio + ((fim - inicio) / 2);

        if (funcionario->trabalho.anos[meio].ano == ano) {
            return meio;
        }

        return (funcionario->trabalho.anos[meio].ano > ano) ?
                procurarAnoTrabalho(funcionario, ano, inicio, meio - 1) :
                procurarAnoTrabalho(funcionario, ano, meio + 1, fim);
    }

    return -1;
}

/**
 * Função utilizada para procurar se um ano contém um determinado mês.
 * @param ano - apontador onde se encontram guardados os anos que um funcionário trabalhou.
 * @param mes - valor correspondente ao mês a ser procurado.
 * @return indice do mês (caso seja encontrado), -1 (caso não seja encontrado).
 */
int procurarMesTrabalho(Ano *ano, int mes, int inicio, int fim) {
    if (fim >= inicio) {
        int meio = inicio + ((fim - inicio) / 2);

        if (ano->meses[meio].Mes == mes) {
            return meio;
        }

        return (ano->meses[meio].Mes > mes) ?
                procurarMesTrabalho(ano, mes, inicio, meio - 1) :
                procurarMesTrabalho(ano, mes, meio + 1, fim);
    }

    return -1;
}

/**
 * Função que verifica se existem dados de um mês de um ano específico
 * @param empresa - apontador onde se encontam guardados os funcionários.
 * @param ano - Inteiro como o ano.
 * @param mes - Inteiro como o mês.
 * @return 0 (Se não existir), 1 (Se existir)
 */
int verificaAnoMes(Empresa *empresa, int ano, int mes) {
    int idAno;
    for (int i = 0; i < empresa->nFuncionarios; i++) {
        idAno=procurarAnoTrabalho(&empresa->funcionarios[i], ano, 0, empresa->funcionarios[i].trabalho.numeroAnos-1);
        if (idAno!=-1) {
            if(procurarMesTrabalho(&empresa->funcionarios[i].trabalho.anos[idAno], mes, 0, 
                    empresa->funcionarios[i].trabalho.anos[idAno].numeroMeses-1)!=-1){
                return 1;
            }
        }
    }
    return 0;
}

/**
 * Esta função retorna o valor o mes - 1 que ainda falta inserir os seus dados
 * @param funcionario - apontador com os dados de um funcionario
 * @param idAno - inteiro como o id do ano
 * @return número do mês que ainda falta inserir
 */
int getMesAtualAtualizar(Funcionario *funcionario, int idAno){
    int mesAtual = 0;
    if (funcionario->dataEntradaEmpresa.ano == funcionario->trabalho.anos[idAno].ano) {
        mesAtual = funcionario->dataEntradaEmpresa.mes - 1;
    }
    for(int i=0; i<funcionario->trabalho.anos[idAno].numeroMeses-1; i++){
        if(funcionario->trabalho.anos[idAno].meses[i].Mes > i){
            return mesAtual;
        }
        mesAtual++;
    }
    return mesAtual;
}

/**
 * Função utilizada para inserir os dados relativos ao número de dias que um funcionário trabalhou num determinado ano e, após obter os dados,
 * calcular o salário de cada mês.
 * @param funcionario - apontador onde serão guardados os dados relativos ao processamento do salário do funcionário.
 * @param irsdados - apontador onde se encontram guardados os dados relativos ao IRS.
 * @param taxasContributivas - apontador onde se encontram guardados os dados relativos às taxas contributivas.
 * @param nMeses - valor correspondente ao número de meses a serem processados.
 * @param idAno - valor correspondente ao índice do ano a ser processado.
 */
void inserirTrabalhoDados(Funcionario *funcionario, IRSDados *irsdados, TaxasContributivas *taxasContributivas, int nMeses, int idAno) {

    int mesAtual = getMesAtualAtualizar(funcionario, idAno);

    int maxFor = funcionario->trabalho.anos[idAno].numeroMeses + nMeses;

    for (int i = funcionario->trabalho.anos[idAno].numeroMeses; i < maxFor; i++) {
        printf("---------------------------------------------------------------------");
        printf("\nMes %s:\n", meses[mesAtual]);
        int finsdesemana = getDiasFinsSemana(mesAtual + 1, funcionario->trabalho.anos[idAno].ano);
        funcionario->trabalho.anos[idAno].meses[i].Mes = mesAtual;
        funcionario->trabalho.anos[idAno].meses[i].nMaxDias = obterInteiro(0,
                (getNumeroDiasMes(mesAtual + 1, funcionario->trabalho.anos[idAno].ano) - finsdesemana / 2), MSG_NUM_DIAS_DEVIA_TRAB);

        if (funcionario->trabalho.anos[idAno].meses[i].nMaxDias != 0) {
            funcionario->trabalho.anos[idAno].meses[i].nDiasTrabalhados = obterInteiro(0,
                    funcionario->trabalho.anos[idAno].meses[i].nMaxDias, MSG_NUM_DIAS_TRAB);
            if (funcionario->trabalho.anos[idAno].meses[i].nDiasTrabalhados != 0) {
                funcionario->trabalho.anos[idAno].meses[i].nFaltas =
                        funcionario->trabalho.anos[idAno].meses[i].nMaxDias - funcionario->trabalho.anos[idAno].meses[i].nDiasTrabalhados;

                funcionario->trabalho.anos[idAno].meses[i].nDiasCompletos = obterInteiro(0,
                        funcionario->trabalho.anos[idAno].meses[i].nDiasTrabalhados, MSG_NUM_DIAS_COMPLETOS);

                funcionario->trabalho.anos[idAno].meses[i].nMeiosDias =
                        funcionario->trabalho.anos[idAno].meses[i].nDiasTrabalhados - funcionario->trabalho.anos[idAno].meses[i].nDiasCompletos;

                if (finsdesemana <= funcionario->trabalho.anos[idAno].meses[i].nDiasTrabalhados) {
                    funcionario->trabalho.anos[idAno].meses[i].nDiasFimSemana = obterInteiro(0, finsdesemana, MSG_NUM_DIAS_FIM_SEMANA);
                } else if (funcionario->trabalho.anos[idAno].meses[i].nDiasTrabalhados != 0) {
                    funcionario->trabalho.anos[idAno].meses[i].nDiasFimSemana =
                            obterInteiro(0, funcionario->trabalho.anos[idAno].meses[i].nDiasTrabalhados, MSG_NUM_DIAS_FIM_SEMANA);
                } else {
                    funcionario->trabalho.anos[idAno].meses[i].nDiasFimSemana = 0;
                }
            } else {
                funcionario->trabalho.anos[idAno].meses[i].nFaltas = funcionario->trabalho.anos[idAno].meses[i].nMaxDias;
                funcionario->trabalho.anos[idAno].meses[i].nDiasCompletos = 0;
                funcionario->trabalho.anos[idAno].meses[i].nMeiosDias = 0;
                funcionario->trabalho.anos[idAno].meses[i].nDiasFimSemana = 0;
            }
        } else {
            funcionario->trabalho.anos[idAno].meses[i].nDiasTrabalhados = 0;
            funcionario->trabalho.anos[idAno].meses[i].nFaltas = 0;
            funcionario->trabalho.anos[idAno].meses[i].nDiasCompletos = 0;
            funcionario->trabalho.anos[idAno].meses[i].nMeiosDias = 0;
            funcionario->trabalho.anos[idAno].meses[i].nDiasFimSemana = 0;
        }

        funcionario->trabalho.anos[idAno].meses[i].salarioBase = funcionario->valorHora *
                (funcionario->trabalho.anos[idAno].meses[i].nMeiosDias * 4 +
                (funcionario->trabalho.anos[idAno].meses[i].nDiasCompletos - funcionario->trabalho.anos[idAno].meses[i].nDiasFimSemana) * 8 +
                funcionario->trabalho.anos[idAno].meses[i].nDiasFimSemana * 16);

        funcionario->trabalho.anos[idAno].meses[i].almoco =
                funcionario->trabalho.anos[idAno].meses[i].nDiasCompletos * funcionario->valorSubsidioAlimentacao;

        funcionario->trabalho.anos[idAno].meses[i].bonus =
                BonusBaseAntiguidade * (funcionario->trabalho.anos[idAno].ano - funcionario->dataEntradaEmpresa.ano);

        if (funcionario->trabalho.anos[idAno].meses[i].nFaltas == 0) {
            funcionario->trabalho.anos[idAno].meses[i].bonus =
                    funcionario->trabalho.anos[idAno].meses[i].bonus + BonusBaseNaoFaltar;
        }

        int idade = idadeFimMes(funcionario->dataNascimento.mes, funcionario->dataNascimento.ano, mesAtual + 1, funcionario->trabalho.anos[idAno].ano);
        int anosTrabalho = idadeFimMes(funcionario->dataEntradaEmpresa.mes, funcionario->dataEntradaEmpresa.ano, mesAtual + 1, funcionario->trabalho.anos[idAno].ano);

        if (idade >= 50 && anosTrabalho <= 21) {
            funcionario->trabalho.anos[idAno].meses[i].bonus =
                    funcionario->trabalho.anos[idAno].meses[i].bonus + BonusBaseIdade;
        }

        funcionario->trabalho.anos[idAno].meses[i].bonus =
                funcionario->trabalho.anos[idAno].meses[i].salarioBase * funcionario->trabalho.anos[idAno].meses[i].bonus;

        funcionario->trabalho.anos[idAno].meses[i].irs = funcionario->trabalho.anos[idAno].meses[i].salarioBase *
                getIrs(irsdados, funcionario->trabalho.anos[idAno].meses[i].salarioBase, funcionario->numeroFilhosDependentes, funcionario->estadoCivil);

        int idTaxasContributivas = getTaxaContributiva(taxasContributivas, funcionario, idade, anosTrabalho);

        funcionario->trabalho.anos[idAno].meses[i].segurancaSocial =
                funcionario->trabalho.anos[idAno].meses[i].salarioBase * taxasContributivas->taxasContributivas[idTaxasContributivas].Trabalhador;

        funcionario->trabalho.anos[idAno].meses[i].segurancaSocialPatronal =
                funcionario->trabalho.anos[idAno].meses[i].salarioBase * taxasContributivas->taxasContributivas[idTaxasContributivas].EntidadeEmpregadora;

        funcionario->trabalho.anos[idAno].meses[i].salarioFinal =
                funcionario->trabalho.anos[idAno].meses[i].bonus + funcionario->trabalho.anos[idAno].meses[i].salarioBase + funcionario->trabalho.anos[idAno].meses[i].almoco
                - funcionario->trabalho.anos[idAno].meses[i].segurancaSocial - funcionario->trabalho.anos[idAno].meses[i].irs;

        mesAtual++;
        funcionario->trabalho.anos[idAno].numeroMeses++;
    }
    
    ordenarPorMesTrabalho(funcionario->trabalho.anos[idAno].meses, 0, funcionario->trabalho.anos[idAno].numeroMeses-1);
}

/**
 * Função utilizada para alocar espaço para os meses trabalhados por um funcionário e chamar a função "inserirTrabalhoDados".
 * @param funcionario - apontador onde se encontram os dados do funcionário.
 * @param irsdados - apontador onde se encontram guardados os dados relativos ao IRS.
 * @param taxasContributivas - apontador onde se encontram guardados os dados relativos às taxas contributivas.
 * @param maxMes - valor correspondente ao número máximo de meses que podem ser processados.
 * @param idAno - valor correspondente ao índice do ano a ser processado.
 */
void inserirTrabalhoMes(Funcionario *funcionario, IRSDados *irsdados, TaxasContributivas *taxasContributivas, int maxMes, int idAno) {
    if (maxMes > 0) {
        int nMeses = obterInteiro(1, maxMes, MSG_OBTER_MESES_INSERIR);
        if ((funcionario->trabalho.anos[idAno].numeroMeses + nMeses) >= funcionario->trabalho.anos[idAno].tamMeses) {
            Mes *novo = (Mes*) realloc(funcionario->trabalho.anos[idAno].meses, sizeof (Mes) *
                    (funcionario->trabalho.anos[idAno].tamMeses + nMeses));
            if (novo != NULL) {
                funcionario->trabalho.anos[idAno].meses = novo;
                funcionario->trabalho.anos[idAno].tamMeses += nMeses;
                inserirTrabalhoDados(funcionario, irsdados, taxasContributivas, nMeses, idAno);
            }else{
                puts("Erro ao alocar mais memória nos meses.");
            }
        } else {
            inserirTrabalhoDados(funcionario, irsdados, taxasContributivas, nMeses, idAno);
        }
    } else {
        printf(MSG_DADOS_ANO_PREENCHIDOS);
    }
}

/**
 * Função utilizada adicionar um ano em que um funcionário trabalhou.
 * @param funcionario - apontador onde se encontram os dados do funcionário.
 * @param idAno - valor correspondente ao índice do ano a ser processado.
 * @param ano - valor correspondente ao ano a ser processado.
 */
void adicionarAno(Funcionario *funcionario, int *idAno, int ano) {
    funcionario->trabalho.anos[funcionario->trabalho.numeroAnos].ano = ano;
    funcionario->trabalho.anos[funcionario->trabalho.numeroAnos].meses = NULL;
    funcionario->trabalho.anos[funcionario->trabalho.numeroAnos].numeroMeses = 0;
    funcionario->trabalho.anos[funcionario->trabalho.numeroAnos].tamMeses = 0;

    funcionario->trabalho.numeroAnos++;
    ordenarPorAnoTrabalho(funcionario->trabalho.anos, 0, funcionario->trabalho.numeroAnos - 1);
    *idAno = procurarAnoTrabalho(funcionario, ano, 0, funcionario->trabalho.numeroAnos - 1);
}

/**
 * Função utilizada para alocar espaço para os anos trabalhados por um funcionário e chamar a função "inserirTrabalhoMes".
 * @param funcionario - apontador onde se encontram os dados do funcionário.
 * @param irsdados - apontador onde se encontram guardados os dados relativos ao IRS.
 * @param taxasContributivas - apontador onde se encontram guardados os dados relativos às taxas contributivas.
 */
void inserirTrabalhoAno(Funcionario *funcionario, IRSDados *irsdados, TaxasContributivas *taxasContributivas) {
    int ano = obterInteiro(funcionario->dataEntradaEmpresa.ano, getAnoAtual(), MSG_ALTERAR_DADOS_ANO);
    int idAno = procurarAnoTrabalho(funcionario, ano, 0, funcionario->trabalho.numeroAnos - 1);
    int maxMes;
    if (idAno == -1) {
        if (funcionario->dataEntradaEmpresa.ano == ano) {
            maxMes = 13 - funcionario->dataEntradaEmpresa.mes;
        } else {
            maxMes = 12;
        }
        if (funcionario->trabalho.numeroAnos == funcionario->trabalho.tamAnos) {
            Ano *novo = (Ano*) realloc(funcionario->trabalho.anos, sizeof (Ano) * (funcionario->trabalho.tamAnos + INC));
            if (novo != NULL) {
                funcionario->trabalho.tamAnos += INC;
                funcionario->trabalho.anos = novo;

                adicionarAno(funcionario, &idAno, ano);
                inserirTrabalhoMes(funcionario, irsdados, taxasContributivas, maxMes, idAno);
            } else {
                puts("Erro ao alocar mais memória no Ano.");
            }
        } else {
            adicionarAno(funcionario, &idAno, ano);
            inserirTrabalhoMes(funcionario, irsdados, taxasContributivas, maxMes, idAno);
        }
    } else {
        if (funcionario->dataEntradaEmpresa.ano == ano) {
            maxMes = 13 - funcionario->trabalho.anos[idAno].numeroMeses - funcionario->dataEntradaEmpresa.mes;
        } else {
            maxMes = 12 - funcionario->trabalho.anos[idAno].numeroMeses;
        }
        inserirTrabalhoMes(funcionario, irsdados, taxasContributivas, maxMes, idAno);
    }
}

/**
 * Função utilizada para verificar se um funcionário existe e caso exista, chamar a função "inserirTrabalhoAno".
 * @param empresa - apontador onde se encontam guardados os funcionários.
 * @param irsdados - apontador onde se encontram guardados os dados relativos ao IRS.
 * @param taxasContributivas - apontador onde se encontram guardados os dados relativos às taxas contributivas.
 */
void inserirTrabalho(Empresa *empresa, IRSDados *irsdados, TaxasContributivas *taxasContributivas) {
    int id = procurarFuncionarios(empresa, obterInteiro(MIN_COD_FUNCIONARIO, MAX_COD_FUNCIONARIO, MSG_OBTER_COD_FUNCIONARIO), 0, empresa->nFuncionarios - 1);
    if (id == -1) {
        puts(ERRO_FUNCIONARIO_NAO_EXISTE);
    } else if (id == -2) {
        puts(ERRO_FUNCIONARIO_ELIMINADO);
    } else {
        inserirTrabalhoAno(&empresa->funcionarios[id], irsdados, taxasContributivas);
    }
}

/**
 * Função utilizada para listar os dados guardados correspondentes ao processamento do salário de um mês.
 * @param mes - apontador onde se encontram os dados do mês.
 */
void listaTrabalhoMes(Mes *mes) {
    printf("\nMes de %s: ", meses[mes->Mes]);
    printf("\nSalario Base: %.2f", mes->salarioBase);
    printf("\nSalario Final: %.2f", mes->salarioFinal);
    printf("\nBonus: %.2f", mes->bonus);
    printf("\nNumero de trabalho: %d", mes->nDiasTrabalhados);
    printf("\nNumero de faltas: %d", mes->nFaltas);
    printf("\nIRS: %.2f", mes->irs);
    printf("\nTaxa Contributiva Funcionaria: %.2f", mes->segurancaSocial);
    printf("\nTaxa Contributiva Patronal: %.2f", mes->segurancaSocialPatronal);
}

/**
 * Função utilizada para verificar se um funcionário trabalhou num determinado ano e caso tenha trabalhado, chamar a função "listaTrabalhoMes".
 * @param funcionario - apontador onde se encontam guardados os dados do funcionário.
 */
void listarTrabalhoAno(Funcionario *funcionario) {
    int ano = obterInteiro(funcionario->dataEntradaEmpresa.ano, getAnoAtual(), MSG_INSIRA_ANO);
    ano = procurarAnoTrabalho(funcionario, ano, 0, funcionario->trabalho.numeroAnos - 1);
    if (ano != -1) {
        for (int i = 0; i < funcionario->trabalho.anos[ano].numeroMeses; i++) {
            listaTrabalhoMes(&funcionario->trabalho.anos[ano].meses[i]);
            printf("\n-------------------------------------------------------------");
        }
    } else {
        printf(MSG_SEM_DADOS);
    }
}

/**
 * Função utilizada para verificar se um funcionário existe e caso exista, chamar a função "listarTrabalhoAno".
 * @param empresa - apontador onde se encontam guardados os funcionários.
 */
void listarTrabalho(Empresa *empresa) {
    int id = procurarFuncionarios(empresa, obterInteiro(MIN_COD_FUNCIONARIO, MAX_COD_FUNCIONARIO, MSG_OBTER_COD_FUNCIONARIO), 0, empresa->nFuncionarios - 1);
    if (id == -1) {
        puts(ERRO_FUNCIONARIO_NAO_EXISTE);
    } else {
        listarTrabalhoAno(&empresa->funcionarios[id]);
    }
}

/**
 * Função que verifica se existe salarios inseridos
 * @param empresa - apontador onde se encontam guardados os funcionários.
 * @return 0 (se não existir), 1 (se existir)
 */
int verificaExisteAno(Empresa *empresa){
    int c;
    for (int i = 0; i < empresa->nFuncionarios; i++) {
        if (empresa->funcionarios[i].trabalho.numeroAnos!=0) {
            c++;
        }
    }
    if(c==0){
        return 0;
    }else{
        return 1;
    }
}

/**
 * Função utilizada para listar os gastos que a empresa teve num ano.
 * @param empresa - apontador onde se encontam guardados os funcionários.
 * @return valor correspondente aos gastos que a empresa teve num ano.
 */
int listarGastosAno(Empresa *empresa) {
    if(verificaExisteAno(empresa)>0){
        int ano, idAno, minAno = getAnoAtual();
        float total = 0;
        for (int i = 0; i < empresa->nFuncionarios; i++) {
            if (minAno > empresa->funcionarios[i].dataEntradaEmpresa.ano) {
                minAno = empresa->funcionarios[i].dataEntradaEmpresa.ano;
            }
        }
        ano = obterInteiro(minAno, getAnoAtual(), MSG_INSIRA_ANO);

        for (int i = 0; i < empresa->nFuncionarios; i++) {
            idAno = procurarAnoTrabalho(&empresa->funcionarios[i], ano, 0, empresa->funcionarios[i].trabalho.numeroAnos - 1);
            if (idAno != -1) {
                for (int j = 0; j < empresa->funcionarios[i].trabalho.anos[idAno].numeroMeses; j++) {
                    total += (empresa->funcionarios[i].trabalho.anos[idAno].meses[j].salarioBase +
                            empresa->funcionarios[i].trabalho.anos[idAno].meses[j].bonus +
                            empresa->funcionarios[i].trabalho.anos[idAno].meses[j].segurancaSocialPatronal +
                            empresa->funcionarios[i].trabalho.anos[idAno].meses[j].almoco);
                }
            }
        }

        if (total == 0) {
            printf(MSG_SEM_GASTOS_ANO, ano);
        } else {
            printf(MSG_GASTOS_ANO, ano, total);
        }
    }else{
        puts("Sem dados de salarios");
    }
}

/**
 * Função utilizada para listar os gastos que a empresa teve num mês.
 * @param empresa - apontador onde se encontam guardados os funcionários.
 * @return valor correspondente aos gastos que a empresa teve num mês.
 */
int listarGastosMes(Empresa *empresa) {
    if(verificaExisteAno(empresa)>0){
        int ano, mes, idAno, idMes, minAno = getAnoAtual();
        float total = 0;
        for (int i = 0; i < empresa->nFuncionarios; i++) {
            if (minAno > empresa->funcionarios[i].dataEntradaEmpresa.ano) {
                minAno = empresa->funcionarios[i].dataEntradaEmpresa.ano;
            }
        }
        ano = obterInteiro(minAno, getAnoAtual(), MSG_INSIRA_ANO);
        mes = obterInteiro(1, 12, MSG_INSIRA_MES);

        for (int i = 0; i < empresa->nFuncionarios; i++) {
            idAno = procurarAnoTrabalho(&empresa->funcionarios[i], ano, 0, empresa->funcionarios[i].trabalho.numeroAnos - 1);
            if (idAno != -1) {
                idMes = procurarMesTrabalho(&empresa->funcionarios[i].trabalho.anos[idAno], mes, 0, empresa->funcionarios[i].trabalho.anos[idAno].numeroMeses - 1);
                if (idMes != -1) {
                    total += (empresa->funcionarios[i].trabalho.anos[idAno].meses[idMes].salarioBase +
                            empresa->funcionarios[i].trabalho.anos[idAno].meses[idMes].bonus +
                            empresa->funcionarios[i].trabalho.anos[idAno].meses[idMes].segurancaSocialPatronal +
                            empresa->funcionarios[i].trabalho.anos[idAno].meses[idMes].almoco);
                }
            }
        }

        if (total == 0) {
            printf(MSG_SEM_GASTOS_MES, mes, ano);
        } else {
            printf(MSG_GASTOS_MES, mes, ano, total);
        }
    }else{
        puts("Sem dados de salarios");
    }
}

/**
 * Função utilizada para listar os funcionários que ganham igual ou mais do que determinado valor por hora.
 * @param empresa - apontador onde se encontam guardados os funcionários.
 */
void listarFuncValorHora(Empresa *empresa) {
    int valor, nValor = 0;
    for (int i = 0; i < empresa->nFuncionarios; i++) {
        if (empresa->funcionarios[i].valorHora != valor) {
            nValor++;
        }
    }
    if (nValor > 0) {
        valor = obterInteiro(MIN_VALOR_HORA, MAX_VALOR_HORA, MSG_OBTER_VALOR_HORA);
        for (int i = 0; i < empresa->nFuncionarios; i++) {
            if (empresa->funcionarios[i].valorHora >= valor) {
                printf("\nFuncionário (código - nome): %d - %s ", empresa->funcionarios[i].codigoFuncionario, empresa->funcionarios[i].nome);
            }
        }
    } else {
        puts(MSG_SEM_DADOS);
    }
}
