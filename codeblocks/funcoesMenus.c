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
