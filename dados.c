
#include <stdio.h>
#include <stdlib.h>
#include "dados.h"
#include "funcionario.h"
#include "funcoes.h"
#include "input.h"
#include "irs.h"
#include "segurancaSocial.h"
#include "dados.h"

/**
 * Função utilizada para importar os nomes das empresas de um ficheiro.
 * @param nomesEmpresas - apontador onde serão armazenados os nomes das empresas.
 * @param ficheiro - nome do ficheiro que contém os nomes de todas as empresas.
 */
void importarNomesEmpresas(NomesEmpresas *nomesEmpresas, char *ficheiro) {
    FILE *fp = fopen(ficheiro, "rb");
    if (fp != NULL) {
        fread(&nomesEmpresas->numeroEmpresas, sizeof (int), 1, fp);
        if (nomesEmpresas->numeroEmpresas > 0) {
            nomesEmpresas->nomesEmpresas = (NomeEmpresa*) calloc(nomesEmpresas->numeroEmpresas + 5, sizeof (NomeEmpresa));
            if (nomesEmpresas->nomesEmpresas != NULL) {
                nomesEmpresas->numeroMaxEmpresas = nomesEmpresas->numeroEmpresas + 5;
                for (int i = 0; i < nomesEmpresas->numeroEmpresas; i++) {
                    fread(&nomesEmpresas->nomesEmpresas[i], sizeof (NomeEmpresa), 1, fp);
                }
            } else {
                puts("Erro ao alocar mais memória nos Nomes de Empresa.");
                nomesEmpresas->numeroEmpresas = 0;
            }
        }
    } else {
        fp = fopen(ficheiro, "wb");
    }
    fclose(fp);
}

/**
 * Função utilizada para atualizar o contador do ficheiro que contém os nomes de todas as empresas.
 * @param contador - valor correspondente ao contador que vai ser atualizado no ficheiro.
 * @param ficheiro - nome do ficheiro que contém os nomes de todas as empresas.
 */
void atualizarContadorNomesEmpresas(int contador, char *ficheiro) {
    FILE *fp = fopen(ficheiro, "r+b");
    if (fp == NULL) {
        puts("Erro ao abrir ficheiro");
    }else{
        fwrite(&contador, sizeof (int), 1, fp);
    }
    fclose(fp);
}

/**
 * Função utilizada para exportar o nome de todas as empresas para o ficheiro indicado.
 * @param nomesEmpresas - apontador onde se encontram armazenados os nomes das empresas.
 * @param ficheiro - nome do ficheiro onde serão exportados os nomes de todas as empresas.
 */
void inserirNomeEmpresaFX(NomesEmpresas *nomesEmpresas, char *ficheiro) {
    atualizarContadorNomesEmpresas(nomesEmpresas->numeroEmpresas, ficheiro);

    FILE *fp = fopen(ficheiro, "ab");
    if (fp == NULL) {
        puts("Erro ao abrir ficheiro");
    }else{
        fwrite(&nomesEmpresas->nomesEmpresas[nomesEmpresas->numeroEmpresas - 1], sizeof (NomeEmpresa), 1, fp);
    }
    fclose(fp);
}

/**
 * Função utilizada para adicionar ao apontador o nome de uma empresa.
 * @param nomesEmpresas - apontador onde será armazenado o nome da empresa.
 * @param nome - nome da empresa a ser adicionada.
 */
void adiconarNomeEmpresa(NomesEmpresas *nomesEmpresas, char *nome) {
    int i;
    for (i = 0; nome[i] != '\0'; i++) {
        nomesEmpresas->nomesEmpresas[nomesEmpresas->numeroEmpresas].nome[i] = nome[i];
    }
    nomesEmpresas->nomesEmpresas[nomesEmpresas->numeroEmpresas].nome[i + 1] = '\0';
    nomesEmpresas->numeroEmpresas++;
}

