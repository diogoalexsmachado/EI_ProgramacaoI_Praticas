#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>

#include "funcoesAuxiliares.h"
#include "funcoesMenus.h"

#define LOCAL_ARMAZEM "ARMAZEM-ABATES"
#define LOCAL_INVENTARIO "ARMAZEM-INVENTARIO"
#define LOCAL_AVARIA "EM REPARACAO"


#define MAX_LABORATORIOS 15
#define MAX_EQUIPAMENTOS 200

#define NAO_EXISTE -1    // Valor devolvido pelas fun��es procurar(...) quando o laborat�rio, equipamento ou avaria n�o existem no respetivo vetor

#define ESTADO_DISPONIVEL 1     // O equipamento est� funcional
#define ESTADO_INDISPONIVEL -1  // o equipamento est� avariado
#define ESTADO_ABATIDO 0        // O equipamento est� abatido -> em Armazem-abates

#define ANO_MIN 2010
#define ANO_MAX 2500

#define POSTO_TRABALHO_MIN 0
#define POSTO_TRABALHO_MAX 30

#define CUSTO_MAX 9999999.999

typedef struct
{
    int dia, mes, ano;
} tipoData;


typedef struct
{
    char designacao[TEXTO_BREVE];   // valor �nico
    char localizacao [TEXTO_BREVE];
    int numPostosTrabalho;
    int quantEquipamentosInstalados;
} tipoLaboratorio;

typedef struct
{
    int numInventario;   // valor �nico
    tipoData dataInventario;
    char descricao [TEXTO_LONGO];
    char numSerie [TEXTO_BREVE];
    char local [TEXTO_BREVE];
    int estado;   // (1)-ESTADO_DISPONIVEL  (-1)-ESTADO_INDISPONIVEL (0)-ESTADO_ABATIDO
                  // em alternativa o estado poderia ser um char estado ou uma string   char estado[TEXTO_BREVE]
    float custo;
} tipoEquipamento;




// ----------- DECLARA��O DAS FUN��ES -------------
tipoData lerData (void);
void escreveData (tipoData data);

int procuraLaboratorio (tipoLaboratorio vetorLaboratorios[MAX_LABORATORIOS], int quantLaboratorios, char designacao[TEXTO_BREVE]);
void listaLaboratorios (tipoLaboratorio vetorLaboratorios[MAX_LABORATORIOS], int quantLaboratorios);
void inserirLaboratorio (tipoLaboratorio vetorLaboratorios[MAX_LABORATORIOS], int *quantLaboratorios);
void alterarLaboratorio (tipoLaboratorio vetorLaboratorios[MAX_LABORATORIOS], int quantLaboratorios);
void consultaLaboratorioDesignacao (tipoLaboratorio vetorLaboratorios[MAX_LABORATORIOS], int quantLaboratorios);
void escreveDadosLaboratorio (tipoLaboratorio laboratorio, int cabecalho);


int procuraEquipamento (tipoEquipamento vetorEquipamentos[MAX_EQUIPAMENTOS], int quantEquipamentos, int numInventario);
void inserirEquipamento (tipoEquipamento vetorEquipamentos[MAX_EQUIPAMENTOS], int *quantEquipamentos);
void alterarEquipamento (tipoEquipamento vetorEquipamentos[MAX_EQUIPAMENTOS], int quantEquipamentos);
void listaEquipamentos (tipoEquipamento vetorEquipamentos[MAX_EQUIPAMENTOS], int quantEquipamentos);
void consultaEquipamentoNrInventario (tipoEquipamento vetorEquipamentos[MAX_EQUIPAMENTOS], int quantEquipamentos);
void escreveDadosEquipamento (tipoEquipamento equipamento, int cabecalho);


void guardarFicheiro (tipoLaboratorio vetorLaboratorios[MAX_LABORATORIOS], int quantLaboratorios, tipoEquipamento vetorEquipamentos[MAX_EQUIPAMENTOS], int quantEquipamentos);
void lerFicheiro (tipoLaboratorio vetorLaboratorios[MAX_LABORATORIOS], int *quantLaboratorios, tipoEquipamento vetorEquipamentos[MAX_EQUIPAMENTOS], int *quantEquipamentos);

