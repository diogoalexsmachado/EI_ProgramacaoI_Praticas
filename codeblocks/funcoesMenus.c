#include <stdio.h>
#include <ctype.h>

#include "funcoesMenus.h"
#include "funcoesAuxiliares.h"

char menu (int quantVeiculos, int quantEncomendas, float percEncomendasEntregues, int quantEncomendasDevolvidas)
{
    char opc;
    printf("\n\n\n\n-------------------------------------------------------------------------\n");
    printf("# Veiculos: %d\t\t# Encomendas Devolvidas: %d\n", quantVeiculos, quantEncomendasDevolvidas);
    printf("# Encomendas: %d\t\t# Percentagem Encomendas Entregues: %.2f%%\n", quantEncomendas, percEncomendasEntregues);
    printf("\n\n------------ MENU PRINCIPAL ---------------------------------------------\n");
    printf("\n\tV - Gerir Veiculos\n");
    printf("\tE - Gerir Encomendas\n");
    printf("\tR - Registos\n");
    printf("\tD - Dados Estatisticos\n");
    printf("\n\tG - Guardar no Ficheiro\n");
    printf("\tL - Ler do Ficheiro\n");
    printf("\n\tS - Sair do Programa\n");
    do
    {
        printf("\n\t\tOPCAO --> ");
        scanf(" %c", &opc);
        opc = toupper(opc);
        if (opc != 'V' && opc != 'E' && opc != 'S' && opc != 'G' && opc != 'L' && opc != 'R' && opc != 'D')
        {
            printf("\nERRO: opcao desconhecida. Tente novamente.\n");
        }
    }
    while (opc != 'V' && opc != 'E' && opc != 'S' && opc != 'G' && opc != 'L' && opc != 'R' && opc != 'D');
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

char menuEstatisticas ()
{
    char opc;
    printf("\n\n\n\n-------------------------------------------------------------------------\n");
    printf("\n\n------------ MENU ESTATISTICAS ---------------------------------------------\n\n");
    printf("\t1 - Peso medio das encomendas\n");
    printf("\t2 - Quantidade de encomendas entregues numa determinada data\n");
    printf("\t3 - Carga média dos veículos em viagem\n");
    printf("\t4 - Matrícula do(s) veículo(s) com menos viagens efetuadas\n");
    printf("\t5 - Destino(s) com maior quantidade de encomendas entregues\n\n");
    printf("\n\t0 - VOLTAR ATRAS\n");
    opc = lerInteiro("\n\t\tOPCAO --> ", 0, 4);
    return opc;
}