#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define NAO_EXISTE -1    // Valor devolvido pelas fun��es procurar(...)
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
	int estado; //0- parado || 1 - em viagem || 2 - de regresso
} tipoVeiculo;

//tipoEncomenda
typedef struct
{
	int numeroRegisto; // valor unico
	tipoData dataRegisto;
	int pesoEncomenda;
	int estado; // 0 - por expedir || 1 - expedido || 2 - entregue || 3- - devolvido
	tipoData dataEntregaOuDevolucao;
	char destino[TEXTO_LONGO];
	char observacoesEncomenda[TEXTO_LONGO];
	int numeroMatricula;
} tipoEncomenda;

//Declaração das funções
float calculos(tipoEncomenda vetorEncomendas[MAX_ENCOMENDAS], int quantEncomendas);

tipoData lerData (void);
void escreveData (tipoData data);

void inserirVeiculo (tipoVeiculo vetorVeiculos[MAX_VEICULOS], int *quantVeiculos);
int procuraVeiculo (tipoVeiculo vetorVeiculos[MAX_VEICULOS], int quantVeiculos, char matricula[8]);
void escreveDadosVeiculo(tipoVeiculo veiculo, int cabecalho);
void listaVeiculos(tipoVeiculo vetorVeiculos[MAX_VEICULOS], int quantVeiculos);
void consultarVeiculo(tipoVeiculo vetorVeiculos[MAX_VEICULOS],int *quantVeiculos);
void declararInicioDeViagem(tipoVeiculo vetorVeiculos[MAX_VEICULOS],int quantVeiculos);
void declararRegressoDeViagem(tipoVeiculo vetorVeiculos[MAX_VEICULOS],int quantVeiculos);

void inserirEncomenda (tipoEncomenda vetorEncomendas[MAX_ENCOMENDAS], int *quantEncomendas);
void listaEncomendas(tipoEncomenda vetorEncomendas[MAX_ENCOMENDAS], int quantEncomendas);
void escreveDadosEncomenda(tipoEncomenda encomenda, int cabecalho);
int procuraEncomenda(tipoEncomenda vetorEncomendas[MAX_ENCOMENDAS], int quantEncomendas, int numReferencia);
void consultarEncomenda(tipoEncomenda vetorEncomendas[MAX_ENCOMENDAS], int *quantEncomendas);
void eliminarEncomenda(tipoEncomenda vetorEncomendas[MAX_ENCOMENDAS], int *quantEncomendas);
void alterarDestinoEncomenda(tipoEncomenda vetorEncomendas[MAX_ENCOMENDAS], int *quantEncomendas);

void pesoMedioEncomendas(tipoEncomenda vetorEncomendas[MAX_ENCOMENDAS], int quantEncomendas);
void destinosComMaisEncomendas(tipoEncomenda vetorEncomendas[MAX_ENCOMENDAS], int quantEncomendas);
void encomendaPorData (tipoEncomenda vetorEncomendas[MAX_ENCOMENDAS], int quantEncomendas);

void guardarFicheiro (tipoVeiculo vetorVeiculos[MAX_VEICULOS], int quantVeiculos, tipoEncomenda vetorEncomenda[MAX_ENCOMENDAS], int quantEncomendas);
void lerFicheiro (tipoVeiculo vetorVeiculos[MAX_VEICULOS], int *quantVeiculos, tipoEncomenda vetorEncomendas[MAX_ENCOMENDAS], int *quantEncomendas);

