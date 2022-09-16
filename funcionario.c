#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionario.h"
#include "funcoes.h"
#include "input.h"
#include "segurancaSocial.h"

/**
 * Função utilizada para pesquisar um funcionário através do seu código.
 * @param empresa - apontador onde se encontram guardados os funcionários.
 * @param codigo - valor correspondente ao código do funcionário a ser pesquisado.
 * @param inicio - valor correspondente à primeira posição a ser procurada.
 * @param fim - valor correspondente à última posição a ser procurada.
 * @return indice do funcionário (caso seja encontrado), -1 (caso não seja encontrado) ou -2 (caso este já tenha saido da empresa).
 */
int procurarFuncionarios(Empresa *empresa, int codigo, int inicio, int fim) {
    if (fim >= inicio) {
        int meio = inicio + ((fim - inicio) / 2);

        if (empresa->funcionarios[meio].codigoFuncionario == codigo && empresa->funcionarios[meio].dataSaidaEmpresa.ano == 0) {
            return meio;
        }else if (empresa->funcionarios[meio].codigoFuncionario == codigo && empresa->funcionarios[meio].dataSaidaEmpresa.ano > 0){
            return -2;
        }

        return (empresa->funcionarios[meio].codigoFuncionario > codigo) ?
                procurarFuncionarios(empresa, codigo, inicio, meio - 1) :
                procurarFuncionarios(empresa, codigo, meio + 1, fim);
    }

    return -1;
}

/**
 * Função utilizada para ordenar os funcionários através dos códigos, utilizando o método de ordenação "QuickSort".
 * @param funcionarios - apontador onde se encontram guardados os funcionários.
 * @param inicio - valor correspondente à primeira posição do apontador.
 * @param fim - valor correspondente à última posição do apontador.
 */
void ordenaFuncionariosCodigo(Funcionario *funcionarios, int inicio, int fim) {
    int i, j, pivot;
    Funcionario temp;

    if (inicio < fim) {
        pivot = inicio;
        i = inicio;
        j = fim;

        while (i < j) {
            while (funcionarios[i].codigoFuncionario <= funcionarios[pivot].codigoFuncionario && i < fim)
                i++;
            while (funcionarios[j].codigoFuncionario > funcionarios[pivot].codigoFuncionario)
                j--;
            if (i < j) {
                temp = funcionarios[i];
                funcionarios[i] = funcionarios[j];
                funcionarios[j] = temp;
            }
        }

        temp = funcionarios[pivot];
        funcionarios[pivot] = funcionarios[j];
        funcionarios[j] = temp;
        ordenaFuncionariosCodigo(funcionarios, inicio, j - 1);
        ordenaFuncionariosCodigo(funcionarios, j + 1, fim);

    }
}

/**
 * Função utilizada para inserir um novo funcionário após verificação do código.
 * @param empresa - apontador onde será guardado o funcionário.
 * @return -1 (caso o funcionário seja inserido), índice do funcionário (caso o código de funcionário já tenha sido atribuído).
 */