int calculos (tipoLaboratorio vetorLaboratorios[MAX_LABORATORIOS], int quantLaboratorios);


int main(void)
{
    tipoLaboratorio vetorLaboratorios[MAX_LABORATORIOS];
    tipoEquipamento vetorEquipamentos[MAX_EQUIPAMENTOS];
    int quantLaboratorios, quantEquipamentos, quantPostosTrabalho, subOpc;
    char opc;
    float percEquipAvariados;


    quantPostosTrabalho=0;
    percEquipAvariados=0;
    quantLaboratorios=0;
    quantEquipamentos=0;


    do
    {
        quantPostosTrabalho = calculos(vetorLaboratorios, quantLaboratorios);
        opc = menu(quantLaboratorios, quantPostosTrabalho, quantEquipamentos, percEquipAvariados);
        switch (opc)
        {
            case 'G': // gerir Laborat�rios
                do{
                    subOpc = subMenuLaboratorios();
                    switch (subOpc)
                    {
                        case 1:  // Inserir um novo laboratorio
                            inserirLaboratorio(vetorLaboratorios, &quantLaboratorios);
                            break;
                        case 2:  // Alterar os campos alter�veis do laborat�rio
                            alterarLaboratorio (vetorLaboratorios, quantLaboratorios);
                            break;
                        case 3:  // Listar TODOS os laborat�rios
                            listaLaboratorios(vetorLaboratorios, quantLaboratorios);
                            break;
                        case 4:  // Consulta UM laboratorio pela sua designa��o
                            consultaLaboratorioDesignacao(vetorLaboratorios, quantLaboratorios);
                            break;
                    }
                } while (subOpc != 0);
                break;

            case 'E':  // gerir Equipamentos
                do
                {
                    subOpc = subMenuEquipamentos();
                    switch (subOpc)
                    {
                        case 1:  // Inserir/Inventariar Equipamento
                            listaEquipamentos(vetorEquipamentos, quantEquipamentos);
                            inserirEquipamento(vetorEquipamentos, &quantEquipamentos);
                            break;
                        case 2:  // Instalar o equipamento no laboratorio
                            printf("\n\nOPCAO EM IMPLEMENTACAO\n\n");
                            break;
                        case 3:  // Abate do equipamento
                            printf("\n\nOPCAO EM IMPLEMENTACAO\n\n");
                            break;
                        case 4:   // Alterar Equipamento
                            alterarEquipamento(vetorEquipamentos, quantEquipamentos);
                            break;
                        case 5:  // Listar TODOS os equipamentos
                            listaEquipamentos(vetorEquipamentos, quantEquipamentos);
                            break;
                        case 6:  // Listar Equipamentos por LAboratorio
                            printf("\n\nOPCAO EM IMPLEMENTACAO\n\n");
                            break;
                        case 7:  // Listar Equipamentos Avariados
                            printf("\n\nOPCAO EM IMPLEMENTACAO\n\n");
                            break;
                        case 8:  // Consultar Equipamento pelo numero de invent�rio
                            consultaEquipamentoNrInventario(vetorEquipamentos, quantEquipamentos);
                            break;
                    }
                } while (subOpc != 0);
                break;

            case 'A':  // gerir Avarias
                do
                {
                    subOpc = subMenuAvarias();
                    switch (subOpc)
                    {
                        case 1: // Registar Avaria
                            printf("\n\nOPCAO EM IMPLEMENTACAO\n\n");
                            break;
                        case 2:  // Eliminar avaria
                            printf("\n\nOPCAO EM IMPLEMENTACAO\n\n");
                            break;
                        case 3:   // Alterar o estado da avaria
                            printf("\n\nOPCAO EM IMPLEMENTACAO\n\n");
                            break;
                        case 4:   // Listar avarias
                            printf("\n\nOPCAO EM IMPLEMENTACAO\n\n");
                            break;
                        case 5:  // Consultar avarias - pelo nr da avaria
                            printf("\n\nOPCAO EM IMPLEMENTACAO\n\n");
                            break;
                        case 6:   // Consultar avarias - pelo nr. de invent�rio do equipamento
                            printf("\n\nOPCAO EM IMPLEMENTACAO\n\n");
                            break;
                        case 7:  // Consultar avarias - por data
                            break;
                    }
                } while (subOpc != 0);
                break;

            case 'T':  // ESTATISTICAS
                printf("\n\nOPCAO EM IMPLEMENTACAO\n\n");
                break;

            case 'F':
                guardarFicheiro(vetorLaboratorios, quantLaboratorios, vetorEquipamentos, quantEquipamentos);
                break;
            case 'R':
                lerFicheiro(vetorLaboratorios, &quantLaboratorios, vetorEquipamentos, &quantEquipamentos);
                break;
            case 'S':
                break;
        }

    }
    while (opc != 'S');

    return 0;
}


