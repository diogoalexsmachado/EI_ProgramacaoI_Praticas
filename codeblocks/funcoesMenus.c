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
    while (opc != 'V' && opc != 'E' && opc != 'S' && opc != 'F' && opc != 'R');

    return opc;
}


char menuVeiculos ()
{
    char opc;

    printf("\n\n\n\n-------------------------------------------------------------------------\n");
    printf("\n\n------------ MENU VEICULOS---------------------------------------------\n");
    printf("\n\t1 - Inserir Veiculo\n");
    printf("\t2 - Consultar Veiculo\n");
    printf("\t3 - Listar Veiculos\n");
    printf("\n\t0 - VOLTAR ATRAS\n");

    opc = lerInteiro("\n\t\tOPCAO --> ", 0, 4);
    return opc;
}

char menuEncomendas ()
{
    char opc;

    printf("\n\n\n\n-------------------------------------------------------------------------\n");
    printf("\n\n------------ MENU ENCOMENDAS---------------------------------------------\n");
    printf("\n\t1 - Inserir Encomenda\n");
    printf("\t2 - Consultar Encomenda\n");
    printf("\t3 - Listar Encomendas\n");
    printf("\t4 - Eliminar Encomenda\n");
    printf("\t5 - Alterar Destino Encomenda\n");

    printf("\n\t0 - VOLTAR ATRAS\n");

    opc = lerInteiro("\n\t\tOPCAO --> ", 0, 5);

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