int inserirFuncionario(Empresa *empresa) {
    int codigo = obterInteiro(MIN_COD_FUNCIONARIO, MAX_COD_FUNCIONARIO, MSG_OBTER_COD_FUNCIONARIO);
    int existe = procurarFuncionarios(empresa, codigo, 0, empresa->nFuncionarios - 1);

    if (existe == -1) {
        empresa->funcionarios[empresa->nFuncionarios].codigoFuncionario = codigo;
        lerString(empresa->funcionarios[empresa->nFuncionarios].nome, MAX_NOME_FUNCIONARIO, MSG_OBTER_NOME);
        empresa->funcionarios[empresa->nFuncionarios].numeroTelefone = obterTelefone(MSG_OBTER_NUM_TELEFONE);
        empresa->funcionarios[empresa->nFuncionarios].numeroTelemovel = obterTelemovel(MSG_OBTER_NUM_TELEMOVEL);
        empresa->funcionarios[empresa->nFuncionarios].estadoCivil = obterInteiro(MIN_ESTADO_CIVIL, MAX_ESTADO_CIVIL, MSG_OBTER_ESTADO_CIVIL);
        empresa->funcionarios[empresa->nFuncionarios].numeroFilhosDependentes = obterInteiro(MIN_NUM_FILHOS, MAX_NUM_FILHOS, MSG_OBTER_NUM_FILHOS);
        empresa->funcionarios[empresa->nFuncionarios].cargo = obterInteiro(MIN_CARGO, MAX_CARGO, MSG_OBTER_CARGO);
        switch (empresa->funcionarios[empresa->nFuncionarios].cargo) {
            case Empregado:
                empresa->funcionarios[empresa->nFuncionarios].valorHora = 5;
                empresa->funcionarios[empresa->nFuncionarios].valorSubsidioAlimentacao = 5;
                break;
            case Chefe:
                empresa->funcionarios[empresa->nFuncionarios].valorHora = 7.5;
                empresa->funcionarios[empresa->nFuncionarios].valorSubsidioAlimentacao = 7.5;
                break;
            case Administrador:
                empresa->funcionarios[empresa->nFuncionarios].valorHora = 10;
                empresa->funcionarios[empresa->nFuncionarios].valorSubsidioAlimentacao = 7.5;
                break;
        }
        obterDataNacimento(&empresa->funcionarios[empresa->nFuncionarios].dataNascimento, MSG_OBTER_DATA_NASC);
        obterDataEntrada(&empresa->funcionarios[empresa->nFuncionarios].dataEntradaEmpresa, &empresa->funcionarios[empresa->nFuncionarios].dataNascimento, MSG_OBTER_DATA_ENTRADA);
        empresa->funcionarios[empresa->nFuncionarios].dataSaidaEmpresa.dia = 0;
        empresa->funcionarios[empresa->nFuncionarios].dataSaidaEmpresa.mes = 0;
        empresa->funcionarios[empresa->nFuncionarios].dataSaidaEmpresa.ano = 0;

        empresa->funcionarios[empresa->nFuncionarios].trabalho.anos = NULL;
        empresa->funcionarios[empresa->nFuncionarios].trabalho.numeroAnos = 0;
        empresa->funcionarios[empresa->nFuncionarios].trabalho.tamAnos = 0;

        empresa->nFuncionarios++;
        ordenaFuncionariosCodigo(empresa->funcionarios, 0, empresa->nFuncionarios - 1);
    }
    return existe;
}

/**
 * Função utilizada para alocar espaço para os funcionários e chamar a função "inserirFuncionario".
 * @param empresa - apontador onde será guardado o funcionário.
 */
void inserirFuncionarios(Empresa *empresa) {
    Funcionario *novo;
    int p;
    if (empresa->nFuncionarios == empresa->maxFuncionarios) {
        novo = (Funcionario*) realloc(empresa->funcionarios, sizeof (Funcionario) * (empresa->maxFuncionarios + INC));
        if (novo != NULL) {
            empresa->maxFuncionarios += INC;
            empresa->funcionarios = novo;
            p = inserirFuncionario(empresa);
        }else{
            puts("Erro ao alocar mais memória no Funcionario");
        }
    } else {
        p = inserirFuncionario(empresa);
    }

    if (p == -1) {
        puts(SUCESS_FUNCIONARIO);
    } else {
        puts(ERRO_FUNCIONARIO_EXISTE);
    }
}

/**
 * Função utilizada para listar um determinado funcionário.
 * @param funcionario - apontador onde se encontra guardado o funcionário.
 */
void listarFuncionario(Funcionario *funcionario) {
    printf("\nFuncionário (código - nome): %d - %s ", funcionario->codigoFuncionario, funcionario->nome);
    printf("\nTelefone: %d \nTelemóvel: %d", funcionario->numeroTelefone, funcionario->numeroTelemovel);
    switch (funcionario->estadoCivil) {
        case Solteiro:
            printf("\nEstado civil: Solteiro");
            break;
        case Casado:
            printf("\nEstado civil: Casado");
            break;
        case Divorciado:
            printf("\nEstado civil: Divorciado");
            break;
        case Viuvo:
            printf("\nEstado civil: Viuvo");
            break;
    }
    printf("\nNúmero de filhos dependentes: %d", funcionario->numeroFilhosDependentes);
    switch (funcionario->cargo) {
        case Empregado:
            printf("\nCargo: Empregado");
            break;
        case Chefe:
            printf("\nCargo: Chefe");
            break;
        case Administrador:
            printf("\nCargo: Administrador");
            break;
    }
    printf("\nData de nascimento: %d/%d/%d", funcionario->dataNascimento.dia, funcionario->dataNascimento.mes, funcionario->dataNascimento.ano);
    printf("\nData de entrada na empresa: %d/%d/%d \n", funcionario->dataEntradaEmpresa.dia, funcionario->dataEntradaEmpresa.mes, funcionario->dataEntradaEmpresa.ano);
    if (funcionario->dataSaidaEmpresa.ano != 0) {
        printf("\nData de saida na empresa: %d/%d/%d \n", funcionario->dataSaidaEmpresa.dia, funcionario->dataSaidaEmpresa.mes, funcionario->dataSaidaEmpresa.ano);
    }
}