/**
 * Função utilizada para, caso necessário, alocar espaço  para os nomes das empresas e chamar a função "adicionarNomeEmpresa".
 * @param nomesEmpresas - apontador onde será armazenado o nome da empresa.
 * @param nome - nome da empresa a ser adicionada.
 */
void inserirNomeEmpresa(NomesEmpresas *nomesEmpresas, char *nome) {
    if (nomesEmpresas->numeroMaxEmpresas == nomesEmpresas->numeroEmpresas) {
        NomeEmpresa *novo = (NomeEmpresa*) realloc(nomesEmpresas->nomesEmpresas, sizeof (NomeEmpresa) * (nomesEmpresas->numeroMaxEmpresas + INC));
        if (novo != NULL) {
            nomesEmpresas->numeroMaxEmpresas += INC;
            nomesEmpresas->nomesEmpresas = novo;
            adiconarNomeEmpresa(nomesEmpresas, nome);
        }else{
            puts("Erro a alocar mais memória nos Nomes Empresas.");
        }
    } else {
        adiconarNomeEmpresa(nomesEmpresas, nome);
    }
}

/**
 * Função utilizada para pesquisar o nome de uma empresa.
 * @param nomesEmpresas - apontador onde se encontram armazenados os nomes das empresas.
 * @param nome - nome da empresa a ser pesquisado.
 * @return indice do nome da empresa (caso seja encontrado) ou -1 (caso não seja encontrado).
 */
int pesquisaNomeEmpresa(NomesEmpresas *nomesEmpresas, char *nome) {
    for (int i = 0; i < nomesEmpresas->numeroEmpresas; i++) {
        if (verificaString(nome, nomesEmpresas->nomesEmpresas[i].nome) == 1) {
            return i;
        }
    }
    return -1;
}

/**
 * Função utilizada para guardar todos os dados de uma empresa em ficheiros (dados dos funcionarios, IRS, segurança social).
 * @param empresa - apontador onde se encontram armazenados os dados de todos os funcionários.
 * @param irsdados - apontador onde se encontram armazenados os dados do IRS.
 * @param nomesEmpresas - apontador onde se encontram armazenados os nomes das empresas.
 */
int guardar(Empresa *empresa, IRSDados *irsdados, NomesEmpresas *nomesEmpresas, TaxasContributivas *taxasContributivas) {
    printf("Guardar:\n");
    char pasta[maxPasta];
    char comando[maxComando] = "cd src && mkdir ";
    char name[90];
    lerString(pasta, 20, "Nome do ficheiro:");
    int posicao = pesquisaNomeEmpresa(nomesEmpresas, pasta);
    if (posicao == -1) {
        juntar4Strings(comando, "\"", pasta, "\"");
        if (system(comando) != 0) {
            puts("Erro ao criar pasta da empresa.");
            return 0;
        } else {
            comando[0] = '\0';
            juntar4Strings(comando, "cd src/\"", pasta, "\" && mkdir relatorios");
            if (system(comando) != 0) {
                printf("Erro ao criar pasta relatorio.");
                return 0;
            } else {
                inserirNomeEmpresa(nomesEmpresas, pasta);
                inserirNomeEmpresaFX(nomesEmpresas, ficheiroNomeEmpresas);
            }
        }
    }
    empresa->idEmpresa = posicao;

    //guardar funcionarios em um ficheiro
    juntar4Strings(name, BASEPASTANAME, pasta, BASEDADOSNAME);
    armazenaDados(empresa, name);

    //guardar irs solteiro em um ficheiro
    name[0] = '\0';
    juntar4Strings(name, BASEPASTANAME, pasta, BASEFicheiroNaoCasado);
    atualizarFicheiroIRS(irsdados->solteiroIRS, irsdados->contadorSolteiroIRS, name);

    //guardar irs casado unico em um ficheiro
    name[0] = '\0';
    juntar4Strings(name, BASEPASTANAME, pasta, BASEFicheiroCasadoUnico);
    atualizarFicheiroIRS(irsdados->casadoUnicoIRS, irsdados->contadorCasadoUnicoIRS, name);

    //guardar irs casado dois em um ficheiro
    name[0] = '\0';
    juntar4Strings(name, BASEPASTANAME, pasta, BASEFicheiroCasadoDois);
    atualizarFicheiroIRS(irsdados->casadoDoisIRS, irsdados->contadorCasadoDoisIRS, name);

    //guardar taxas contributivas em um ficheiro
    name[0] = '\0';
    juntar4Strings(name, BASEPASTANAME, pasta, BASEFicheiroTaxasContributivas);
    guardarDadosFicheiroTaxasContributivas(taxasContributivas, name);

    return 1;
}