int main(void)
{
	tipoVeiculo vetorVeiculos[MAX_VEICULOS];
	tipoEncomenda vetorEncomendas[MAX_ENCOMENDAS];


	char opc;
	int subOpc, quantVeiculos = 0, quantEncomendas = 0, quantEncomendasDevolvidas = 0;
	float percEncomendasEntregues=0.0;

	do
	{
		percEncomendasEntregues=calculos(vetorEncomendas, quantEncomendas);
		opc = menu(quantVeiculos, quantEncomendas, percEncomendasEntregues, quantEncomendasDevolvidas);
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
					consultarVeiculo(vetorVeiculos, &quantVeiculos);
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
					consultarEncomenda(vetorEncomendas, &quantEncomendas);
					break;
				case 3: //listar encomendas
					listaEncomendas(vetorEncomendas, quantEncomendas);
					break;
				case 4: //eliminar encomenda
					eliminarEncomenda(vetorEncomendas, &quantEncomendas);
					break;
				case 5: //alterar destino encomenda
					alterarDestinoEncomenda(vetorEncomendas, &quantEncomendas);
					break;
				}
			}
			while (subOpc != 0);
			break;
		case 'R':
			do
			{
				subOpc = menuRegistos(); // chama o menu dos encomendas
				switch (subOpc)
				{
				case 1: // carregamento de encomendas
						
					break;
				case 2: // inicio de viagem
						declararInicioDeViagem(vetorVeiculos, quantVeiculos);
					break;
				case 3: // regresso de viagem
						declararRegressoDeViagem(vetorVeiculos, quantVeiculos);
					break;
				case 4: // descarregamento de encomendas

					break;
				}
			}
			while (subOpc != 0);
			break;
		case 'D':
			do
			{
				subOpc = menuEstatisticas(); // chama o menu dos encomendas
				switch (subOpc)
				{
				case 1: // peso medio das encomendas
					pesoMedioEncomendas(vetorEncomendas, quantEncomendas);
					break;
				case 2: // qtd de encomendas por veiculo

					break;
				case 3: // carga media dos veiculos em viagem

					break;
				case 4: // matricula dos veiculos com menos viagens feitas

					break;
				case 5: // destinos com mais encomendas
					destinosComMaisEncomendas(vetorEncomendas, quantEncomendas);
				break;
				case 6: //encomendas numa determinada data
					encomendaPorData(vetorEncomendas, quantEncomendas);
				break;
				}
			}
			while (subOpc != 0);
			break;
		case 'G': //guardar ficheiro
			guardarFicheiro(vetorVeiculos, quantVeiculos, vetorEncomendas, quantEncomendas);
			break;
		case 'L': //ler ficheiro
			lerFicheiro (vetorVeiculos, &quantVeiculos, vetorEncomendas, &quantEncomendas);
			break;
	}
	}
	while (opc != 'S');
}

//função que permite calcular dados estatisticos do menu principal
float calculos(tipoEncomenda vetorEncomendas[MAX_ENCOMENDAS], int quantEncomendas)
{
	int i, count = 0;
	float percEncomendasEntregues=0.0;
	for (i=0; i < quantEncomendas; i++)
	{
		if (vetorEncomendas[i].estado == 2)
		{
			count++;
		}
	}

	percEncomendasEntregues = (float) (count*100)/quantEncomendas;

	return percEncomendasEntregues;
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
			lerMatricula("\nMATRICULA: ", vetorVeiculos[*quantVeiculos].matricula, 0);

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
		printf("\n\nATENCAO: nao existem veiculos inseridos.\n");
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
		printf("\n\tMatricula.\t\tData \t\tCarga  \t\tEstado\t\n");
		printf("\t________________________________________________________________\n");
	}
	printf("\t%8s\t\t", veiculo.matricula);
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