/**
 * Função utilizada para atualizar os dados de um funcionário.
 * @param funcionario - apontador onde se encontra guardado o funcionário.
 * @param empresa - apontador onde se encontam guardados os funcionários (utilizado para pesquisa).
 */
void atualizarFuncionario(Funcionario *funcionario, Empresa *empresa) {
    int op, codigo, x = 0, cargoAntigo;
    listarFuncionario(funcionario);
    
    printf("\nOpções");
    printf("\n1 - Nome");
    printf("\n2 - Código");
    printf("\n3 - Telefone");
    printf("\n4 - Telemóvel");
    printf("\n5 - Estado Civil");
    printf("\n6 - Número de filhos dependentes");
    printf("\n7 - Cargo");
    printf("\n8 - Alterar valor hora");
    printf("\n9 - Data de nascimento");
    printf("\n10 - Data de entrada na empresa");
    printf("\n11 - Data de saida na empresa");
    printf("\n\t\t0 - Voltar");
    printf("\n------------------------------------------------------------");

    op = obterInteiro(0, 11, MSG_OBTER_OPCAO);
    switch (op) {
        case 0:
            break;
        case 1:
            lerString(funcionario->nome, MAX_NOME_FUNCIONARIO, MSG_OBTER_NOME);
            break;
        case 2:
            //Deixar como está (enviar o funcionario e os funcionarios(utilizado para procurar)) ou tentamos de outra maneira?
            do {
                codigo = obterInteiro(MIN_COD_FUNCIONARIO, MAX_COD_FUNCIONARIO, MSG_OBTER_COD_FUNCIONARIO);
                if (procurarFuncionarios(empresa, codigo, 0, empresa->nFuncionarios - 1) == -1) {
                    x = -1;
                } else {
                    puts(ERRO_FUNCIONARIO_EXISTE);
                }
            } while (x != -1);
            funcionario->codigoFuncionario = codigo;
            ordenaFuncionariosCodigo(empresa->funcionarios, 0, empresa->nFuncionarios - 1);
            break;
        case 3:
            funcionario->numeroTelefone = obterTelefone(MSG_OBTER_NUM_TELEFONE);
            break;
        case 4:
            funcionario->numeroTelemovel = obterTelemovel(MSG_OBTER_NUM_TELEMOVEL);
            break;
        case 5:
            funcionario->estadoCivil = obterInteiro(MIN_ESTADO_CIVIL, MAX_ESTADO_CIVIL, MSG_OBTER_ESTADO_CIVIL);
            break;
        case 6:
            funcionario->numeroFilhosDependentes = obterInteiro(MIN_NUM_FILHOS, MAX_NUM_FILHOS, MSG_OBTER_NUM_FILHOS);
            break;
        case 7:
            cargoAntigo = funcionario->cargo;
            funcionario->cargo = obterInteiro(MIN_CARGO, MAX_CARGO, MSG_OBTER_CARGO);
            switch (funcionario->cargo) {
                case Empregado:
                    if (cargoAntigo > Empregado) {
                        funcionario->valorHora = 5;
                    }
                    funcionario->valorSubsidioAlimentacao = 5;
                    break;
                case Chefe:
                    if (cargoAntigo == Empregado && funcionario->valorHora < 7.5 || cargoAntigo > Chefe) {
                        funcionario->valorHora = 7.5;
                    }
                    funcionario->valorSubsidioAlimentacao = 7.5;
                    break;
                case Administrador:
                    if (cargoAntigo < Administrador && funcionario->valorHora < 10) {
                        funcionario->valorHora = 10;
                    }
                    funcionario->valorSubsidioAlimentacao = 7.5;
                    break;
            }
            break;
        case 8:
            empresa->funcionarios[empresa->nFuncionarios].valorHora = obterFloat(MIN_VALOR_HORA, MAX_VALOR_HORA, MSG_OBTER_VALOR_HORA);
            break;
        case 9:
            obterDataNacimento_Alterar(&funcionario->dataNascimento, &funcionario->dataEntradaEmpresa, MSG_OBTER_DATA_NASC);
            break;
        case 10:
            obterDataEntrada(&funcionario->dataEntradaEmpresa, &funcionario->dataNascimento, MSG_OBTER_DATA_ENTRADA);
            break;
        case 11:
            if(funcionario->trabalho.numeroAnos>0){
                obterDataSaida(&funcionario->dataSaidaEmpresa, funcionario->trabalho.anos[funcionario->trabalho.numeroAnos - 1].ano,
                        funcionario->trabalho.anos[funcionario->trabalho.numeroAnos - 1].meses[funcionario->trabalho.anos[funcionario->trabalho.numeroAnos - 1].numeroMeses - 1].Mes,
                        MSG_OBTER_DATA_SAIDA);
            }else{        
                obterDataSaida(&funcionario->dataSaidaEmpresa, funcionario->dataEntradaEmpresa.ano,funcionario->dataEntradaEmpresa.mes, MSG_OBTER_DATA_SAIDA);
            }
            break;
    }
}

