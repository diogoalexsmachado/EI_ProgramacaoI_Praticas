#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define NAO_EXISTE -1    // Valor devolvido pelas fun��es procurar(...) quando o laborat�rio, equipamento ou avaria n�o existem no respetivo vetor
#define ESTADO_DISPONIVEL 1
#define ESTADO_INDISPONIVEL 0

#define ANO_MIN 1900
#define ANO_MAX 2500

#include "funcoesMenus.h"
#include "funcoesAuxiliares.h"

#define MAX_VEICULOS 10
#define MAX_ENCOMENDAS 100

//tipoData
typedef struct
{
    int dia, mes, ano;
} tipoData;

//tipoVeiculo
typedef struct
{
    char matricula[TEXTO_BREVE]; // valor �nico
    tipoData dataFabrico;
    int cargaMaxima;
    int estado;
} tipoVeiculo;

//tipoEncomenda
typedef struct
{
    int numeroRegisto; // valor �nico
    tipoData dataRegisto;
    int pesoEncomenda;
    char estado[TEXTO_BREVE];
    tipoData dataEntregaOuDevolucao;
    char observacoesEncomenda[TEXTO_LONGO];
} tipoEncomenda;

//Declaração das funções
tipoData lerData (void);
void escreveData (tipoData data);

void inserirVeiculo (tipoVeiculo vetorVeiculos[MAX_VEICULOS], int *quantVeiculos);
int procuraVeiculo (tipoVeiculo vetorVeiculos[MAX_VEICULOS], int quantVeiculos, char matricula[8]);
void listaVeiculos(tipoVeiculo vetorVeiculos[MAX_VEICULOS], int quantVeiculos);
void consultaVeiculo(tipoVeiculo vetorVeiculos[MAX_VEICULOS],int *quantVeiculos);

int main(void)
{
    tipoVeiculo vetorVeiculos[MAX_VEICULOS];
    tipoEncomenda vetorEncomendas[MAX_ENCOMENDAS];

    char opc;
    int subOpc, quantVeiculos, quantEncomendas;

    do
    {

        opc = menu();
        switch (opc)
        {
        case 'V':
            do
            {
                subOpc = menuVeiculos(); // chama o menu dos veiculos
                switch (subOpc)
                {
                case 1: // inserir veiculo
                    inserirVeiculo(vetorVeiculos, &quantVeiculos);
                    break;
                case 2: //consultar veiculo
                    consultaVeiculo(vetorVeiculos, &quantVeiculos);
                    break;
                case 3: //listar veiculos
                    listaVeiculos(vetorVeiculos, quantVeiculos);
                    break;
                }
            }
            while (subOpc != 0);
            break;
        case 'E':
            do
            {
                subOpc = menuEncomendas(); // chama o menu dos encomendas
                switch (subOpc)
                {
                case 1: // inserir encomenda
                    inserirEncomenda(vetorEncomendas, &quantEncomendas);
                    break;
                case 2: //consultar encomenda
                    break;
                case 3: //listar encomendas
                    break;
                case 4: //eliminar encomenda
                    break;
                case 5: //alterar destino encomenda
                    break;
                }
            }
            while (subOpc != 0);
            break;
        }
    }
    while (opc != 'S');
}

///////////////////////////////////////////FUNÇOES VEICULOS/////////////////////////////////////////////////////////
//Função que permite adicionar um veiculo se ele não existir
void inserirVeiculo (tipoVeiculo vetorVeiculos[MAX_VEICULOS], int *quantVeiculos)
{
    int posicao;

    if (*quantVeiculos == MAX_VEICULOS)
    {
        printf("\n\nATENCAO: Impossivel inserir um novo Veiculo (MAXIMO atingido).\n");
    }
    else
    {
        do
        {
            printf("\n\n----------- INSERIR/INVENTARIAR VEICULOS -----------  \n");
            lerMatricula("\nMATRICULA: ", vetorVeiculos[*quantVeiculos].matricula);

            posicao = procuraVeiculo(vetorVeiculos, *quantVeiculos, vetorVeiculos[*quantVeiculos].matricula);

            if (posicao == NAO_EXISTE)  // Equipamento n�o existe no vetor
            {

                printf("\nData de Fabrico: ");
                vetorVeiculos[*quantVeiculos].dataFabrico = lerData();
                vetorVeiculos[*quantVeiculos].cargaMaxima = lerInteiro("\nCarga maxima: ", 0, 9999);
                vetorVeiculos[*quantVeiculos].estado = ESTADO_DISPONIVEL;
                (*quantVeiculos)++;

            }
            else
            {
                printf("\n\nATENCAO: O veiculo com essa matricula ja existe: %s\n", vetorVeiculos[*quantVeiculos].matricula);
            }
        }
        while (posicao != NAO_EXISTE);
    }
}

//função para listar veiculos
void listaVeiculos(tipoVeiculo vetorVeiculos[MAX_VEICULOS], int quantVeiculos)
{
    int i;

    if (quantVeiculos == 0)
    {
        printf("\n\nATENCAO: nao existem equipamentos inseridos.\n");
    }
    else
    {
        printf("\n\n----------------------------------------- LISTAGEM DE VEICULOS ----------------------------------------- \n");

        for (i=0; i < quantVeiculos; i++)
        {
            escreveDadosVeiculo(vetorVeiculos[i], i);
        }
    }
}