/**
 * Função utilizada para libertar a memória de todo o programa.
 * @param empresa - apontador onde se encontram armazenados os dados de todos os funcionários.
 * @param irsdados - apontador onde se encontram armazenados os dados do IRS.
 * @param nomesEmpresas - apontador onde se encontram armazenados os nomes das empresas.
 * @param taxasContributivas
 * @param limparNomesEmpresas - 1 (caso seja para limpar a memória do apontador "nomesEmpresas") ou 0 (caso não seja para limpar a memória do apontador "nomesEmpresas").
 */
void limparDados(Empresa *empresa, IRSDados *irsdados, NomesEmpresas *nomesEmpresas, TaxasContributivas *taxasContributivas, int limparNomesEmpresas) {
    int i, j;
    for (i = 0; i < empresa->nFuncionarios; i++) {
        for (j = 0; j < empresa->funcionarios[i].trabalho.numeroAnos; j++) {
            free(empresa->funcionarios[i].trabalho.anos[j].meses);
        }
        free(empresa->funcionarios[i].trabalho.anos);
    }
    free(empresa->funcionarios);
    empresa->maxFuncionarios = 0;
    empresa->nFuncionarios = 0;


    free(irsdados->solteiroIRS);
    irsdados->contadorSolteiroIRS = 0;
    irsdados->tamcontadorSolteiroIRS = 0;

    free(irsdados->casadoUnicoIRS);
    irsdados->contadorSolteiroIRS = 0;
    irsdados->tamcontadorCasadoUnicoIRS = 0;

    free(irsdados->casadoDoisIRS);
    irsdados->contadorCasadoDoisIRS = 0;
    irsdados->tamcontadorCasadoDoisIRS = 0;

    free(taxasContributivas->taxasContributivas);
    taxasContributivas->numeroTaxasContributivas = 0;
    taxasContributivas->maxTaxasContributivas = 0;

    if (limparNomesEmpresas == 1) {
        free(nomesEmpresas->nomesEmpresas);
        nomesEmpresas->numeroEmpresas = 0;
        nomesEmpresas->numeroMaxEmpresas = 0;
    }

}

/**
 * Função utilizada para importar todos os dados de uma determinada empresa (dados dos funcionarios, IRS, segurança social).
 * @param empresa - apontador onde serão armazenados os dados dos funcionários.
 * @param irsdados - apontador onde serão armazenados os dados do IRS.
 * @param nomesEmpresas - apontador onde se encontram os nomes das empresas, utilizado para selecionar uma empresa já armazenada.
 */