// Fun��o para calcular o total de postos de trabalho
int calculos (tipoLaboratorio vetorLaboratorios[MAX_LABORATORIOS], int quantLaboratorios)
{
    int i, quantPostosTrabalho;

    quantPostosTrabalho = 0;

    for (i=0; i < quantLaboratorios; i++)
    {
        (quantPostosTrabalho) += vetorLaboratorios[i].numPostosTrabalho;
    }

    return quantPostosTrabalho;
}


// -------------------------------- FUN��ES GERIR EQUIPAMENTOS ---------------------------------

// Fun��o que permite inserir/inventariar um equipamento no vetor
void inserirEquipamento (tipoEquipamento vetorEquipamentos[MAX_EQUIPAMENTOS], int *quantEquipamentos)
{
    int posicao;

    if (*quantEquipamentos == MAX_EQUIPAMENTOS)
    {
        printf("\n\nATENCAO: Impossivel inserir um novo Equipamento (MAXIMO atingido).\n");
    }
    else
    {
        do{
            printf("\n\n----------- INSERIR/INVENTARIAR EQUIPAMENTO -----------  \n");
            vetorEquipamentos[*quantEquipamentos].numInventario = lerInteiro("\nNumero de inventario: ", 1, INT_MAX);

            posicao = procuraEquipamento(vetorEquipamentos, *quantEquipamentos, vetorEquipamentos[*quantEquipamentos].numInventario);

            if (posicao == NAO_EXISTE)  // Equipamento n�o existe no vetor
            {
                printf("\nData de Inventariacao: ");
                vetorEquipamentos[*quantEquipamentos].dataInventario = lerData();
                lerString("\nDescricao do Equipamento: ", vetorEquipamentos[*quantEquipamentos].descricao, TEXTO_LONGO);
                lerString("\nNumero de Serie: ", vetorEquipamentos[*quantEquipamentos].numSerie, TEXTO_BREVE);
                strcpy(vetorEquipamentos[*quantEquipamentos].local, LOCAL_INVENTARIO);
                vetorEquipamentos[*quantEquipamentos].estado = ESTADO_DISPONIVEL;
                vetorEquipamentos[*quantEquipamentos].custo = lerFloat("\nCusto do Equipamento: ", 0.0, CUSTO_MAX);
                (*quantEquipamentos)++;
            }
            else
            {
                printf("\n\nATENCAO: O equipamento nr. %d ja existe. Escolha outro numero para o inventario.\n", vetorEquipamentos[*quantEquipamentos].numInventario);
            }
        } while (posicao != NAO_EXISTE);
    }
}