//função para escrever os dados do veiculo
void escreveDadosVeiculo(tipoVeiculo veiculo, int cabecalho)
{
    if (cabecalho == 0)
    {
        printf("\nMatricula.\t\tData \t\tCarga  \tEstado\t\n");
        printf("__________________________________________________________\n");
    }

    printf("%8s\t\t\t", veiculo.matricula);
    escreveData(veiculo.dataFabrico);
    printf("\t%d", veiculo.cargaMaxima);
    switch (veiculo.estado)
    {
        case ESTADO_DISPONIVEL:
            printf("\tDisponivel\n");
            break;
        case ESTADO_INDISPONIVEL:
            printf("\tIndisponivel\n");
            break;
    }
}

void consultaVeiculo(tipoVeiculo vetorVeiculos[MAX_VEICULOS], int *quantVeiculos)
{
    int posicao;
    do
    {
        printf("\n\n----------- CONSULTAR VEICULO -----------  \n");
        lerMatricula("\nMATRICULA: ", vetorVeiculos[*quantVeiculos].matricula);

        posicao = procuraVeiculo(vetorVeiculos, *quantVeiculos, vetorVeiculos[*quantVeiculos].matricula);

        if (posicao == NAO_EXISTE)  // Equipamento n�o existe no vetor
        {
            printf("\n\nATENCAO: O veiculo com essa matricula não existe: %s\n", vetorVeiculos[*quantVeiculos].matricula);
        }
        else
        {
            printf("\nMatricula.\t\tData \t\tCarga  \tEstado\t\n");
            printf("__________________________________________________________\n");


            printf("%s\t\t\t", vetorVeiculos[posicao].matricula);
            escreveData(vetorVeiculos[posicao].dataFabrico);
            printf("\t%d", vetorVeiculos[posicao].cargaMaxima);
            switch (vetorVeiculos[posicao].estado)
            {
                case ESTADO_DISPONIVEL:
                    printf("\tDisponivel");
                    break;
                case ESTADO_INDISPONIVEL:
                    printf("\tIndisponivel");
                    break;
            }
        }
    }
    while (posicao != NAO_EXISTE);
}

//função para procurar veiculos e retorna a posição no vetor
int procuraVeiculo (tipoVeiculo vetorVeiculos[MAX_VEICULOS], int quantVeiculos, char matricula[8])
{
    int posicao, i;

    posicao=NAO_EXISTE;

    for (i=0; i < quantVeiculos; i++)
    {
        if (strcmp(vetorVeiculos[i].matricula,matricula) == 0)
        {
            posicao = i;
            i = quantVeiculos;
        }
    }

    return posicao;
}

///////////////////////////////////////////FUNÇOES VEICULOS/////////////////////////////////////////////////////////
//Função que permite adicionar uma encomenda se ela não existir
void inserirEncomenda (tipoEncomenda vetorEncomendas[MAX_ENCOMENDAS], int *quantEncomendas)
{
    int posicao;

    if (*quantEncomendas == MAX_ENCOMENDAS)
    {
        printf("\n\nATENCAO: Impossivel inserir uma nova encomenda (MAXIMO atingido).\n");
    }
    else
    {
        do
        {
            printf("\n\n----------- INSERIR/INVENTARIAR VEICULOS -----------  \n");
            vetorEncomendas[*quantEncomendas].numeroRegisto = lerInteiro("\nID ENCOMENDA: ", 1,16);

            posicao = procuraVeiculo(vetorEncomendas, *quantEncomendas, vetorEncomendas[*quantEncomendas].numeroRegisto);
/*
            if (posicao == NAO_EXISTE)  // Equipamento n�o existe no vetor
            {

                printf("\nData de Fabrico: ");
                vetorEncomendas[*quantEncomendas].dataFabrico = lerData();
                vetorEncomendas[*quantEncomendas].cargaMaxima = lerInteiro("\nCarga maxima: ", 0, 9999);
                vetorEncomendas[*quantEncomendas].estado = ESTADO_DISPONIVEL;
                (*quantEncomendas)++;

            }
            else
            {
                printf("\n\nATENCAO: O veiculo com essa matricula ja existe: %s\n", vetorEncomendas[*quantEncomendas].matricula);
            }*/
        }
        while (posicao != NAO_EXISTE);
    }
}

//função para procurar veiculos e retorna a posição no vetor
int procuraEncomenda(tipoEncomenda vetorEncomendas[MAX_ENCOMENDAS], int quantEncomendas, char numeroRegisto)
{
    int posicao, i;

    posicao=NAO_EXISTE;

    for (i=0; i < quantEncomendas; i++)
    {
        if (strcmp(vetorEncomendas[i].numeroRegisto,numeroRegisto) == 0)
        {
            posicao = i;
            i = quantEncomendas;
        }
    }

    return posicao;
}


///////////////////////////////////////////FUNÇOES GERAIS/////////////////////////////////////////////////////////
//função para escrever a data
void escreveData (tipoData data)
{
    printf("%02d-%02d-%4d", data.dia, data.mes, data.ano);
}

//função para ler a data
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