void importar(Empresa *empresa, IRSDados *irsdados, NomesEmpresas *nomesEmpresas, TaxasContributivas *taxasContributivas) {
    printf("Importar dados:\n");
    if (nomesEmpresas->numeroEmpresas > 0) {
        char pasta[maxPasta];
        char name[90];
        int i;
        for (i = 0; i < nomesEmpresas->numeroEmpresas; i++) {
            printf("%d - %s\n", i + 1, nomesEmpresas->nomesEmpresas[i].nome);
        }
        int posicao = obterInteiro(1, i, "Número da empresa:") - 1;
        empresa->idEmpresa = posicao;
        juntar2Strings(pasta, nomesEmpresas->nomesEmpresas[posicao].nome);

        limparDados(empresa, irsdados, nomesEmpresas, taxasContributivas, 0);

        //importar funcionarios que esta em um ficheiro
        juntar4Strings(name, BASEPASTANAME, pasta, BASEDADOSNAME);
        importaDados(empresa, name);

        //importar irs solteiro que esta em um um ficheiro
        name[0] = '\0';
        juntar4Strings(name, BASEPASTANAME, pasta, BASEFicheiroNaoCasado);
        carregarDadosFicheiroIRS(&irsdados->solteiroIRS, &irsdados->contadorSolteiroIRS, &irsdados->tamcontadorSolteiroIRS, name);

        //importar irs casado unico que esta em um ficheiro
        name[0] = '\0';
        juntar4Strings(name, BASEPASTANAME, pasta, BASEFicheiroCasadoUnico);
        carregarDadosFicheiroIRS(&irsdados->casadoUnicoIRS, &irsdados->contadorCasadoUnicoIRS, &irsdados->tamcontadorCasadoUnicoIRS, name);

        //importar irs casado dois que esta em um ficheiro
        name[0] = '\0';
        juntar4Strings(name, BASEPASTANAME, pasta, BASEFicheiroCasadoDois);
        carregarDadosFicheiroIRS(&irsdados->casadoDoisIRS, &irsdados->contadorCasadoDoisIRS, &irsdados->tamcontadorCasadoDoisIRS, name);

        //guardar taxas contributivas em um ficheiro
        name[0] = '\0';
        juntar4Strings(name, BASEPASTANAME, pasta, BASEFicheiroTaxasContributivas);
        carregarDadosFicheiroTaxasContributivas(taxasContributivas, name);

        puts(IMPORTADOS_SUCESSO);
    } else {
        puts(SEMDADOGUAR);
    }
}

/**
 * Esta função passa os dados de uma variável com os dados de um mês de salário para a memória dinâmica com todos os salários.
 * @param mes - apontador com os dados de um salário da memória dinâmica
 * @param dados - variavel com os dados de um salário
 */
void adicionarSalarioRelatorioFinal(Mes *mes, Mes dados){
    mes->Mes=dados.Mes;
    mes->almoco=dados.almoco;
    mes->bonus=dados.bonus;
    mes->irs=dados.irs;
    mes->nDiasCompletos=dados.nDiasCompletos;
    mes->nDiasFimSemana=dados.nDiasFimSemana;
    mes->nDiasTrabalhados=dados.nDiasTrabalhados;
    mes->nFaltas=dados.nFaltas;
    mes->nMaxDias=dados.nMaxDias;
    mes->nMeiosDias=dados.nMeiosDias;
    mes->salarioBase=dados.salarioBase;
    mes->salarioFinal=dados.salarioFinal;
    mes->segurancaSocial=dados.segurancaSocial;
    mes->segurancaSocialPatronal=dados.segurancaSocialPatronal;
}

/**
 * Esta função se necessário aloca mais memória ao apontador para poder adicionar mais salários, de seguida chama a função "adicionarSalarioRelatorioFinal"
 * @param funcionario - apontador com o funcionário que vai adicionar mais um sálario
 * @param idAno - id do ano que vai adicionar esse salário
 * @param dados - dados do salário
 */