//função para consultar veículo
void consultarVeiculo(tipoVeiculo vetorVeiculos[MAX_VEICULOS], int *quantVeiculos)
{
	int posicao;
	do
	{
		printf("\n\n----------- CONSULTAR VEICULO -----------  \n");
		lerMatricula("\nMATRICULA: ", vetorVeiculos[*quantVeiculos].matricula, 1);

		posicao = procuraVeiculo(vetorVeiculos, *quantVeiculos, vetorVeiculos[*quantVeiculos].matricula);

		if (posicao == NAO_EXISTE)  // Equipamento n�o existe no vetor
		{
			printf("\n\nATENCAO: O veiculo com essa matricula não existe: %s\n", vetorVeiculos[*quantVeiculos].matricula);
		}
		else
		{
			escreveDadosVeiculo(vetorVeiculos[posicao], 0);
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

void declararInicioDeViagem(tipoVeiculo vetorVeiculos[MAX_VEICULOS],int quantVeiculos)
{
	int posicao;
	do
	{
		printf("\n\n----------- INICIO VIAGEM -----------  \n");
		lerMatricula("\nMATRICULA: ", vetorVeiculos[quantVeiculos].matricula, 1);

		posicao = procuraVeiculo(vetorVeiculos, quantVeiculos, vetorVeiculos[quantVeiculos].matricula);

		if (posicao == NAO_EXISTE)  // matricula n�o existe no vetor
		{
			printf("\n\nATENCAO: O veiculo com essa matricula não existe: %s\n", vetorVeiculos[quantVeiculos].matricula);
		}
		else
		{
			vetorVeiculos[posicao].estado=1;
		}
	}
	while (posicao != NAO_EXISTE);
}

void declararRegressoDeViagem(tipoVeiculo vetorVeiculos[MAX_VEICULOS],int quantVeiculos)
{
	int posicao;
	do
	{
		printf("\n\n----------- INICIO VIAGEM -----------  \n");
		lerMatricula("\nMATRICULA: ", vetorVeiculos[quantVeiculos].matricula, 1);

		posicao = procuraVeiculo(vetorVeiculos, quantVeiculos, vetorVeiculos[quantVeiculos].matricula);

		if (posicao == NAO_EXISTE)  // matricula n�o existe no vetor
		{
			printf("\n\nATENCAO: O veiculo com essa matricula não existe: %s\n", vetorVeiculos[quantVeiculos].matricula);
		}
		else
		{
			vetorVeiculos[posicao].estado=2;
		}
	}
	while (posicao != NAO_EXISTE);
}

///////////////////////////////////////////FUNÇOES ENCOMENDAS/////////////////////////////////////////////////////////
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
			vetorEncomendas[*quantEncomendas].numeroRegisto = lerInteiro("\nNUM REGISTO: ", 1,MAX_ENCOMENDAS);

			posicao = procuraEncomenda(vetorEncomendas, *quantEncomendas, vetorEncomendas[*quantEncomendas].numeroRegisto);

			if (posicao == NAO_EXISTE)  // encomenda n�o existe no vetor
			{
				printf("\nData de Registo: ");
				vetorEncomendas[*quantEncomendas].dataRegisto = lerData();
				vetorEncomendas[*quantEncomendas].pesoEncomenda = lerInteiro("\nPeso Encomenda: ", 0, 9999);
				printf("\nData de Entrega: ");
				vetorEncomendas[*quantEncomendas].dataEntregaOuDevolucao = lerData();
				lerString("Destino: ", vetorEncomendas[*quantEncomendas].destino, TEXTO_LONGO);
					//TODO VERIFICAÇÃO IF MESMO DIA OU DEPOIS
				lerString("Observacoes: ", vetorEncomendas[*quantEncomendas].observacoesEncomenda, TEXTO_LONGO);
				(*quantEncomendas)++;
			}
			else
			{
				printf("\n\nATENCAO: A encomenda com esse num registo ja existe: %d\n", vetorEncomendas[*quantEncomendas].numeroRegisto);
			}
		}
		while (posicao != NAO_EXISTE);
	}
}

//função para listar encomendas
void listaEncomendas(tipoEncomenda vetorEncomendas[MAX_ENCOMENDAS], int quantEncomendas)
{
	int i;

	if (quantEncomendas == 0)
	{
		printf("\n\nATENCAO: nao existem encomendas inseridos.\n");
	}
	else
	{
		printf("\n\n-------------------------------------------- LISTAGEM DE ENCOMENDAS -------------------------------------------------- \n\n");

		for (i=0; i < quantEncomendas; i++)
		{
			escreveDadosEncomenda(vetorEncomendas[i], i);
		}
	}
}

//função para escrever os dados do encomenda
void escreveDadosEncomenda(tipoEncomenda encomenda, int cabecalho)
{
	if (cabecalho == 0)
	{
		printf("\tNUM.\t\tData Reg. \t\tPeso \t\tEstado\t\tData Entr.\tDestino\t\tObs\t\n");
		printf("\t___________________________________________________________________________________________________\n");
	}

	//TODO if observacoes mostrar asterisco

	printf("\t%d\t\t", encomenda.numeroRegisto);
	escreveData(encomenda.dataRegisto);
	printf("\t\t%d", encomenda.pesoEncomenda);
	switch (encomenda.estado)
	{
		case ESTADO_DISPONIVEL:
			printf("\t\tDisponivel\t");
			break;
		case ESTADO_INDISPONIVEL:
			printf("\t\tIndisponivel\t");
			break;
	}
	escreveData(encomenda.dataEntregaOuDevolucao);
	printf("\t%s", encomenda.destino);
	printf("\t\t%s\n\n", encomenda.observacoesEncomenda);
}

//função para procurar encomenda e retorna a posição no vetor
int procuraEncomenda(tipoEncomenda vetorEncomendas[MAX_ENCOMENDAS], int quantEncomendas, int numeroRegisto)
{
	int posicao, i;
	posicao=NAO_EXISTE;
	for (i=0; i < quantEncomendas; i++)
	{
		if (vetorEncomendas[i].numeroRegisto == numeroRegisto)
		{
			posicao = i;
			i = quantEncomendas;
		}
	}
	return posicao;
}