// Fun��o que permite alterar alguns campos do equipamento
void alterarEquipamento (tipoEquipamento vetorEquipamentos[MAX_EQUIPAMENTOS], int quantEquipamentos)
{
    int posicao, opc, nrInventario;

    if (quantEquipamentos == 0)
    {
        printf("\n\nATENCAO: nao existem equipamentos inseridos.\n");
    }
    else
    {
        listaEquipamentos(vetorEquipamentos, quantEquipamentos);
        printf("\n\n-------------- ALTERAR EQUIPAMENTO --------------  \n");
        nrInventario =  lerInteiro("\nNr. de Inventario do equipamento que pertende alterar (digite 0 para cancelar): ", 0, INT_MAX);

        if (nrInventario == 0)
        {
            printf("\n\nATENCAO: operacao de alteracao cancelada.\n\n");
        }
        else
        {
            posicao = procuraEquipamento(vetorEquipamentos, quantEquipamentos, nrInventario);

            if (posicao == NAO_EXISTE)  // Equipamento n�o existe no vetor
            {
                printf("\n\nATENCAO: O equipamento com nr. de inventario %d nao existe.\n", nrInventario);
            }
            else  // O Laboratorio foi encontrado
            {
                opc = menuAlterarEquipamento();
                switch (opc)
                {
                    case 1: // alterar Data do Invent�rio
                        printf("\nNova data do inventario: ");
                        vetorEquipamentos[posicao].dataInventario = lerData();
                        break;

                    case 2:  // alterar Descri��o
                        lerString("\nNova Descricao: ", vetorEquipamentos[posicao].descricao, TEXTO_LONGO);
                        break;

                    case 3:   // alterar numero de serie
                        lerString("\nNovo Nr. de Serie: ", vetorEquipamentos[posicao].numSerie, TEXTO_BREVE);
                        break;

                    case 4:   // alterar o custo
                        vetorEquipamentos[posicao].custo = lerFloat("\nNovo custo: ", 0, CUSTO_MAX);
                        break;
                }
            }
        }
    }
}


//Fun��o que procura, atrav�s do numero do invent�rio, se o equipamento j� existe no vetor
int procuraEquipamento (tipoEquipamento vetorEquipamentos[MAX_EQUIPAMENTOS], int quantEquipamentos, int numInventario)
{
    int posicao, i;

    posicao=NAO_EXISTE;

    for (i=0; i < quantEquipamentos; i++)
    {
        if (vetorEquipamentos[i].numInventario == numInventario)
        {
            posicao = i;
            i = quantEquipamentos;
        }
    }

    return posicao;
}

// Fun��o que lista todos os equipamentos registados no vetor
void listaEquipamentos (tipoEquipamento vetorEquipamentos[MAX_EQUIPAMENTOS], int quantEquipamentos)
{
    int i;

    if (quantEquipamentos == 0)
    {
        printf("\n\nATENCAO: nao existem equipamentos inseridos.\n");
    }
    else
    {
        printf("\n\n----------------------------------------- LISTAGEM DE EQUIPAMENTOS ----------------------------------------- \n");

        for (i=0; i < quantEquipamentos; i++)
        {
            escreveDadosEquipamento(vetorEquipamentos[i], i);
        }
    }
}

// Fun��o que escreve no ecra os dados de um equipamento fornecido. O par�metro cabe�alho permite a fun��o escrever ou n�o escrever os t�tulos para a listagem
void escreveDadosEquipamento (tipoEquipamento equipamento, int cabecalho)
{
    if (cabecalho == 0)
    {
        printf("\nNr.Inv.\tData \t\tDescricao  \tNr. de Serie  \tLocal  \t\t\tEstado\t\t\tCusto \n");
        printf("___________________________________________________________________________________________________________\n");
    }

    printf("%6d\t", equipamento.numInventario);
    escreveData(equipamento.dataInventario);
    printf("\t%12s\t%13s\t%18s", equipamento.descricao, equipamento.numSerie, equipamento.local);
    switch (equipamento.estado)
    {
        case ESTADO_DISPONIVEL:
            printf("\tDisponivel");
            break;
        case ESTADO_INDISPONIVEL:
            printf("\tIndisponivel");
            break;
        case ESTADO_ABATIDO:
            printf("\tAbatido");
    }
    printf("\t%9.2f\n", equipamento.custo);
}