void adicionarSalarioRelatorioMes(Funcionario *funcionario, int idAno, Mes dados){
    if (funcionario->trabalho.anos[idAno].numeroMeses >= funcionario->trabalho.anos[idAno].tamMeses) {
        Mes *novo = (Mes*) realloc(funcionario->trabalho.anos[idAno].meses, sizeof (Mes) *
                (funcionario->trabalho.anos[idAno].tamMeses + 1));
        if (novo != NULL) {
            funcionario->trabalho.anos[idAno].meses = novo;
            funcionario->trabalho.anos[idAno].tamMeses ++;
            int idMes = funcionario->trabalho.anos[idAno].numeroMeses;
            funcionario->trabalho.anos[idAno].numeroMeses ++;
            adicionarSalarioRelatorioFinal(&funcionario->trabalho.anos[idAno].meses[idMes], dados);
            ordenarPorMesTrabalho(funcionario->trabalho.anos[idAno].meses, 0, funcionario->trabalho.anos[idAno].numeroMeses-1);
        }else{
            puts("Erro ao alocar mais memória no apontador meses.");
        }
    }else{
        int idMes = funcionario->trabalho.anos[idAno].numeroMeses;
        funcionario->trabalho.anos[idAno].numeroMeses ++;
        adicionarSalarioRelatorioFinal(&funcionario->trabalho.anos[idAno].meses[idMes], dados);
        ordenarPorMesTrabalho(funcionario->trabalho.anos[idAno].meses, 0, funcionario->trabalho.anos[idAno].numeroMeses-1);
    }
}

/**
 * Esta função se necessário aloca espaços no apontador mês e no ano, e se tiver espaço chama a função "adicionarSalarioRelatorioFinal"
 * @param empresa - apontador com os dados de todos os funcionarios
 * @param codigoFuncionario - Inteiro com o código do funcionario
 * @param ano - Inteiro com o ano
 * @param dados - dados do salário
 */
void adicionarSalarioRelatorio(Empresa *empresa, int codigoFuncionario, int ano, Mes dados){
    int codigo = procurarFuncionarios(empresa, codigoFuncionario, 0, empresa->nFuncionarios-1);
    if(codigo!=-1){
        int idAno = procurarAnoTrabalho(&empresa->funcionarios[codigo], ano, 0, 
                empresa->funcionarios[codigo].trabalho.numeroAnos - 1);
        if(idAno != -1){
            int idMes = procurarMesTrabalho(&empresa->funcionarios[codigo].trabalho.anos[idAno], dados.Mes, 0,
                    empresa->funcionarios[codigo].trabalho.anos[idAno].numeroMeses-1);
            if(idMes != -1){
                printf("\n1 - Alterar dados");
                printf("\n2 - Não alterar dados");
                int op = obterInteiro(1,2,"Insira uma opção:");
                switch(op){
                    case 1:
                        adicionarSalarioRelatorioFinal(&empresa->funcionarios[codigo].trabalho.anos[idAno].meses[idMes], dados);
                        ordenarPorMesTrabalho(empresa->funcionarios[codigo].trabalho.anos[idAno].meses, 0, empresa->funcionarios[codigo].trabalho.anos[idAno].numeroMeses-1);
                        break;
                    case 2:
                        break;
                }
            }else{
                adicionarSalarioRelatorioMes(&empresa->funcionarios[codigo], idAno, dados);
            }
        }else{            
            Ano *novo = (Ano*) realloc(empresa->funcionarios[codigo].trabalho.anos, sizeof (Ano) * (empresa->funcionarios[codigo].trabalho.tamAnos + INC));
            if (novo != NULL) {
                empresa->funcionarios[codigo].trabalho.tamAnos += INC;
                empresa->funcionarios[codigo].trabalho.anos = novo;

                adicionarAno(&empresa->funcionarios[codigo], &idAno, ano);
                adicionarSalarioRelatorioMes(&empresa->funcionarios[codigo], idAno, dados);
            } else {
                puts("Erro ao alocar mais memória ao Ano.");
            }
        }
    }else{
        printf("\nNão foi possível importar os dados pois o funcionario com o código %d não existe.", codigoFuncionario);
    }
}

/**
 * Esta função pergunta ao utilizador qual o mês que pretende importar,  
 * se existir importa esses dados do ficheiro e de seguida chama a função "adicionarSalarioRelatorio"
 * @param empresa
 * @param nomesEmpresas
 */
