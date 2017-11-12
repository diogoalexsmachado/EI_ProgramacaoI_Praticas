#include <stdio.h>
#include <stdlib.h>

#define MAX_VEICULOS 10
#define MAX_ENCOMENDAS 100

#define TEXTO_BREVE 32
#define TEXTO_LONGO 256


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
    int input=0;
    printf("Escreve:");
    scanf("%d", &input);
    printf("O teu input: %d\n", input);
    return 0;
}
