#include <stdio.h>
#include <ctype.h>

#include "funcoesMenus.h"
#include "funcoesAuxiliares.h"

char menu ()
{
    char opc;
    printf("\n\n\n\n-------------------------------------------------------------------------\n");
    printf("\n\n------------ MENU PRINCIPAL ---------------------------------------------\n");
    printf("\n\tV - Gerir Veiculos\n");
    printf("\tE - Gerir Encomendas\n");
    printf("\tR - Registos\n");
    printf("\n\tG - Guardar no Ficheiro\n");
    printf("\tL - Ler do Ficheiro\n");
    printf("\n\tS - Sair do Programa\n");
    do
    {
        printf("\n\t\tOPCAO --> ");
        scanf(" %c", &opc);
        opc = toupper(opc);
        if (opc != 'V' && opc != 'E' && opc != 'S' && opc != 'G' && opc != 'L' && opc != 'R')
        {
            printf("\nERRO: opcao desconhecida. Tente novamente.\n");
        }
    }
    while (opc != 'V' && opc != 'E' && opc != 'S' && opc != 'G' && opc != 'L' && opc != 'R');
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
    printf("\n\n------------ MENU REGISTOS ---------------------------------------------\n\n");
    printf("\t1 - Carregamento de Encomendas\n");
    printf("\t2 - Inicio de Viagem\n");
    printf("\t3 - Regresso de Viagem\n");
    printf("\t4 - Descarregamento de Encomendas\n");
    printf("\n\t0 - VOLTAR ATRAS\n");
    opc = lerInteiro("\n\t\tOPCAO --> ", 0, 4);
    return opc;
}