void importarRelatorioFinal(Empresa *empresa, NomesEmpresas *nomesEmpresas) {
    if (empresa->nFuncionarios > 0) {
        int ano = obterInteiro(getAnoAtual() - 100, getAnoAtual(), "Ano que pretende exeportar:");
        int mes = obterInteiro(1, 12, "Mês que pretende exeportar:") - 1;
        char ano1[5];
        char mes1[5];
        char nomeFicheiro[80] = "\0";
        sprintf(ano1, "%d", ano);
        sprintf(mes1, "%d", mes + 1);
        juntar4Strings(nomeFicheiro, "./src/", nomesEmpresas->nomesEmpresas[empresa->idEmpresa].nome, "/relatorios/");
        juntar4Strings(nomeFicheiro, mes1, "-", ano1);
        juntar2Strings(nomeFicheiro, ".txt");
        
        FILE *fp;
        fp = fopen(nomeFicheiro, "r");
        if (fp == NULL) {
            puts("Não existe ficherio desse mês.");
        } else {
            int codigoFuncionario;
            Mes dados;
            dados.Mes = mes;

            while (fscanf(fp, "Codigo:%d\nMaximo dias de trabalho:%d\nDias Trabalhados:%d\nDias Completos:%d\nMeios Dias:%d\nDias Fim de Semana:%d\nFaltas:%d\nSalario Base:%f\nSalario Final:%f\nAlmoço:%f\nBonus:%f\nIRS:%f\nSeguranca Social:%f\nSeguranca Social Patronal:%f\n\n",
                    &codigoFuncionario, &dados.nMaxDias, &dados.nDiasTrabalhados, &dados.nDiasCompletos, 
                    &dados.nMeiosDias, &dados.nDiasFimSemana, &dados.nFaltas, &dados.salarioBase, 
                    &dados.salarioFinal, &dados.almoco, &dados.bonus, &dados.irs, 
                    &dados.segurancaSocial, &dados.segurancaSocialPatronal) != EOF) {
                adicionarSalarioRelatorio(empresa, codigoFuncionario, ano, dados);
            }

        }
        fclose(fp);

    } else {
        puts("Sem funcionarios.");
    }
}

/**
 * Esta função verifica se a empresa já foi guardada e se sim chama a função "importarRelatorioFinal"
 * @param empresa - apontador com todos os funcionarios
 * @param nomesEmpresas - apontador com os nomes das empresas(nome das pasta)
 */
void importarRelatorio(Empresa *empresa, NomesEmpresas *nomesEmpresas) {
    if (empresa->idEmpresa != -1) {
        importarRelatorioFinal(empresa, nomesEmpresas);
    } else {
        puts("Sem dados para importar.");
    }
}

/**
 * Está função exporta os salarios de um mês especifico para um ficheiro txt em formato de relatorio
 * @param empresa - apontador com todos o funcionarios
 * @param nomesEmpresas - apontador com os nomes das empresas(nomes das pasta)
 */