//função para consultar encomenda
void consultarEncomenda(tipoEncomenda vetorEncomendas[MAX_ENCOMENDAS], int *quantEncomendas)
{
	int posicao;
	do
	{
		printf("\n\n----------- CONSULTAR VEICULO -----------  \n");
		vetorEncomendas[*quantEncomendas].numeroRegisto = lerInteiro("\nNUM REGISTO: ", 1, MAX_ENCOMENDAS);

		posicao = procuraEncomenda(vetorEncomendas, *quantEncomendas, vetorEncomendas[*quantEncomendas].numeroRegisto);

		if (posicao == NAO_EXISTE)  // Encomenda n�o existe no vetor
		{
			printf("\n\nATENCAO: A encomenda com esse num de registo não existe: %d\n", vetorEncomendas[*quantEncomendas].numeroRegisto);
		}
		else
		{
			escreveDadosEncomenda(vetorEncomendas[posicao], 0);
		}
	}
	while (posicao != NAO_EXISTE);
}

//função para eliminar encomenda
void eliminarEncomenda(tipoEncomenda vetorEncomendas[MAX_ENCOMENDAS], int *quantEncomendas)
{
	int posicao, i;

	printf("\n\n----------- ELIMINAR VEICULO -----------  \n");

	vetorEncomendas[*quantEncomendas].numeroRegisto = lerInteiro("\nNUM REGISTO: ", 1, MAX_ENCOMENDAS);

	posicao = procuraEncomenda(vetorEncomendas, *quantEncomendas, vetorEncomendas[*quantEncomendas].numeroRegisto);


	if (posicao == NAO_EXISTE)  // Encomenda nao existe no vetor
	{
		printf("\n\nATENCAO: A encomenda com esse num de registo não existe: %d\n", vetorEncomendas[*quantEncomendas].numeroRegisto);
	}
	else
	{
		for (i=posicao; i < *quantEncomendas-1; i++)
		{
		vetorEncomendas[i] = vetorEncomendas[i+1];
		}

		(*quantEncomendas)--; /* Atualiza nº de encomendas */
	}
}

