#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define NAO_EXISTE -1    // Valor devolvido pelas fun��es procurar(...) quando o laborat�rio, equipamento ou avaria n�o existem no respetivo vetor
#define ESTADO_DISPONIVEL -1

#define ANO_MIN 1900
#define ANO_MAX 2500

#include "funcoesMenus.h"
#include "funcoesAuxiliares.h"

#define MAX_VEICULOS 10
#define MAX_ENCOMENDAS 100

typedef struct //tipoData
{
    int dia, mes, ano;
} tipoData;

typedef struct //tipoVeiculo
{
    char matricula[TEXTO_BREVE]; // valor �nico
    tipoData dataFabrico;
    int cargaMaxima;
    char estado[TEXTO_BREVE];
} tipoVeiculo;

typedef struct //encomendas
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
void inserirVeiculo (tipoVeiculo vetorVeiculos[MAX_VEICULOS], int *quantVeiculos);
int procuraVeiculo (tipoVeiculo vetorVeiculos[MAX_VEICULOS], int quantVeiculos, char matricula[8]);

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
                    break;
                case 3: //listar veiculos
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

            //strcpy(vetorVeiculos[*quantVeiculos].matricula, lerMatricula("\nMATRICULA: ", vetorVeiculos[*quantVeiculos].matricula));

            posicao = procuraVeiculo(vetorVeiculos, *quantVeiculos, vetorVeiculos[*quantVeiculos].matricula);

            if (posicao == NAO_EXISTE)  // Equipamento n�o existe no vetor
            {

                lerMatricula("\nMATRICULA: ", vetorVeiculos[*quantVeiculos].matricula);
                printf("\nData de Fabrico: ");
                vetorVeiculos[*quantVeiculos].dataFabrico = lerData();
                vetorVeiculos[*quantVeiculos].cargaMaxima = lerInteiro("\nCarga mazima: ", 0, 9999);
                strcpy(vetorVeiculos[*quantVeiculos].estado, ESTADO_DISPONIVEL);
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