/**
 * Função utilizada para verificar se um funcionário existe e caso exista, chamar a função "atualizarFuncionario".
 * @param empresa - apontador onde se encontam guardados os funcionários.
 */
void atualizarFuncionarios(Empresa *empresa) {
    int codigo = procurarFuncionarios(empresa, obterInteiro(MIN_COD_FUNCIONARIO, MAX_COD_FUNCIONARIO, MSG_OBTER_COD_FUNCIONARIO), 0, empresa->nFuncionarios - 1);

    if (codigo == -1) {
        puts(ERRO_FUNCIONARIO_NAO_EXISTE);
    } else if (codigo == -2) {
        puts(ERRO_FUNCIONARIO_ELIMINADO);
    } else {
        atualizarFuncionario(&empresa->funcionarios[codigo], empresa);
    }
}

/**
 * Função utilizada para eliminar um funcionário (atualiza a data de saída da empresa de um funcionário).
 * @param funcionario - apontador onde se encontra guardado o funcionário.
 */
void eliminarFuncionario(Funcionario *funcionario) {
    if(funcionario->trabalho.numeroAnos>0){
        obterDataSaida(&funcionario->dataSaidaEmpresa, funcionario->trabalho.anos[funcionario->trabalho.numeroAnos - 1].ano,
                funcionario->trabalho.anos[funcionario->trabalho.numeroAnos - 1].meses[funcionario->trabalho.anos[funcionario->trabalho.numeroAnos - 1].numeroMeses - 1].Mes,
                MSG_OBTER_DATA_SAIDA);
    }else{        
        obterDataSaida(&funcionario->dataSaidaEmpresa, funcionario->dataEntradaEmpresa.ano,funcionario->dataEntradaEmpresa.mes, MSG_OBTER_DATA_SAIDA);
    }
}

/**
 * Função utilizada para verificar se um funcionário existe e caso exista, chamar a função "eliminarFuncionario".
 * @param empresa - apontador onde se encontam guardados os funcionários.
 */
void eliminarFuncionarios(Empresa *empresa) {
    int codigo = procurarFuncionarios(empresa, obterInteiro(MIN_COD_FUNCIONARIO, MAX_COD_FUNCIONARIO, MSG_OBTER_COD_FUNCIONARIO), 0, empresa->nFuncionarios - 1);

    if (codigo == -1) {
        puts(ERRO_FUNCIONARIO_NAO_EXISTE);
    } else if (codigo == -2) {
        puts(ERRO_FUNCIONARIO_ELIMINADO);
    } else {
        eliminarFuncionario(&empresa->funcionarios[codigo]);
    }
}

/**
 * Função utilizada para verificar se um funcionário existe e caso exista, chamar a função "listarFuncionario".
 * @param empresa - apontador onde se encontam guardados os funcionários.
 */