// Fun��o que escreve no ecra os dados de um equipamento selecionado pelo utlizador atrav�s do campo nr. de invent�rio
void consultaEquipamentoNrInventario (tipoEquipamento vetorEquipamentos[MAX_EQUIPAMENTOS], int quantEquipamentos)
{
    int posicao, numInventario;

    if (quantEquipamentos == 0)
    {
        printf("\n\nATENCAO: nao existem Equipamentos inseridos.\n");
    }
    else
    {
        printf("\n\n----------- CONSULTA EQUIPAMENTO -----------  \n");
        numInventario = lerInteiro("\nNr. do inventario: ", 1, INT_MAX);

        posicao = procuraEquipamento(vetorEquipamentos, quantEquipamentos, numInventario);

        if (posicao == NAO_EXISTE)  // Equipamento n�o existe no vetor
        {
            printf("\n\nATENCAO: O Equipamento com o nr %d nao existe.\n", numInventario);
        }
        else
        {
            escreveDadosEquipamento(vetorEquipamentos[posicao], 0);
        }
    }
}


// -------------------------------- FUN��ES GERIR LABORATORIO ---------------------------------

// Fun��o que permite inserir/registar um novo laborat�rio
void inserirLaboratorio (tipoLaboratorio vetorLaboratorios[MAX_LABORATORIOS], int *quantLaboratorios)
{
    int posicao;


    if (*quantLaboratorios == MAX_LABORATORIOS)
    {
        printf("\n\nATENCAO: Impossivel inserir um novo laboratorio (MAXIMO atingido).\n");
    }
    else
    {
        printf("\n\n-------------- INSERIR LABORATORIO --------------  \n");
        lerString("\nDesignacao: ", vetorLaboratorios[*quantLaboratorios].designacao, TEXTO_BREVE);

        posicao = procuraLaboratorio(vetorLaboratorios, *quantLaboratorios, vetorLaboratorios[*quantLaboratorios].designacao);
        if (posicao == NAO_EXISTE)  // Laborat�rio n�o existe no vetor
        {
            lerString("Localizacao: ", vetorLaboratorios[*quantLaboratorios].localizacao, TEXTO_BREVE);
            vetorLaboratorios[*quantLaboratorios].numPostosTrabalho = lerInteiro("Nr. Postos de trabalho: ", POSTO_TRABALHO_MIN, POSTO_TRABALHO_MAX);
            vetorLaboratorios[*quantLaboratorios].quantEquipamentosInstalados = 0;
            (*quantLaboratorios)++;
        }
        else
        {
            escreveDadosLaboratorio(vetorLaboratorios[posicao], 0);
            printf("\n\nATENCAO: O laboratorio %s ja existe.\n", vetorLaboratorios[*quantLaboratorios].designacao);
        }
    }
}

// fun��o que procura um laborat�rio tendo em conta a sua designa��o
int procuraLaboratorio (tipoLaboratorio vetorLaboratorios[MAX_LABORATORIOS], int quantLaboratorios, char designacao[TEXTO_BREVE])
{
    int posicao, i;

    posicao=NAO_EXISTE;

    for (i=0; i < quantLaboratorios; i++)
    {
        if (strcmp(vetorLaboratorios[i].designacao, designacao) == 0)
        {
            posicao = i;
            i = quantLaboratorios;
        }
    }

    return posicao;
}


// Fun��o que permite alterar os campos do laborat�rio
void alterarLaboratorio (tipoLaboratorio vetorLaboratorios[MAX_LABORATORIOS], int quantLaboratorios)
{
    int posicao, opc;
    char designacao[TEXTO_BREVE], novoTexto[TEXTO_BREVE];

    if (quantLaboratorios == 0)
    {
        printf("\n\nATENCAO: nao existem laboratorios inseridos.\n");
    }
    else
    {
        listaLaboratorios(vetorLaboratorios, quantLaboratorios);
        printf("\n\n-------------- ALTERAR LABORATORIO --------------  \n");
        lerString("\nDesignacao do laboratorio que pertende alterar (digite 0 para cancelar): ", designacao, TEXTO_BREVE);
        if (strcmp(designacao, "0")==0)  // O utilizador cancelou a opera��o de altera��oA
        {
            printf("\n\nATENCAO: operacao cancelada\n\n");
        }
        else
        {
            posicao = procuraLaboratorio(vetorLaboratorios, quantLaboratorios, designacao);

            if (posicao == NAO_EXISTE)  // Laborat�rio n�o existe no vetor
            {
                printf("\n\nATENCAO: O laboratorio %s nao existe.\n", designacao);
            }
            else  // O Laboratorio foi encontrado
            {
                opc = menuAlterarLaboratorio();
                switch (opc)
                {

                    case 1:  // alterar Localiza��o
                        lerString("\nNova Localizacao: ", novoTexto, TEXTO_BREVE);
                        strcpy(vetorLaboratorios[posicao].localizacao, novoTexto);
                        break;
                    case 2:   // alterar numero de postos de trabalho
                        vetorLaboratorios[posicao].numPostosTrabalho = lerInteiro("\nNova quantidade de postos de trabalho: ", POSTO_TRABALHO_MIN, POSTO_TRABALHO_MAX);
                        break;
                }
            }
        }
    }
}



