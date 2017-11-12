#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "funcoesMenus.h"
#include "funcoesAuxiliares.h"

#define MAX_VEICULOS 10
#define MAX_ENCOMENDAS 100

typedef struct
{
    int dia, mes, ano;
} tipoData;

typedef struct
{
    char matricula[TEXTO_BREVE];   // valor �nico
    tipoData dataFabrico;
    int cargaMaxima;
    char estado[TEXTO_BREVE];
} tipoVeiculo;

typedef struct
{
    int numeroRegisto;   // valor �nico
    tipoData dataRegisto;
    int pesoEncomenda;
    char estado[TEXTO_BREVE];
    tipoData dataEntregaOuDevolucao;
    char observacoesEncomenda[TEXTO_LONGO];
} tipoEncomenda;


int main(void)
{
  tipoVeiculo vetorVeiculos[MAX_VEICULOS];
  tipoEncomenda vetorEncomendas[MAX_ENCOMENDAS];

  char opc;


  opc = menu();
  switch (opc) {
    case 'V': //TODO submenuVeiculos
      break;
    case 'E': //TODO submenu encomendas
      break;

  }

}