void pesquisarFuncionarioCodigo(Empresa *empresa) {
    int codigo = procurarFuncionarios(empresa, obterInteiro(MIN_COD_FUNCIONARIO, MAX_COD_FUNCIONARIO, MSG_OBTER_COD_FUNCIONARIO), 0, empresa->nFuncionarios - 1);
    if (codigo == -1) {
        puts(ERRO_FUNCIONARIO_NAO_EXISTE);
    } else {
        listarFuncionario(&empresa->funcionarios[codigo]);
    }
}

/**
 * Função utilizada para guardar os índices de determinados funcionários num apontador.
 * @param idFuncionario - apontador onde serão guardados os índices dos funcionários.
 * @param max - valor correspondente ao número máximo de espaços disponíveis.
 * @param posicao - valor correspondente ao número de índices guardados.
 * @param n - valor correspondente ao índice a ser armazenado.
 * @return 1 (caso a função seja executada com sucesso) ou 0 (caso a função não seja executada com sucesso).
 */
int addIdFuncionario(int **idFuncionario, int *max, int *posicao, int n) {
    int resultado = 1;
    if (*max == *posicao) {
        int *novo = (int*) realloc(*idFuncionario, sizeof (int) * ((*max) + INC));
        if (novo != NULL) {
            *idFuncionario = novo;
            (*max) = (*max) + INC;
            (*idFuncionario)[*posicao] = n;
            (*posicao) = (*posicao) + 1;
        } else {
            puts("Erro ao alocar mais memória ao Id Funcionario.");
            resultado = 0;
        }
    } else {
        (*idFuncionario)[*posicao] = n;
        (*posicao) = (*posicao) + 1;
    }
    return resultado;
}

/**
 * Função utilizada para ler um nome, listar o nome dos funcionários que contenham o nome inserido e após o utilizador selecionar um funcionário, 
 * chamar a função "listarFuncionario".
 * @param empresa - apontador onde se encontam guardados os funcionários.
 */
void pesquisarFuncionarioNome(Empresa *empresa) {
    char nomeFun[MAX_NOME_FUNCIONARIO];
    int *idFuncionario = NULL;
    int max = 0, posicao = 0;
    lerString(nomeFun, MAX_NOME_FUNCIONARIO, MSG_OBTER_NOME);
    for (int i = 0; i < empresa->nFuncionarios; i++) {
        if (verificarPalavras(empresa->funcionarios[i].nome, nomeFun) == 1) {
            addIdFuncionario(&idFuncionario, &max, &posicao, i);
            printf("%d - %s\n", posicao, empresa->funcionarios[i].nome);
        }
    }
    if (posicao > 0) {
        posicao = obterInteiro(1, posicao + 1, MSG_ESCOLHER_NOME) - 1;
        listarFuncionario(&empresa->funcionarios[idFuncionario[posicao]]);
    } else {
        puts(ERRO_FUNCIONARIO_NAO_EXISTE);
    }
    free(idFuncionario);
}

/**
 * Função utilizada listar todos os funcionários da empresa.
 * @param empresa - apontador onde se encontram guardados os funcionários.
 */
void listaFuncionarios(Empresa *empresa) {
    if(empresa->nFuncionarios>0){
        for (int i = 0; i < empresa->nFuncionarios; i++) {
            listarFuncionario(&empresa->funcionarios[i]);
        }
    }else{
        puts(ERRO_LISTA_VAZIA);
    }
}

/**
 * Função utilizada listar todos os funcionários atuais da empresa.
 * @param empresa - apontador onde se encontram guardados os funcionários.
 */
void listaFuncionariosAtuais(Empresa *empresa) {
    if(empresa->nFuncionarios>0){
        for (int i = 0; i < empresa->nFuncionarios; i++) {
        if (empresa->funcionarios[i].dataSaidaEmpresa.ano == 0) {
            listarFuncionario(&empresa->funcionarios[i]);
        }
    }
    }else{
        puts(ERRO_LISTA_VAZIA);
    }
}

/**
 * Função utilizada listar todos os funcionários que já saíram da empresa.
 * @param empresa - apontador onde se encontram guardados os funcionários.
 */
void listaFuncionariosEliminados(Empresa *empresa) {
    if(empresa->nFuncionarios>0){
        for (int i = 0; i < empresa->nFuncionarios; i++) {
            if (empresa->funcionarios[i].dataSaidaEmpresa.ano != 0) {
                listarFuncionario(&empresa->funcionarios[i]);
            }
        }
    }else{
        puts(ERRO_LISTA_VAZIA);
    }
}