void exportarRelatorioFinal(Empresa *empresa, NomesEmpresas *nomesEmpresas) {
    int ano = obterInteiro(getAnoAtual() - 100, getAnoAtual(), "Ano que pretende exeportar:");
    int mes = obterInteiro(1, 12, "Mês que pretende exeportar:") - 1;
    if (verificaAnoMes(empresa, ano, mes) != 0) {
        char ano1[5];
        char mes1[5];
        char nomeFicheiro[80] = "\0";
        sprintf(ano1, "%d", ano);
        sprintf(mes1, "%d", mes + 1);
        juntar4Strings(nomeFicheiro, "./src/", nomesEmpresas->nomesEmpresas[empresa->idEmpresa].nome, "/relatorios/");
        juntar4Strings(nomeFicheiro, mes1, "-", ano1);
        juntar2Strings(nomeFicheiro, ".txt");

        FILE *fp;
        fp = fopen(nomeFicheiro, "w");
        if (fp == NULL) {
            puts("Erro ao criar/alterar ficheiro.");
        } else {
            int idAno, idMes;
            for (int i = 0; i < empresa->nFuncionarios; i++) {
                idAno = procurarAnoTrabalho(&empresa->funcionarios[i], ano, 0, empresa->funcionarios[i].trabalho.numeroAnos - 1);
                if (idAno != -1) {
                    idMes = procurarMesTrabalho(&empresa->funcionarios[i].trabalho.anos[idAno], mes, 0,
                            empresa->funcionarios[i].trabalho.anos[idAno].numeroMeses - 1);
                    if (idMes != -1) {
                        fprintf(fp, "Codigo:%d\nMaximo dias de trabalho:%d\nDias Trabalhados:%d\nDias Completos:%d\nMeios Dias:%d\nDias Fim de Semana:%d\nFaltas:%d\nSalario Base:%.2f\nSalario Final:%.2f\nAlmoço:%.2f\nBonus:%f\nIRS:%.2f\nSeguranca Social:%.2f\nSeguranca Social Patronal:%.2f\n\n",
                                empresa->funcionarios[i].codigoFuncionario,
                                empresa->funcionarios[i].trabalho.anos[idAno].meses[idMes].nMaxDias,
                                empresa->funcionarios[i].trabalho.anos[idAno].meses[idMes].nDiasTrabalhados,
                                empresa->funcionarios[i].trabalho.anos[idAno].meses[idMes].nDiasCompletos,
                                empresa->funcionarios[i].trabalho.anos[idAno].meses[idMes].nMeiosDias,
                                empresa->funcionarios[i].trabalho.anos[idAno].meses[idMes].nDiasFimSemana,
                                empresa->funcionarios[i].trabalho.anos[idAno].meses[idMes].nFaltas,
                                empresa->funcionarios[i].trabalho.anos[idAno].meses[idMes].salarioBase,
                                empresa->funcionarios[i].trabalho.anos[idAno].meses[idMes].salarioFinal,
                                empresa->funcionarios[i].trabalho.anos[idAno].meses[idMes].almoco,
                                empresa->funcionarios[i].trabalho.anos[idAno].meses[idMes].bonus,
                                empresa->funcionarios[i].trabalho.anos[idAno].meses[idMes].irs,
                                empresa->funcionarios[i].trabalho.anos[idAno].meses[idMes].segurancaSocial,
                                empresa->funcionarios[i].trabalho.anos[idAno].meses[idMes].segurancaSocialPatronal
                                );
                    }
                }
            }
            printf("Dados exportados com sucesso.");
        }
        fclose(fp);
    } else {
        printf("Sem dados para exportar nesse mes.");
    }
}

/**
 * Está função verifica se o utilizador ja tem alguma empresa atribuida e senão pede para a criar, 
 * de seguida chama a função "exportarRelatorioFinal"
 * @param empresa - apontador com todos os funcionarios
 * @param irsdados - apontador com todos os dados do IRS
 * @param nomesEmpresas - apontador com os nomes das empresas(nome das pasta)
 * @param taxasContributivas - apontador com as Taxas de Contribuinte
 */
void exportarRelatorio(Empresa *empresa, IRSDados *irsdados, NomesEmpresas *nomesEmpresas, TaxasContributivas *taxasContributivas) {
    if (empresa->nFuncionarios > 0) {
        if (empresa->idEmpresa != -1) {
            exportarRelatorioFinal(empresa, nomesEmpresas);
        } else {
            int c = guardar(empresa, irsdados, nomesEmpresas, taxasContributivas);
            if (c == 1) {
                exportarRelatorioFinal(empresa, nomesEmpresas);
            }
        }
    } else {
        puts("Sem dados para exportar");
    }
}