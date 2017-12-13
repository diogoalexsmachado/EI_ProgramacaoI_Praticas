#include <stdio.h>
#include <ctype.h>

#include "funcoesMenus.h"
#include "funcoesAuxiliares.h"


// -------------- FUNÇÕES DE MENU ----------------

char menu ()
{
    char opc;

    printf("\n\n\n\n-------------------------------------------------------------------------\n");
    printf("\n\n------------ MENU PRINCIPAL ---------------------------------------------\n");
    printf("\n\tV - Gerir Veiculos\n");
    printf("\tE - Gerir Encomendas\n");

    printf("\n\tF - Guardar no Ficheiro\n");
    printf("\tR - Ler do Ficheiro\n");
    printf("\n\tS - Sair do Programa\n");
    do
    {

        printf("\n\t\tOPCAO --> ");
        scanf(" %c", &opc);
        opc = toupper(opc);

        if (opc != 'V' && opc != 'E' && opc != 'S' && opc != 'F' && opc != 'R')
        {
            printf("\nERRO: opcao desconhecida. Tente novamente.\n");
        }
    }
    while (opc != 'G' && opc != 'E' && opc != 'S' && opc != 'F' && opc != 'R');

    return opc;
}


char menuVeiculos ()
{
    char opc;

    printf("\n\n\n\n-------------------------------------------------------------------------\n");
    printf("\n\n------------ MENU VEICULOS---------------------------------------------\n");
    printf("\n\tI - Inserir Veiculo\n");
    printf("\tC - Consultar Veiculo\n");
    printf("\tL - Listar Veiculos\n");

    printf("\n\tX - VOLTAR ATRAS\n");

    do
    {

        printf("\n\t\tOPCAO --> ");
        scanf(" %c", &opc);
        opc = toupper(opc);

        if (opc != 'V' && opc != 'E' && opc != 'S' && opc != 'F' && opc != 'R')
        {
            printf("\nERRO: opcao desconhecida. Tente novamente.\n");
        }
    }
    while (opc != 'G' && opc != 'E' && opc != 'S' && opc != 'F' && opc != 'R');

    return opc;
}

char menuEncomendas ()
{
    char opc;

    printf("\n\n\n\n-------------------------------------------------------------------------\n");
    printf("\n\n------------ MENU ENCOMENDAS---------------------------------------------\n");
    printf("\n\tI - Inserir Encomenda\n");
    printf("\tC - Consultar Encomenda\n");
    printf("\tL - Listar Encomendas\n");
    printf("\tE - Eliminar Encomenda\n");
    printf("\tA - Alterar Destino Encomenda\n");

    printf("\n\tX - VOLTAR ATRAS\n");

    do
    {

        printf("\n\t\tOPCAO --> ");
        scanf(" %c", &opc);
        opc = toupper(opc);

        if (opc != 'V' && opc != 'E' && opc != 'S' && opc != 'F' && opc != 'R')
        {
            printf("\nERRO: opcao desconhecida. Tente novamente.\n");
        }
    }
    while (opc != 'G' && opc != 'E' && opc != 'S' && opc != 'F' && opc != 'R');

    return opc;
}

char menuRegistos ()
{
    char opc;

    printf("\n\n\n\n-------------------------------------------------------------------------\n");
    printf("\n\n------------ MENU REGISTOS ---------------------------------------------\n");
    printf("\n\tC - Carregamento de Encomendas\n");
    printf("\tI - Inicio de Viagem\n");
    printf("\tR - Regresso de Viagem\n");
    printf("\tD - Descarregamento de Encomendas\n");

    printf("\n\tX - VOLTAR ATRAS\n");

    do
    {

        printf("\n\t\tOPCAO --> ");
        scanf(" %c", &opc);
        opc = toupper(opc);

        if (opc != 'V' && opc != 'E' && opc != 'S' && opc != 'F' && opc != 'R')
        {
            printf("\nERRO: opcao desconhecida. Tente novamente.\n");
        }
    }
    while (opc != 'G' && opc != 'E' && opc != 'S' && opc != 'F' && opc != 'R');

    return opc;
}