/**
 * Função utilizada para guardar o número de funcionários num ficheiro.
 * @param contador - valor correspondente ao número de funcionários.
 * @param ficheiro - nome do ficheiro onde será armazenada a informação.
 */
void atualizacontador(int contador, char *ficheiro) {
    FILE *fp = fopen(ficheiro, "w+b");
    if (fp == NULL) {
        puts("Erro ao abrir ficheiro.");
    }else{
        fwrite(&contador, sizeof (int), 1, fp);
    }
    fclose(fp);
}

/**
 * Função utilizada para guardar todos os dados dos funcionários num ficheiro.
 * @param empresa - apontador onde se encontram guardados os funcionários.
 * @param ficheiro - nome do ficheiro onde serão guardados os dados.
 */
void armazenaDados(Empresa *empresa, char *ficheiro) {
    atualizacontador(empresa->nFuncionarios, ficheiro);

    FILE *fp = fopen(ficheiro, "ab");
    if (fp == NULL) {
        puts("Erro ao abrir ficheiro.");
    }else{
        for (int i = 0; i < empresa->nFuncionarios; i++) {
            fwrite(&empresa->funcionarios[i], sizeof (Funcionario), 1, fp);
            for (int j = 0; j < empresa->funcionarios[i].trabalho.numeroAnos; j++) {
                fwrite(&empresa->funcionarios[i].trabalho.anos[j], sizeof (Ano), 1, fp);
                for (int k = 0; k < empresa->funcionarios[i].trabalho.numeroAnos; k++) {
                    fwrite(&empresa->funcionarios[i].trabalho.anos[j].meses[k], sizeof (Mes), 1, fp);
                }
            }
        }
    }
    fclose(fp);
}

/**
 * Função utilizada para importar todos os dados dos funcionários de um ficheiro.
 * @param empresa - apontador serão guardados os dados dos funcionários.
 * @param ficheiro - nome do ficheiro onde se encontram guardados os dados.
 */
void importaDados(Empresa *empresa, char *ficheiro) {
    FILE *fp = fopen(ficheiro, "rb");
    if (fp != NULL) {
        fread(&empresa->nFuncionarios, sizeof (int), 1, fp);
        if (empresa->nFuncionarios > 0) {
            empresa->funcionarios = (Funcionario*) calloc(empresa->nFuncionarios + INC, sizeof (Funcionario));
            if (empresa->funcionarios != NULL) {
                empresa->maxFuncionarios = empresa->nFuncionarios + INC;
                for (int i = 0; i < empresa->nFuncionarios; i++) {
                    fread(&empresa->funcionarios[i], sizeof (Funcionario), 1, fp);
                    if (empresa->funcionarios[i].trabalho.numeroAnos > 0) {

                        empresa->funcionarios[i].trabalho.anos = (Ano*) calloc(empresa->funcionarios[i].trabalho.numeroAnos + 1, sizeof (Ano));
                        if (empresa->funcionarios[i].trabalho.anos != NULL) {
                            empresa->funcionarios[i].trabalho.tamAnos = empresa->funcionarios[i].trabalho.numeroAnos + 1;
                            for (int j = 0; j < empresa->funcionarios[i].trabalho.numeroAnos; j++) {
                                fread(&empresa->funcionarios[i].trabalho.anos[j], sizeof (Ano), 1, fp);

                                if (empresa->funcionarios[i].trabalho.anos[j].numeroMeses > 0) {

                                    empresa->funcionarios[i].trabalho.anos[j].meses = (Mes*) calloc(empresa->funcionarios[i].trabalho.anos[j].tamMeses, sizeof (Mes));
                                    if (empresa->funcionarios[i].trabalho.anos[j].meses != NULL) {
                                        for (int k = 0; k < empresa->funcionarios[i].trabalho.anos[j].numeroMeses; k++) {
                                            fread(&empresa->funcionarios[i].trabalho.anos[j].meses[k], sizeof (Mes), 1, fp);
                                        }
                                    } else {
                                        empresa->funcionarios[i].trabalho.anos[j].numeroMeses = 0;
                                        empresa->funcionarios[i].trabalho.anos[j].tamMeses = 0;
                                    }
                                } else {
                                    empresa->funcionarios[i].trabalho.anos[j].meses = NULL;
                                }

                            }
                        } else {
                            puts("Erro ao alocar mais memória ao ano.");
                            empresa->funcionarios[i].trabalho.numeroAnos = 0;
                            empresa->funcionarios[i].trabalho.tamAnos = 0;
                        }

                    } else {
                        empresa->funcionarios[i].trabalho.anos = NULL;
                    }
                }
            } else {
                puts("Erro ao alocar mais memória ao funcionario.");
                empresa->nFuncionarios = 0;
            }
        } else {
            empresa->funcionarios = NULL;
        }
    } else {
        fp = fopen(ficheiro, "wb");
    }
    fclose(fp);
}