// Fun��o que escreve no ecra os dados do laborat�rio passado por par�metro. O par�metro cabe�alho � uma flag que indica se os t�tulos da listagem s�o ou n�o escritos no ecra
void escreveDadosLaboratorio (tipoLaboratorio laboratorio, int cabecalho)
{
    if (cabecalho == 0)
    {
        printf("\n  Designacao \t    Localizacao \tPostos Trabalho\t  Equip.Instalados\n");
        printf("____________________________________________________________________________\n");
    }

    printf("\n%10s\t%15s\t%15d\t %15d", laboratorio.designacao, laboratorio.localizacao, laboratorio.numPostosTrabalho, laboratorio.quantEquipamentosInstalados);
}


// Fun��o que lista no ecra todos os laborat�rios registados
void listaLaboratorios (tipoLaboratorio vetorLaboratorios[MAX_LABORATORIOS], int quantLaboratorios)
{
    int i;

    if (quantLaboratorios == 0)
    {
        printf("\n\nATENCAO: nao existem laboratorios inseridos.\n");
    }
    else
    {
        printf("\n\n------------------------- LISTAGEM DE LABORATORIOS -------------------------  \n");

        for (i=0; i < quantLaboratorios; i++)
        {
            escreveDadosLaboratorio(vetorLaboratorios[i], i);
        }
    }
}


// Fun��o que escreve no ecra os dados de um laborat�rio selecionado pelo utlizador atrav�s do campo designacao
void consultaLaboratorioDesignacao (tipoLaboratorio vetorLaboratorios[MAX_LABORATORIOS], int quantLaboratorios)
{
    int posicao;
    char designacao[TEXTO_BREVE];

    if (quantLaboratorios == 0)
    {
        printf("\n\nATENCAO: nao existem laboratorios inseridos.\n");
    }
    else
    {
        listaLaboratorios(vetorLaboratorios, quantLaboratorios);
        printf("\n\n----------- CONSULTA LABORATORIO -----------  \n");
        lerString("\nDesignacao do laboratorio: ", designacao, TEXTO_BREVE);

        posicao = procuraLaboratorio(vetorLaboratorios, quantLaboratorios, designacao);

        if (posicao == NAO_EXISTE)  // Laborat�rio n�o existe no vetor
        {
            printf("\n\nATENCAO: O laboratorio %s nao existe.\n", designacao);
        }
        else
        {
            escreveDadosLaboratorio(vetorLaboratorios[posicao], 0);
        }
    }
}



// -------------- FUN��ES LER e ESCREVER FICHEIRO ----------------