//função para eliminar encomenda
void alterarDestinoEncomenda(tipoEncomenda vetorEncomendas[MAX_ENCOMENDAS], int *quantEncomendas)
{
	int posicao;

	printf("\n\n----------- EDITAR DESTINO ENCOMENDA -----------  \n");

	vetorEncomendas[*quantEncomendas].numeroRegisto = lerInteiro("\nNUM REGISTO: ", 1, MAX_ENCOMENDAS);

	posicao = procuraEncomenda(vetorEncomendas, *quantEncomendas, vetorEncomendas[*quantEncomendas].numeroRegisto);

	if (posicao == NAO_EXISTE)  // Encomenda nao existe no vetor
	{
		printf("\n\nATENCAO: A encomenda com esse num de registo não existe: %d\n", vetorEncomendas[*quantEncomendas].numeroRegisto);
	}
	else
	{
		printf("DESTINO ANTIGO: %s \n", vetorEncomendas[posicao].destino);
		lerString("NOVO DESTINO:", vetorEncomendas[posicao].destino, TEXTO_LONGO);
	}
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


// -------------- FUNCOES ESTATISTICAS ----------------

//função que permite calcular peso medio das encomendas
void pesoMedioEncomendas(tipoEncomenda vetorEncomendas[MAX_ENCOMENDAS], int quantEncomendas)
{
	int i, count = 0;
	float pesoMediaEncomendas=0.0;
	for (i=0; i < quantEncomendas; i++)
	{
			count += vetorEncomendas[i].pesoEncomenda;
	}

	pesoMediaEncomendas = (float) count/quantEncomendas;
	limpaEcra();
	printf("Peso Médio das encomendas: %.2f kg",pesoMediaEncomendas);
}

void destinosComMaisEncomendas(tipoEncomenda vetorEncomendas[MAX_ENCOMENDAS], int quantEncomendas)
{
	char strTotal[TEXTO_LONGO*100]= "";
	int i,j,count=0; 

	for(i=0;i<quantEncomendas; i++)
	{
		strcat(strTotal,vetorEncomendas[i].destino);
	}
	//printf("strlen %d\n",strlen(strTotal));
   	for(i=0; i<strlen(strTotal) ; i++)
	{
		for(j=0; j<strlen(strTotal) ; j++){			
			if(strTotal[i] == vetorEncomendas[j].destino[j] && i < strlen(vetorEncomendas[j].destino))
			{
				count++;		
				printf("\nDESTINO: %s, Nº DE VEZES: %d\n", vetorEncomendas[i].destino,count);
			}
		}
	}
}

void encomendaPorData (tipoEncomenda vetorEncomendas[MAX_ENCOMENDAS], int quantEncomendas)
{
	tipoData dataEscolhida;

	dataEscolhida = lerData();

    int i,posicao=-1;
    for (i=0; i<quantEncomendas; i++)
    {
        if (vetorEncomendas[i].dataRegisto.dia==0 && vetorEncomendas[i].dataRegisto.mes==0 && vetorEncomendas[i].dataRegisto.ano==0)
        {
            posicao=i;
            i=quantEncomendas;
        }
    }

	if (posicao==-1)
    {
        printf("\n Data de avaria nao encontrada.\n");
    }
    else
    {
        printf("A encomenda foi encontrada com sucesso!");
		escreveDadosEncomenda(vetorEncomendas[posicao],0);
    }

    
}

// -------------- FUNCOES LER e ESCREVER FICHEIRO ----------------

// Funcao guardar no ficheiro
void guardarFicheiro (tipoVeiculo vetorVeiculos[MAX_VEICULOS], int quantVeiculos, tipoEncomenda vetorEncomendas[MAX_ENCOMENDAS], int quantEncomendas)
{
	FILE *ficheiro;
	int elementosGuardados;

	ficheiro = fopen("dadosGuardados.dat", "wb");

	if (ficheiro == NULL)
	{
		printf("\nERRO: falha na abertura do ficheiro.\n");
	}
	else
	{
		elementosGuardados = fwrite(&quantVeiculos, sizeof(int), 1, ficheiro);
		if (elementosGuardados != 1)
		{
			printf("\nERRO: falha na gravacao do numero de veiculos inseridos.\n");
		}
		else
		{
			elementosGuardados = fwrite(vetorVeiculos, sizeof (tipoVeiculo), quantVeiculos, ficheiro);
			if (elementosGuardados != quantVeiculos)
			{
				printf("\nERRO: falha na gravacao dos dados dos veiculos inseridos.\n");
			}
			else
			{
				elementosGuardados = fwrite(&quantEncomendas, sizeof(int), 1, ficheiro);
				if (elementosGuardados != 1)
				{
					printf("\nERRO: falha na gravacao do numero de encomendas inseridos.\n");
				}
				else
				{
					elementosGuardados = fwrite(vetorEncomendas, sizeof(tipoEncomenda), quantEncomendas, ficheiro);
					if (elementosGuardados != quantEncomendas)
					{
						 printf("\nERRO: falha na gravacao dos dados das encomendas inseridos.\n");
					}
				}
			}
		}
		fclose(ficheiro);
	}
}

// Funcao ler do ficheiro
void lerFicheiro (tipoVeiculo vetorVeiculos[MAX_VEICULOS], int *quantVeiculos, tipoEncomenda vetorEncomendas[MAX_ENCOMENDAS], int *quantEncomendas)
{
	FILE *ficheiro;
	int elementosGuardados;

	*quantVeiculos = 0;
	*quantEncomendas = 0;

	ficheiro = fopen("dadosGuardados.dat", "rb");

	if (ficheiro == NULL)
	{
		printf("\nERRO: falha na abertura do ficheiro.\n");
	}
	else
	{
		elementosGuardados = fread(quantVeiculos, sizeof(int), 1, ficheiro);
		if (elementosGuardados != 1)
		{
			printf("\nERRO: falha na leitura do numero de veiculos inseridos.\n");
		}
		else
		{
			elementosGuardados = fread(vetorVeiculos, sizeof (tipoVeiculo), *quantVeiculos, ficheiro);
			if (elementosGuardados != *quantVeiculos)
			{
				printf("\nERRO: falha na leitura dos dados dos veiculos inseridos.\n");
				*quantVeiculos = 0;
			}
			else
			{
				elementosGuardados = fread(quantEncomendas, sizeof(int), 1, ficheiro);
				if (elementosGuardados != 1)
				{
					printf("\nERRO: falha na leitura do numero de encomendas inseridas.\n");
				}
				else
				{
					elementosGuardados = fread(vetorEncomendas, sizeof(tipoEncomenda), *quantEncomendas, ficheiro);
					if (elementosGuardados != *quantEncomendas)
					{
						 printf("\nERRO: falha na leitura dos dados das encomendas inseridas.\n");
						 *quantEncomendas = 0;
					}
				}
			}
		}
		fclose(ficheiro);
	}
}