/**
 * Função utilizada para obter a média de faltas de um funcionário num determinado ano.
 * @param funcionario - apontador onde se encontram guardados os dados do funcionário.
 */
void mediaFaltasFunc(Funcionario *funcionario) {
    int idAno, diasDeviaTrabalho = 0;
    float mediaFaltas = 0;

    idAno = obterAnoFaltas(funcionario, MSG_INSIRA_ANO);

    for (int i = 0; i < funcionario->trabalho.anos[idAno].numeroMeses; i++) {
        mediaFaltas += funcionario->trabalho.anos[idAno].meses[i].nFaltas;
        diasDeviaTrabalho += funcionario->trabalho.anos[idAno].meses[i].nMaxDias;
    }
    printf(MSG_MEDIA_FALTAS, funcionario->nome, ((mediaFaltas / diasDeviaTrabalho) * 100),
            funcionario->trabalho.anos[idAno].ano);
}

/**
 * Função utilizada para verificar se um funcionário existe e caso exista, chamar a função "mediaFaltasFunc".
 * @param empresa - apontador onde se encontam guardados os funcionários.
 */
void mediaFaltas(Empresa *empresa) {
    int codigo = procurarFuncionarios(empresa, obterInteiro(MIN_COD_FUNCIONARIO, MAX_COD_FUNCIONARIO, MSG_OBTER_COD_FUNCIONARIO), 0, empresa->nFuncionarios - 1);
    if (codigo == -1) {
        puts(ERRO_FUNCIONARIO_NAO_EXISTE);
    } else {
        if(empresa->funcionarios[codigo].trabalho.numeroAnos>0){
            mediaFaltasFunc(&empresa->funcionarios[codigo]);
        }else{
            puts("O funcionario ainda não tem nenhum salário inserido.");
        }
    }
}

/**
 * Função utilizada procurar a taxa contributiva a ser utilizada num funcionário e chamar a função "listaTaxaContributiva".
 * @param taxasContributivas - apontador onde se encontam guardadas as taxas contributivas.
 * @param empresa - apontador onde se encontam guardados os funcionários.
 */
void pesquisarTaxaFuncionario(TaxasContributivas *taxasContributivas, Empresa *empresa) {
    int codigo = procurarFuncionarios(empresa, obterInteiro(MIN_COD_FUNCIONARIO, MAX_COD_FUNCIONARIO, MSG_OBTER_COD_FUNCIONARIO), 0, empresa->nFuncionarios - 1);
    if (codigo == -1) {
        puts(ERRO_FUNCIONARIO_NAO_EXISTE);
    } else {
        int ano = obterInteiro(empresa->funcionarios[codigo].dataEntradaEmpresa.ano, getAnoAtual()+100, "Ano em que pretende fazer a pesquisa:");
        int mes = obterInteiro(1, 12, "Mês em que pretende fazer a pesquisa:");
        int idade = idadeFimMes(empresa->funcionarios[codigo].dataNascimento.mes, empresa->funcionarios[codigo].dataNascimento.ano, mes, ano);
        int anosTrabalho = idadeFimMes(empresa->funcionarios[codigo].dataEntradaEmpresa.mes, empresa->funcionarios[codigo].dataEntradaEmpresa.ano, mes, ano);
        int idTaxa = getTaxaContributiva(taxasContributivas, &empresa->funcionarios[codigo], idade, anosTrabalho);       
        if (idTaxa != -1) {
            listaTaxaContributiva(&taxasContributivas->taxasContributivas[idTaxa]);
             printf("\n");
        }else{
            printf("Error a calcular taxa");
        }
    }
}