// Fun��o que guarda os dados dos vetores dos laborat�rios e dos equipamentos num ficheiro
void guardarFicheiro (tipoLaboratorio vetorLaboratorios[MAX_LABORATORIOS], int quantLaboratorios, tipoEquipamento vetorEquipamentos[MAX_EQUIPAMENTOS], int quantEquipamentos)
{
    FILE *ficheiro;
    int elementosGuardados;

    ficheiro = fopen("dadoBin.dat", "wb");

    if (ficheiro == NULL)
    {
        printf("\nERRO: falha na abertura do ficheiro.\n");
    }
    else
    {
        elementosGuardados = fwrite(&quantLaboratorios, sizeof(int), 1, ficheiro);
        if (elementosGuardados != 1)
        {
            printf("\nERRO: falha na gravacao do numero de laboratorios inseridos.\n");
        }
        else
        {
            elementosGuardados = fwrite(vetorLaboratorios, sizeof (tipoLaboratorio), quantLaboratorios, ficheiro);
            if (elementosGuardados != quantLaboratorios)
            {
                printf("\nERRO: falha na gravacao dos dados dos laboratorios inseridos.\n");
            }
            else
            {
                elementosGuardados = fwrite(&quantEquipamentos, sizeof(int), 1, ficheiro);
                if (elementosGuardados != 1)
                {
                    printf("\nERRO: falha na gravacao do numero de Equipamentos inseridos.\n");
                }
                else
                {
                    elementosGuardados = fwrite(vetorEquipamentos, sizeof(tipoEquipamento), quantEquipamentos, ficheiro);
                    if (elementosGuardados != quantEquipamentos)
                    {
                         printf("\nERRO: falha na gravacao dos dados dos equipamentos inseridos.\n");
                    }
                }
            }
        }
        fclose(ficheiro);
    }
}

// Fun��o que l� do ficheiro os dados dos laborat�rios e dos equipamentos e os guarda nos repetivos vetores
void lerFicheiro (tipoLaboratorio vetorLaboratorios[MAX_LABORATORIOS], int *quantLaboratorios, tipoEquipamento vetorEquipamentos[MAX_EQUIPAMENTOS], int *quantEquipamentos)
{
    FILE *ficheiro;
    int elementosGuardados;

    *quantEquipamentos = 0;
    *quantLaboratorios = 0;

    ficheiro = fopen("dadoBin.dat", "rb");

    if (ficheiro == NULL)
    {
        printf("\nERRO: falha na abertura do ficheiro.\n");
    }
    else
    {
        elementosGuardados = fread(quantLaboratorios, sizeof(int), 1, ficheiro);
        if (elementosGuardados != 1)
        {
            printf("\nERRO: falha na leitura do numero de laboratorios inseridos.\n");
        }
        else
        {
            elementosGuardados = fread(vetorLaboratorios, sizeof (tipoLaboratorio), *quantLaboratorios, ficheiro);
            if (elementosGuardados != *quantLaboratorios)
            {
                printf("\nERRO: falha na leitura dos dados dos laboratorios inseridos.\n");
                *quantLaboratorios = 0;
            }
            else
            {
                elementosGuardados = fread(quantEquipamentos, sizeof(int), 1, ficheiro);
                if (elementosGuardados != 1)
                {
                    printf("\nERRO: falha na leitura do numero de Equipamentos inseridos.\n");
                }
                else
                {
                    elementosGuardados = fread(vetorEquipamentos, sizeof(tipoEquipamento), *quantEquipamentos, ficheiro);
                    if (elementosGuardados != *quantEquipamentos)
                    {
                         printf("\nERRO: falha na leitura dos dados dos equipamentos inseridos.\n");
                         *quantEquipamentos = 0;
                    }
                }
            }
        }
        fclose(ficheiro);
    }
}


// -------------- FUN��ES GESTAO da DATA  ----------------

void escreveData (tipoData data)
{
    printf("%02d-%02d-%4d", data.dia, data.mes, data.ano);
}

tipoData lerData (void)
{
    tipoData data;
    int diaMax;

    data.ano = lerInteiro("\nAno: ", ANO_MIN, ANO_MAX);
    data.mes = lerInteiro("Mes: ", 1, 12);

    switch (data.mes)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            diaMax = 31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            diaMax = 30;
            break;
        case 2:
            if (data.ano % 400 == 0 || (data.ano % 4 == 0 && data.ano % 100 != 0))
            {

                diaMax = 29;
            }
            else
            {
                diaMax = 28;
            }
    }

    data.dia = lerInteiro("Dia: ", 1, diaMax);

    return data;
}
