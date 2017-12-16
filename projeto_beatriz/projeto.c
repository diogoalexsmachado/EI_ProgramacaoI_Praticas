#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define LABORATORIOS 15
#define EQUIPAMENTOS 200
#define MAX_STRING 30
#define AVARIA_REPARADA 1
#define AVARIA_POR_REPARAR -1
#define CUSTO_MAXIMO 10000.00
#define CUSTO_MINIMO 0.001
#define MINIMO_ANO 2016
#define MAXIMO_ANO 2017
#define EQUIPAMENTO_INDISPONIVEL -1
#define EQUIPAMENTO_DISPONIVEL 1
#define LOCAL_ARMAZEM "ARMAZEM-ABATES"
#define LOCAL_INVENTARIO "ARMAZEM-INVENTARIO"
#define LOCAL_AVARIA "EM REPARACAO"
#define LOCAL_EQUIPAMENTO "EM LABORATORIO"
#define MAX_AVARIAS 1000
typedef struct
{
    int dia,mes,ano;
} tipoData;

typedef struct
{
    char designacao [MAX_STRING],localizacao [MAX_STRING];
    int postoTrabalho,quantEquipamentos;
} tipoLaboratorio;

typedef struct
{
    int numInventario,estado;
    tipoData dataInventario;
    char descricao [MAX_STRING],localEquipamento [MAX_STRING],numSerie[MAX_STRING];
    float custo;
} tipoEquipamento;

typedef struct
{
    int numAvaria,numInventario,estadoAvaria;
    tipoData dataAvaria;
    char descricaoAvaria [MAX_STRING];
    float custo;

} tipoAvaria;

//Declaracao de funcoes
void escreveData (tipoData data );
int lerInteiro (char msg[], int minimo, int maximo);
void lerString(char msg[],char nome[MAX_STRING], int maxCaracteres);
void limparBufferStdin(void);
float lerFloat(char mensagem[MAX_STRING], float minimo, float maximo);
void listarLaboratorios (tipoLaboratorio vetorLaboratorios[LABORATORIOS], int numLab);
int pesquisaLaboratorios (char nome [MAX_STRING], tipoLaboratorio vetorLaboratorios[LABORATORIOS], int numLab);
void lerLaboratorio (tipoLaboratorio *dados);
void acrescentaLaboratorio(tipoLaboratorio vetorLaboratorios[LABORATORIOS], int *numLab);
void alteraLaboratorios (tipoLaboratorio vetorLaboratorios[LABORATORIOS],int numLab);
void lerEquipamentos (tipoEquipamento *infoEquipamentos);
void acrescentaEquipamento(tipoEquipamento vetorEquipamentos[EQUIPAMENTOS], int *numEquip);
void listarEquipamentos (tipoEquipamento vetorEquipamentos[EQUIPAMENTOS], int numEquip);
int pesquisaEquipamentosNumInventario (tipoEquipamento vetorEquipamentos[EQUIPAMENTOS], int numEquip, int numInventario);
void gravaFicheiroBinarioLab(tipoLaboratorio vetorLaboratorios[LABORATORIOS],int numLab);
void gravaFicheiroBinarioEquip(tipoEquipamento vetorEquipamentos[EQUIPAMENTOS],int numEquip);
void lerFicheiroBinarioLab(tipoLaboratorio vetorLaboratorios[LABORATORIOS], int *numLab);
void lerFicheiroBinarioEquip(tipoEquipamento vetorEquipamentos[EQUIPAMENTOS], int *numEquip);
char menuPrincipal (int numLab, int postoTrabalho, int numEquip, float percentagemEquiAvar);
char menuLaboratorios (void);
char menuEquipamentos (void);
void consultaLabDesignacao (tipoLaboratorio vetorLaboratorios[LABORATORIOS], int numLab);
int pesquisaLaboratoriosLocal (char nome [MAX_STRING],tipoLaboratorio vetorLaboratorios [LABORATORIOS], int numLab);
void consultaLabLocal (tipoLaboratorio vetorLaboratorios [LABORATORIOS],int numLab);
void escreveLab (tipoLaboratorio lab);
void escreveEquipamentos (tipoEquipamento equipamento);
int pesquisaEquipamentosLocal (char nome [MAX_STRING],tipoEquipamento vetorEquipamentos[EQUIPAMENTOS], int numEquip);
void consultaEquipNumInventario (tipoEquipamento vetorEquipamentos[EQUIPAMENTOS],int numEquip);
void consultaEquipLocal (tipoEquipamento vetorEquipamentos[EQUIPAMENTOS], int numEquip);
char menuAvariasEstatisticas (float custoMedioEquip, float percentagemEquipAbatidos, int quantEquipAvariadosData, char labMenorEquipDisponivel);
char menuFicheiros (void);
/*Avarias*/
void leDadosInstalacao (tipoAvaria *avarias);
void leDadosAvarias (tipoAvaria *avarias, int idAvaria);
void leDadosReparacao (tipoAvaria *reparacao);
void leDadosAbate (tipoAvaria *abate);
tipoAvaria *insereAvaria(tipoAvaria *vetorAvarias,int *numAvarias,int *idAvaria,tipoEquipamento vetorEquipamentos[],int numEquip);
void escreveAvarias (tipoAvaria avarias);
tipoAvaria *eliminaAvaria (tipoAvaria *vetorAvarias, int *numAvarias);
int pesquisaAvariasNumAvaria (tipoAvaria vetorAvarias[], int numAvarias, int procNumero );
void listarEquipamentosDisponiveis (tipoEquipamento vetorEquipamentos[],tipoLaboratorio vetorLaboratorios [],int numEquip,int numLab);
int comparaNumeros (const void *v1,const void *v2);
void ordenaEquip(tipoEquipamento vetorEquipamentos[],int numEquip);
float custoMedioEquip (tipoEquipamento vetorEquipamentos [EQUIPAMENTOS], int numEquip);
void logReparacoes (tipoAvaria avaria);
int contaPercEquipAbatidos (tipoEquipamento vetorEquipamentos[EQUIPAMENTOS], int numEquip, float *percentagemEquipAbatidos);
tipoAvaria *leFicheiroBinarioAvaria (tipoAvaria vetorAvarias[], int *numAvarias);
void gravaFicheiroBinarioAvaria (tipoAvaria *avaria, int numAvarias);
char lerCaracter(void);
void alteraEstadoEquipamentoAbatido (tipoEquipamento *equipamento);
void consultaAvariaDataAvaria (tipoAvaria *vetorAvarias, int numAvarias, tipoData dataAvaria);
int pesquisaAvariaData (tipoAvaria vetorAvarias[], int numAvaria,tipoData dataAvaria);
void abateEquipamento (tipoAvaria *vetorAvarias,tipoEquipamento vetorEquipamentos [EQUIPAMENTOS],tipoLaboratorio vetorLaboratorios[LABORATORIOS],int *numEquip,int *quantEquipamentos,int numLab);
int equipAvariadosData (tipoEquipamento vetorEquipamentos[EQUIPAMENTOS],tipoAvaria *vetorAvarias,int numAvarias,int numEquip,tipoData dataAvaria);
void reparacoesMaiorCusto (tipoAvaria *vetorAvarias,int numAvarias, float custo);
void labDesignacaoMenorEquipDisponiveis (tipoLaboratorio vetorLaboratorios [LABORATORIOS],tipoEquipamento vetorEquipamentos[EQUIPAMENTOS],char designacao,int numEquip);
void consultaAvariaNumInventarioEquip (tipoAvaria *vetorAvarias,int numAvarias);
void consultaAvariaNumAvaria (tipoAvaria *vetorAvarias,int numAvarias);
int pesquisaAvariaNumInventarioEquip (tipoAvaria vetorAvarias[],int numInventario,int procNumero);
void listarAvarias (tipoAvaria *vetorAvarias, int numAvarias);
int main(void)
{
    char opcao,opcaoLaboratorio,opcaoEquipamentos,opcaoAvariasEstatisticas,labMenorEquipDisponivel='a',opcaoFicheiros,designacao='a';
    int numLab=0,numEquip=0,postoTrabalho=0,quantEquipAvariadosData,idAvaria=1,numAvarias,quantEquipamentos;

    tipoLaboratorio vetorLaboratorios[LABORATORIOS];
    tipoEquipamento vetorEquipamentos[EQUIPAMENTOS];
    tipoAvaria *vetorAvarias;
    vetorAvarias=NULL;
    float percentagemEquipAvar,custoMedio,percentagemEquipAbatidos,custo=0;
    tipoData dataAvaria;
    percentagemEquipAvar=0.0;
    custoMedio=0.0;
    percentagemEquipAbatidos=0.0;
    quantEquipAvariadosData=0;

    do
    {
        opcao=menuPrincipal(numLab,numEquip,postoTrabalho,percentagemEquipAvar);
        switch(opcao)
        {
        case 'A':
            do
            {
                opcaoLaboratorio=menuLaboratorios();
                switch(opcaoLaboratorio)
                {
                case 'A':
                    acrescentaLaboratorio(vetorLaboratorios, &numLab);
                    break;
                case 'B':
                    listarLaboratorios(vetorLaboratorios,numLab);
                    break;
                case 'C':
                    consultaLabDesignacao (vetorLaboratorios, numLab);
                    break;
                case 'D':
                    consultaLabLocal(vetorLaboratorios,numLab);
                    break;
                case 'E':
                    alteraLaboratorios (vetorLaboratorios, numLab);
                    break;
                }
            }
            while(opcaoLaboratorio!='F');
            break;

        case 'B':
            do
            {
                opcaoEquipamentos=menuEquipamentos();
                switch(opcaoEquipamentos)
                {
                case 'A':
                    acrescentaEquipamento(vetorEquipamentos,&numEquip);
                    break;
                case 'B':
                    listarEquipamentos(vetorEquipamentos,numEquip);
                    break;
                case 'C':
                    consultaEquipNumInventario (vetorEquipamentos, numEquip);
                    break;
                case 'D':
                    consultaEquipLocal(vetorEquipamentos,numEquip);
                    break;
                }
            }
            while(opcaoEquipamentos!='E');
            break;
        case 'C':
            do
            {
                opcaoAvariasEstatisticas=menuAvariasEstatisticas(custoMedio,percentagemEquipAbatidos,quantEquipAvariadosData,labMenorEquipDisponivel);
                switch(opcaoAvariasEstatisticas)
                {
                case 'A':
                    vetorAvarias=insereAvaria(vetorAvarias,&numAvarias,&idAvaria,vetorEquipamentos, numEquip);
                    break;
                case 'B':
                    abateEquipamento (vetorAvarias,vetorEquipamentos,vetorLaboratorios,&numEquip,&quantEquipamentos,numLab);
                    break;
                case 'C':
                    listarAvarias (vetorAvarias,numAvarias);
                    break;
                case 'D':
                    consultaAvariaNumAvaria (vetorAvarias,numAvarias);
                    break;
                case 'E':
                    consultaAvariaNumInventarioEquip (vetorAvarias,numAvarias);
                    break;
                case 'F':
                    consultaAvariaDataAvaria (vetorAvarias,numAvarias,dataAvaria);
                    break;
                case 'G':
                    vetorAvarias=eliminaAvaria (vetorAvarias,&numAvarias);
                    break;
                case 'I':
                    custoMedioEquip (vetorEquipamentos,numEquip);
                    break;
                case 'J':
                    contaPercEquipAbatidos (vetorEquipamentos, numEquip,&percentagemEquipAbatidos);
                    break;
                case 'K':
                    equipAvariadosData (vetorEquipamentos,vetorAvarias,numAvarias,numEquip,dataAvaria);
                    break;
                case 'L':
                    reparacoesMaiorCusto (vetorAvarias,numAvarias,custo);
                    break;
                case 'M':
                    labDesignacaoMenorEquipDisponiveis (vetorLaboratorios, vetorEquipamentos,designacao,numEquip);
                    break;
                }
            }
            while (opcaoAvariasEstatisticas!='H');
            break;
        case 'D':
            do
            {
                opcaoFicheiros=menuFicheiros();
                switch(opcaoFicheiros)
                {
                case 'A':
                    gravaFicheiroBinarioLab(vetorLaboratorios,numLab);
                    break;
                case 'B':
                    lerFicheiroBinarioLab(vetorLaboratorios,&numLab);
                    break;
                case 'C':
                    gravaFicheiroBinarioEquip(vetorEquipamentos,numEquip);
                    break;
                case 'D':
                    lerFicheiroBinarioEquip(vetorEquipamentos,&numEquip);
                    break;
                case 'E':
                    /*vetorAvarias=leFicheiroBinarioAvaria (vetorAvarias,&numAvarias);*/
                    break;
                case 'F':
                    /*gravaFicheiroBinarioAvaria (vetorAvarias,numAvarias);*/
                    break;
                case 'G':
                    /* logReparacoes (avaria);*/
                    break;

                }
            }
            while (opcaoFicheiros!='H');
        }
    }
    while(opcao!='S');
    free (vetorAvarias);
    return 0;
}

/*Menus*/
char menuPrincipal (int numLab, int postoTrabalho, int numEquip, float percentagemEquiAvar)
{
    char opcao;
    do
    {
        printf("\n \t Menu Principal \n");
        printf("\n Escolha uma das seguintes opcoes: \n");
        printf("\n A- Laboratorios \n");
        printf("\n B - Equipamentos \n");
        printf("\n C - Estatistcas e avarias \n");
        printf("\n D - Ler e Gravar  Ficheiros\n");
        printf("\n S - Sair \n");
        printf("\n Quantidade de laboratorios: %d\n",numLab);
        printf("\n Quantidade de postos de trabalho: %d\n",postoTrabalho);
        printf("\n Quantidade de equipamentos: %d\n",numEquip);
        printf("\n Percentagem de Equipamentos avariados: %.2f\n",percentagemEquiAvar);
        scanf(" %c",&opcao);
        opcao=toupper(opcao);

    }
    while (opcao!='A' && opcao!='B' && opcao!='C' && opcao!='D' && opcao!='S');
    return opcao;
}

char menuLaboratorios (void)
{
    char opcao;
    do
    {
        printf("\n \t Menu dos Laboratorios \n");
        printf("\n A - Inserir os dados do laboratorio.\n");
        printf("\n B - Listar os dados dos laboratorios.\n");
        printf("\n C - Consultar os dados dos laboratorios por designacao.\n");
        printf("\n D - Consultar os dados dos laboratorios por localizacao.\n");
        printf("\n E - Alterar os dados dos laboratorios. \n");
        printf("\n F - Voltar ao menu principal. \n");
        scanf(" %c",&opcao);
        opcao=toupper(opcao);
    }
    while(opcao!='A' && opcao!='B' && opcao!='C' && opcao!='D' && opcao!='E' && opcao!='F');
    return opcao;
}
char menuEquipamentos (void)
{
    char opcao;
    do
    {
        printf("\n \t Menu dos Equipamentos\n ");
        printf("\n A - Inventariacao de equipamentos. \n");
        printf("\n B - Listar os dados dos equipamentos. \n");
        printf("\n C - Consultar os dados dos equipamentos pelo seu numero de inventario. \n");
        printf("\n D - Consultar os dados dos equipamentos pela sua localizacao. \n");
        printf("\n E - Voltar ao menu principal. \n");
        scanf(" %c",&opcao);
        opcao=toupper(opcao);
    }
    while(opcao!='A' && opcao!='B' && opcao!='C' && opcao!='D' && opcao!='E');
    return opcao;
}
char menuAvariasEstatisticas (float custoMedioEquip, float percentagemEquipAbatidos, int quantEquipAvariadosData, char labMenorEquipDisponivel)
{
    char opcao;
    do
    {
        printf("\n \t Menu das avarias\n");
        printf("\n A - Registar instalacao, avarias,reparacao abate de equipamento. \n");
        printf("\n B - Registar abate de equipamento. \n");
        printf("\n C - Listar os dados das avarias. \n");
        printf("\n D - Consultar dados das avarias pelo numero de avaria. \n");
        printf("\n E - Consultar dados das avarias pelo numero de inventario do equipamento. \n");
        printf("\n F - Consultar dados das avarias pela data de avaria. \n");
        printf("\n G - Eliminar avarias incorretamente registadas. \n");
        printf("\n H - Voltar ao menu principal. \n");
        printf("\n \t Dados estatisticos. \n");
        printf("\n I - Custo medio de cada equipamento.\n");
        printf("\n J - Percentagem de Equipamentos abatidos. \n");
        printf("\n K - Quantidade de equipamentos avariados numa determinada data.\n");
        printf("\n L - Dados das reparacoes com maior custo.\n");
        printf("\n M - Designacao do(s) laboratorio(s) com menor percentagem de equipamentos disponiveis.\n");
        scanf(" %c",&opcao);
        opcao=toupper(opcao);
    }
    while(opcao!='A' && opcao!='B' && opcao!='C' && opcao!='D' && opcao!='E' && opcao!='F' && opcao!='G' && opcao!='H' && opcao!='I' && opcao!='J' && opcao!='K' && opcao!='L' && opcao!='M' );
    return opcao;
}
char menuFicheiros (void)
{
    char opcao;
    do
    {
        printf("\n \t Menu dos Ficheiros\n");
        printf("\n A - Gravar em Ficheiro Binario os dados dos laboratorios.\n");
        printf("\n B - Ler Ficheiro Binario os dados dos laboratorios. \n");
        printf("\n C - Gravar em Ficheiro Binario os dados dos equipamentos. \n");
        printf("\n D - Ler Ficheiro Binario os dados dos equipamentos. \n");
        printf("\n E - Ler Ficheiro Binario os dados das avarias. \n");
        printf("\n F - Gravar Ficheiro Binario os dados das avarias. \n");
        printf("\n G - Log em ficheiro de texto referente a reparacao. \n");
        printf("\n H - Voltar ao menu principal. \n");
        scanf(" %c",&opcao);
        opcao=toupper(opcao);
    }
    while(opcao!='A' && opcao!='B' && opcao!='C' && opcao!='D' && opcao!='E' && opcao!='F' && opcao!='G' && opcao!='H');
    return opcao;
}
/*Fim dos menus*/
/*Funcoes auxiliares*/
float lerFloat(char mensagem[MAX_STRING], float minimo, float maximo)
{
    float numero;
    int controlo;
    do
    {
        printf("%s (%.2f a %.2f) :", mensagem, minimo, maximo);
        controlo = scanf ("%f", &numero);
        limparBufferStdin();

        if (controlo == 0)
        {
            printf("Insera um numero decimal. \n");
        }
        else
        {
            if(numero<minimo || numero>maximo)
            {
                printf("Numero invalido. Insira novamente:\n");
            }
        }
    }
    while(numero<minimo || numero>maximo || controlo ==0);

    return numero;
}
void lerString(char msg[],char nome[MAX_STRING], int maxCaracteres)
{
    int tamanhoString;
    do
    {
        printf("%s", msg);
        fgets(nome, maxCaracteres, stdin);
        tamanhoString=strlen(nome);

        if (nome[tamanhoString-1]!='\n')
        {
            limparBufferStdin();
        }
        else
        {
            nome[tamanhoString-1]='\0';
        }
    }
    while(tamanhoString==1);
}
int lerInteiro (char msg[], int minimo, int maximo)
{
    int numero,aux;

    do
    {
        printf("%s (%d - %d): ", msg,minimo,maximo);
        aux=scanf("%d", &numero);
        limparBufferStdin();
        if (numero<minimo || numero>maximo || aux!=1)
        {
            printf("\n Numero invalido!\n");
        }
    }
    while (numero<minimo || numero>maximo || aux!=1);
    return numero;
}
void limparBufferStdin(void)
{
    char lixo;
    do
    {
        lixo=getchar();
    }
    while(lixo!= '\n' && lixo!=EOF);
}
/*Fim das funcoes auxiliares*/
/*Funcoes do laboratorio*/

void lerLaboratorio (tipoLaboratorio *dados)
{
    lerString("\n Designacao do laboratorio: \n",dados->designacao, MAX_STRING);
    lerString("\n Localização \n",dados->localizacao, MAX_STRING);
    dados->postoTrabalho = lerInteiro ("\n Postos de Trabalho: \n", 1, 20);
    dados->quantEquipamentos = lerInteiro ("\n Equipamentos Instalados: \n", 1, 200);
}

void listarLaboratorios (tipoLaboratorio vetorLaboratorios[LABORATORIOS], int numLab)
{
    int i;
    if (numLab==0)
    {
        printf("\n Nao existem dados!!!\n");
    }
    else
    {
        for (i=0; i<numLab; i++)
        {
            escreveLab(vetorLaboratorios[i]);
        }
    }
}

void consultaLabDesignacao (tipoLaboratorio vetorLaboratorios[LABORATORIOS], int numLab)
{
    char nome [MAX_STRING];
    int posicao;
    posicao=-1;
    lerString("Insira a designacao do laboratorio. ",nome,MAX_STRING);
    posicao=pesquisaLaboratorios(nome,vetorLaboratorios,numLab);

    if (posicao==-1)
    {
        printf("\n Designacao de laboratorio nao encontrada.\n");
    }
    else
    {
        printf("\n A localizacao do laboratorio e: %s\n",vetorLaboratorios[posicao].localizacao);
        printf("\n O numero de postos de trabalho do laboratorio e: %d\n",vetorLaboratorios[posicao].postoTrabalho);
        printf("\n A quantidade de equipamentos instalados no laboratorio e: %d\n",vetorLaboratorios[posicao].quantEquipamentos);
    }
}
void consultaLabLocal (tipoLaboratorio vetorLaboratorios [LABORATORIOS],int numLab)
{
    char nome [MAX_STRING];
    int posicao;
    posicao=-1;
    lerString("Insira a localizacao do laboratorio. ",nome,MAX_STRING);
    posicao=pesquisaLaboratoriosLocal(nome,vetorLaboratorios,numLab);
    if (posicao==-1)
    {
        printf("\n Localizacao do laboratorio nao encontrada.\n");
    }
    else
    {
        printf("\n A designacao do laboratorio e: %s\n",vetorLaboratorios[posicao].designacao);
        printf("\n O numero de postos de trabalho do laboratorio e: %d\n",vetorLaboratorios[posicao].postoTrabalho);
        printf("\n A quantidade de equipamentos e: %d\n",vetorLaboratorios[posicao].quantEquipamentos);
    }
}
int pesquisaLaboratorios (char nome [MAX_STRING], tipoLaboratorio vetorLaboratorios[LABORATORIOS], int numLab)
{
    int posicao=-1,i;

    for (i=0; i<numLab; i++)
    {
        if (strcmp(vetorLaboratorios[i].designacao, nome)==0)
        {
            posicao=i;
            i=numLab;
        }
    }
    return posicao;
}
int pesquisaLaboratoriosLocal (char nome [MAX_STRING],tipoLaboratorio vetorLaboratorios [LABORATORIOS], int numLab)
{

    int posicao=-1,i;
    for (i=0; i<numLab; i++)
    {
        if (strcmp(vetorLaboratorios[i].localizacao,nome)==0)
        {
            posicao=i;
            i=numLab;
        }
    }
    return posicao;
}

void acrescentaLaboratorio(tipoLaboratorio vetorLaboratorios[LABORATORIOS], int *numLab)
{
    tipoLaboratorio dados;
    int posicao;
    if (*numLab==LABORATORIOS)
    {
        printf("\n Impossivel acrescentar mais laboratorios!\n");
    }
    else
    {
        do
        {
            lerLaboratorio(&dados);
            posicao=pesquisaLaboratorios(dados.designacao,vetorLaboratorios,*numLab);

            if(posicao!=-1)
            {
                printf("\n Laboratorio existente. Introduza os dados de novo!!!\n");
            }
        }
        while(posicao>-1);
        vetorLaboratorios[*numLab]=dados;
        (*numLab)++;
    }
}
void alteraLaboratorios (tipoLaboratorio vetorLaboratorios[LABORATORIOS],int numLab)
{
    int opcao,posicao;
    char designacao[MAX_STRING];

    lerString("\n Insira a designacao do laboratorio a alterar! \n",designacao,MAX_STRING);
    posicao=pesquisaLaboratorios(designacao,vetorLaboratorios,numLab);

    if (posicao==-1)
    {
        printf("\n O laboratorio que selecionou nao existe!\n");
    }
    else
    {
        opcao=lerInteiro("Que opcao deseja alterar 1 - Localizacao \n - \n 2 - Numero de postos de trabalho\n \n 3 - Quantidade de equipamentos instalados",1,3);
        switch(opcao)
        {
        case 1:
            printf("\n Localizacao \n");
            lerString("\n Localizacao \n",vetorLaboratorios[posicao].localizacao, MAX_STRING);
            break;
        case 2:
            printf("\n Numero de postos de trabalho \n");
            vetorLaboratorios[posicao].postoTrabalho = lerInteiro ("\n Postos de Trabalho: \n", 1, 10);
            break;
        case 3:
            printf("\n Quantidade de equipamentos instalados \n");
            vetorLaboratorios[posicao].quantEquipamentos = lerInteiro ("\n Quantidade de equipamentos instalados: \n", 1, 30);
            break;
        }
    }
}
void escreveLab (tipoLaboratorio lab)
{
    printf("\n Designacao: %s \n",lab.designacao);
    printf("\n Localizacao: %s \n",lab.localizacao);
    printf("\n Numero de postos de trabalho: %d \n",lab.postoTrabalho);
    printf("\n Quantidade de equipamentos instalados: %d \n",lab.quantEquipamentos);
}
/*Fim das Funcoes do laboratorio*/

/*Funcoes dos Equipamentos*/
void lerEquipamentos (tipoEquipamento *infoEquipamentos)
{

    printf("\n Inserir dados dos Equipamentos\n");
    infoEquipamentos->numInventario=lerInteiro("\n Numero do Equipamento: \n",1,EQUIPAMENTOS);
    printf("\n Data de inventariacao: \n");
    infoEquipamentos->dataInventario.dia=lerInteiro("\n Dia: ",1,31);
    infoEquipamentos->dataInventario.mes=lerInteiro("\n Mes: ",1,12);
    infoEquipamentos->dataInventario.ano=lerInteiro("\n Ano: ",2016,2017);
    lerString("\n Numero de Serie: \n",infoEquipamentos->numSerie,MAX_STRING);
    lerString("\n Localizacao: \n",infoEquipamentos->localEquipamento,MAX_STRING);
    infoEquipamentos->estado = EQUIPAMENTO_DISPONIVEL;   // Equipamento disponivel
    infoEquipamentos->custo=lerFloat("\n Custo: \n",1.0,5000);
}

void acrescentaEquipamento(tipoEquipamento vetorEquipamentos[EQUIPAMENTOS], int *numEquip)
{
    tipoEquipamento infoEquipamentos;
    int posicao;
    if (*numEquip==EQUIPAMENTOS)
    {
        printf("\n Impossivel acrescentar mais equipamentos!\n");
    }
    else
    {
        do
        {
            lerEquipamentos(&infoEquipamentos);
            strcpy(vetorEquipamentos[*numEquip].localEquipamento,LOCAL_EQUIPAMENTO); /*coloca o equipamento no laboratorio*/
            posicao=pesquisaEquipamentosNumInventario(vetorEquipamentos,*numEquip,infoEquipamentos.numInventario);

            if(posicao!=-1)
            {
                printf("\n Equipamento existente. Introduza os dados de novo!!!\n");
            }
        }
        while(posicao>-1);
        vetorEquipamentos[*numEquip]=infoEquipamentos;
        (*numEquip)++;
    }

}
void escreveEquipamentos (tipoEquipamento equipamento)
{
    printf("\n Numero de inventario: %d \n",equipamento.numInventario);
    printf("\n Data de inventariacao: %d - %d - %d \n",equipamento.dataInventario.dia,equipamento.dataInventario.mes,equipamento.dataInventario.ano);
    printf("\n Descricao: %s \n",equipamento.descricao);
    printf("\n Numero de serie: %s \n",equipamento.numSerie);
    printf("\n Localizacao: %s \n",equipamento.localEquipamento);
    printf("\n Estado: %d \n",equipamento.estado);
    printf("\n Custo: %4.2f \n",equipamento.custo);
}
void listarEquipamentos (tipoEquipamento vetorEquipamentos[EQUIPAMENTOS], int numEquip)
{
    int i;
    if (numEquip==0)
    {
        printf("\n Nao existem dados!!!\n");

    }
    else
    {
        for (i=0; i<numEquip; i++)
        {
            escreveEquipamentos(vetorEquipamentos[i]);
        }
    }
}

int pesquisaEquipamentosNumInventario (tipoEquipamento vetorEquipamentos[EQUIPAMENTOS], int numEquip, int numInventario)
{
    int posicao=-1,i;

    for (i=0; i<numEquip; i++)
    {
        if (vetorEquipamentos[i].numInventario ==  numInventario)
        {
            posicao=i;
            i=numEquip;
        }
    }
    return posicao;
}
int pesquisaEquipamentosLocal (char nome [MAX_STRING],tipoEquipamento vetorEquipamentos[EQUIPAMENTOS], int numEquip)
{

    int posicao=-1,i;
    for (i=0; i<numEquip; i++)
    {
        if (strcmp(vetorEquipamentos[i].localEquipamento,nome)==0)
        {
            posicao=i;
            i=numEquip;
        }
    }
    return posicao;
}
void consultaEquipNumInventario (tipoEquipamento vetorEquipamentos[EQUIPAMENTOS],int numEquip)
{
    int posicao,numInventario=0;
    posicao=-1;
    lerInteiro("\n Insira o numero de Inventario do equipamento.\n",1,EQUIPAMENTOS);
    posicao=pesquisaEquipamentosNumInventario(vetorEquipamentos,numEquip,numInventario);
    if (posicao==-1)
    {
        printf("\n Numero de inventario nao encontrado.\n");
    }
    else
    {
        printf("\n Data de inventariacao: %d - %d - %d \n",vetorEquipamentos[posicao].dataInventario.dia,vetorEquipamentos[posicao].dataInventario.mes,vetorEquipamentos[posicao].dataInventario.ano);
        printf("\n Numero de serie: %s \n",vetorEquipamentos[posicao].numSerie);
        printf("\n Localizacao do equipamento: %s \n",vetorEquipamentos[posicao].localEquipamento);
        printf("\n Estado: 1- Disponivel %d\n",vetorEquipamentos[posicao].estado);
        printf("\n Custo do equipamento: %4.2f \n",vetorEquipamentos[posicao].custo);
    }
}
void consultaEquipLocal (tipoEquipamento vetorEquipamentos[EQUIPAMENTOS], int numEquip)
{
    char nome [MAX_STRING];
    int posicao;
    posicao=-1;
    lerString("Insira a localizacao do equipamento.",nome,MAX_STRING);
    posicao=pesquisaEquipamentosLocal(nome,vetorEquipamentos,numEquip);
    if (posicao==-1)
    {
        printf("\n Localizacao de equipamento nao encontrada. \n");
    }
    else
    {
        printf("\n Data de inventariacao: %d - %d - %d \n",vetorEquipamentos[posicao].dataInventario.dia,vetorEquipamentos[posicao].dataInventario.mes,vetorEquipamentos[posicao].dataInventario.ano);
        printf("\n Numero de serie: %s\n",vetorEquipamentos[posicao].numSerie);
        printf("\n Estado: 1-Disponivel %d \n",vetorEquipamentos[posicao].estado);
        printf("\n Custo do equipamento: %4.2f \n",vetorEquipamentos[posicao].custo);
    }
}
/*Fim das funcoes dos equipamentos*/
/*Ficheiros*/
void gravaFicheiroBinarioLab(tipoLaboratorio vetorLaboratorios[LABORATORIOS],int numLab)
{

    FILE*fich;
    int num_elementos;

    fich=fopen("laboratorios.dat", "wb");
    if (fich==NULL)
    {
        perror("\n Erro a abrir ficheiro para escrita.");
    }
    else
    {
        num_elementos=fwrite(&numLab,sizeof(int),1,fich);
        fwrite(vetorLaboratorios,sizeof(tipoLaboratorio),numLab,fich);
        if (num_elementos<numLab)
        {
            printf("\n Apenas foram escritos os dados de %d laboratorios.",num_elementos);
        }
        fclose(fich);
    }
}
void gravaFicheiroBinarioEquip(tipoEquipamento vetorEquipamentos[EQUIPAMENTOS],int numEquip)
{

    FILE*fich;
    int num_elementos;

    fich=fopen("equipamentos.dat", "wb");
    if (fich==NULL)
    {
        perror("\n Erro a abrir ficheiro para escrita.");
    }
    else
    {
        num_elementos=fwrite(&numEquip,sizeof(int),1,fich);
        fwrite(vetorEquipamentos,sizeof(tipoEquipamento),numEquip,fich);
        if (num_elementos<numEquip)
        {
            printf("\n Apenas foram escritos os dados de %d equipamentos.",num_elementos);
        }
        fclose(fich);
    }
}
void lerFicheiroBinarioLab(tipoLaboratorio vetorLaboratorios[LABORATORIOS], int *numLab)
{
    int numElemLidos;
    FILE*fich;
    fich=fopen("laboratorios.dat","rb");
    if (fich==NULL)
    {
        perror("\n Erro a abrir ficheiro para leitura!");
    }
    else
    {
        fread(numLab,sizeof(int),1,fich);
        numElemLidos=fread(vetorLaboratorios,sizeof(tipoLaboratorio),*numLab,fich);
        if (numElemLidos<*numLab)
        {
            printf("\nErro ao ler os dados dos laboratorios.");
            *numLab=0;
        }
        fclose(fich);
    }
}
void lerFicheiroBinarioEquip(tipoEquipamento vetorEquipamentos[EQUIPAMENTOS], int *numEquip)
{
    int numElemLidos;
    FILE*fich;
    fich=fopen("equipamentos.dat","rb");
    if (fich==NULL)
    {
        perror("\n Erro a abrir ficheiro para leitura!");
    }
    else
    {
        fread(numEquip,sizeof(int),1,fich);
        numElemLidos=fread(vetorEquipamentos,sizeof(tipoEquipamento),*numEquip,fich);
        if (numElemLidos<*numEquip)
        {
            printf("\nErro ao ler os dados dos equipamentos.");
            *numEquip=0;
        }
        fclose(fich);
    }
}
void escreveData (tipoData data )
{

    printf("\n %2d/%2d/%4d \n ",data.dia,data.mes,data.ano);
}
tipoData lerData (void)
{
    tipoData data;
    int maximoDia;
    data.ano=lerInteiro("\n Ano: \n",MINIMO_ANO,MAXIMO_ANO);
    data.mes=lerInteiro("\n Mes: \n",1,12);

    switch (data.mes)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        maximoDia = 31;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        maximoDia = 30;
        break;
    case 2:
        if (data.ano % 400 == 0 || (data.ano % 4 == 0 && data.ano % 100 != 0))
        {

            maximoDia = 29;
        }
        else
        {
            maximoDia = 28;
        }
    }

    data.dia = lerInteiro("Dia: ", 1, maximoDia);

    return data;
}

void leDadosInstalacao (tipoAvaria *instalacao)
{

    printf("Descricao da instalacao!");
    lerString(" Breve descricao da instalacao: ",instalacao->descricaoAvaria,MAX_STRING);
    printf("Insira a data da instalacao.");
    instalacao->dataAvaria=lerData();
    printf("Numero de inventario do equipamento: ");
    lerInteiro("Numero de Inventario do equipamento: ",1,EQUIPAMENTOS);
}


void leDadosReparacao (tipoAvaria *reparacao)
{

    printf("Descricao da reparacao!");
    lerString("Breve descricao da reparacao a efetuar: ",reparacao->descricaoAvaria,MAX_STRING);
    printf("Numero de inventario do equipamento: ");
    reparacao->numInventario=lerInteiro("Numero de Inventario do equipamento: ",1,EQUIPAMENTOS);
    printf("Insira a data da reparacao.");
    reparacao->dataAvaria=lerData();
    printf("Custo da reparacao.");
    reparacao->custo=lerFloat("Insira o custo da reparacao: ",CUSTO_MINIMO,CUSTO_MAXIMO);
}
void leDadosAbate (tipoAvaria *abate)
{
    int nEquip=1;

    printf("Insira o numero de inventario do equipamento que deseja abater.");
    abate->numInventario=lerInteiro("Numero de inventario do equipamento",1,EQUIPAMENTOS);
    printf("Insira a data do abate do equipamento");
    abate->dataAvaria=lerData();
    printf("Motivo do abate.");
    lerString("Insira um breve motivo do abate: ",abate->descricaoAvaria,MAX_STRING);
    nEquip--;
}
tipoAvaria *insereAvaria(tipoAvaria *vetorAvarias,int *numAvarias,int *idAvaria,tipoEquipamento vetorEquipamentos[],int numEquip)
{
    tipoAvaria *avarias;
    char nome[MAX_STRING];
    int numInventario,posicao=-1;
    avarias=vetorAvarias;

    if (numEquip==0)
    {
        printf("\n Impossivel inserir uma avaria!\n");
    }
    else
    {
        numInventario=lerInteiro("\n Insira o numero do equipamento.\n",1,EQUIPAMENTOS);
        posicao=pesquisaEquipamentosNumInventario (vetorEquipamentos,numEquip,numInventario);

        if (posicao==-1)
        {
            printf("\n O equipamento nao foi encontrado.\n");
        }
        else
        {
            if (vetorEquipamentos[posicao].estado==1)
            {
                printf("\n Pode registar a avaria do equipamento. \n");

                avarias=realloc(avarias,(*numAvarias+1)*sizeof(tipoAvaria));
                if (strcmp(vetorEquipamentos[posicao].localEquipamento,nome)==0)
                {

                    printf("\n Foi encontrado o equipamento.\n");

                    if (avarias==NULL)
                    {
                        printf("Erro ao reservar memoria!!!");
                        avarias=vetorAvarias;
                    }

                    else
                    {
                        printf("\n Registar Avaria de Equipamento \n");
                        printf("Descricao da avaria!");
                        lerString("Breve descricao da avaria: ",avarias[*numAvarias].descricaoAvaria,MAX_STRING);
                        printf("Numero da avaria!");
                        avarias[*numAvarias].numAvaria=*idAvaria;
                        printf("Numero de inventario do equipamento: ");
                        avarias[*numAvarias].numInventario=lerInteiro("Numero de Inventario do equipamento: ",1,EQUIPAMENTOS);
                        printf("Insira a data da avaria.");
                        avarias[*numAvarias].dataAvaria=lerData();
                        printf("Estado da avaria - 1: Por reparar /t 2: Reparada /t 3: Nenhuma das opcoes anteriores");
                        avarias[*numAvarias].estadoAvaria=1;

                        vetorEquipamentos[posicao].estado=AVARIA_POR_REPARAR;
                        (*numAvarias)++;
                        (*idAvaria)++;
                    }
                }


                /*main*/ /*opcao=lerInteiro("Escolha uma das seguintes opcoes: /t 1- Registar Instalacao de Equipamento. /t 2- Registar Avaria de Equipamento. /t 3- Registar Reparacao de Equipamento. /t 4- Registar Abate de Equipamento ",1,4);
                     switch(opcao){
                         //case 1:
                             printf("\n Registar Instalacao de Equipamento\n");
                             leDadosReparacao(&avarias[i]);
                         break;
                         case 2:

                         break;
                         case 3:
                             printf("\n Registar Reparacao de Equipamento \n");
                             leDadosReparacao(&avarias[i]);
                         break;
                         case 4:
                             printf("\n Registar Abate de Equipamento \n");
                             leDadosAbate(&avarias[i]);
                         break;
                     }*/
            }
        }

    }
    return avarias;
}



void escreveAvarias (tipoAvaria avarias)
{

    printf("\n Dados das avarias.\n");
    printf("\n Numero da avaria: %d \n",avarias.numAvaria);
    printf("\n Data da avaria: %d/%d/%d \n",avarias.dataAvaria.dia,avarias.dataAvaria.mes,avarias.dataAvaria.ano);
    printf("\n Numero de inventario do equipamento: %d \n",avarias.numInventario);
    printf("\n Breve descricao da avaria: %s\n",avarias.descricaoAvaria);
    printf("\n Estado da avaria: %d \n",avarias.estadoAvaria);
    printf("\n Custo da avaria: %4.2f \n",avarias.custo);
}

void listarAvarias (tipoAvaria *vetorAvarias, int numAvarias)
{
    int i;
    if (numAvarias==0)
    {
        printf("\n Nao existem dados!!!\n");
    }
    else
    {
        for (i=0; i<numAvarias; i++)
        {
            escreveAvarias(vetorAvarias[i]);
        }
    }
}
void abateEquipamento (tipoAvaria *vetorAvarias,tipoEquipamento vetorEquipamentos [EQUIPAMENTOS],tipoLaboratorio vetorLaboratorios[LABORATORIOS],int *numEquip, int *quantEquipamentos,int numLab)
{
    int i,posicao=-1,numInventario,procNumero=0;

    numInventario=lerInteiro("Insira o numero do inventario do equipamento.",1,EQUIPAMENTOS);
    posicao=pesquisaAvariaNumInventarioEquip (vetorAvarias,numInventario,procNumero);


    if (posicao==-1)
    {
        printf("\n O numero de inventario que inseriu nao foi encontrado!\n");
    }
    else
    {

        strcpy(vetorEquipamentos[numInventario].localEquipamento,LOCAL_ARMAZEM);
        vetorEquipamentos[numInventario].estado=EQUIPAMENTO_INDISPONIVEL;
        for (i=0; i<numLab; i++)
        {
            quantEquipamentos-=vetorLaboratorios[i].quantEquipamentos;
        }
    }
}
void consultaAvariaDataAvaria (tipoAvaria *vetorAvarias, int numAvarias, tipoData dataAvaria)
{
    int posicao;
    posicao=-1;
    printf("\n Insira a data da avaria.\n");
    dataAvaria=lerData();
    posicao=pesquisaAvariaData(vetorAvarias,numAvarias,dataAvaria);
    if (posicao==-1)
    {
        printf("\n Data de avaria nao encontrada.\n");
    }
    else
    {
        printf("A avaria foi encontrada com sucesso!");
    }

}
int pesquisaAvariaData (tipoAvaria vetorAvarias[], int numAvaria,tipoData dataAvaria)
{
    int i,posicao=-1;
    for (i=0; i<numAvaria; i++)
    {

        if (vetorAvarias[i].dataAvaria.dia==0 && vetorAvarias[i].dataAvaria.mes==0 && vetorAvarias[i].dataAvaria.ano==0)
        {
            posicao=i;
            i=numAvaria;
        }
    }
    return posicao;
}
void consultaAvariaNumAvaria (tipoAvaria *vetorAvarias,int numAvarias)
{
    int posicao,numeroAvaria;
    posicao=-1;
    numeroAvaria=lerInteiro("\n Insira o numero da avaria.\n",1,MAX_AVARIAS);
    posicao=pesquisaAvariasNumAvaria(vetorAvarias,numAvarias,numeroAvaria);
    if (posicao==-1)
    {
        printf("Numero da avaria nao encontrado.");
    }
    else
    {
        printf("\n Data de registo: %d - %d - %d \n",vetorAvarias[posicao].dataAvaria.dia,vetorAvarias[posicao].dataAvaria.mes,vetorAvarias[posicao].dataAvaria.ano);
        printf("\n Numero de inventario do equipamento: %d \n",vetorAvarias[posicao].numInventario);
        printf("\n Breve descricao da avaria: %s \n",vetorAvarias[posicao].descricaoAvaria);
        printf("\n Estado da avaria: %d\n",vetorAvarias[posicao].estadoAvaria);
        printf("\n Custo da avaria: %4.2f \n",vetorAvarias[posicao].custo);
    }
}
void consultaAvariaNumInventarioEquip (tipoAvaria *vetorAvarias,int numInventario)
{
    int posicao,numeroInventario=0;

    posicao=-1;
    numInventario=lerInteiro("\n Insira o numero de inventario.\n",1,EQUIPAMENTOS);
    posicao=pesquisaAvariaNumInventarioEquip (vetorAvarias, numInventario,numeroInventario);
    if (posicao==-1)
    {
        printf("\n Numero de inventario nao encontrado.\n");
    }
    else
    {
        printf("\n Data de registo: %d - %d - %d \n",vetorAvarias[posicao].dataAvaria.dia,vetorAvarias[posicao].dataAvaria.mes,vetorAvarias[posicao].dataAvaria.ano);
        printf("\n Numero de inventario do equipamento: %d \n",vetorAvarias[posicao].numInventario);
        printf("\n Breve descricao da avaria: %s \n",vetorAvarias[posicao].descricaoAvaria);
        printf("\n Estado da avaria: %d\n",vetorAvarias[posicao].estadoAvaria);
        printf("\n Custo da avaria: %4.2f \n",vetorAvarias[posicao].custo);
    }
}
int pesquisaAvariaNumInventarioEquip (tipoAvaria vetorAvarias[],int numInventario,int procNumero)
{
    int posicao=-1,i;
    for (i=0; i<numInventario; i++)
    {
        if (vetorAvarias[i].numInventario==procNumero)
        {
            posicao=i;
            i=numInventario;
        }
    }
    return posicao;
}
int pesquisaAvariasNumAvaria (tipoAvaria vetorAvarias[], int numAvarias, int procNumero )
{
    int posicao=-1,i;

    for (i=0; i<numAvarias; i++)
    {
        if (vetorAvarias[i].numAvaria ==  procNumero)
        {
            posicao=i;
            i=numAvarias;
        }
    }
    return posicao;
}

tipoAvaria *eliminaAvaria (tipoAvaria *vetorAvarias, int *numAvarias)
{
    tipoAvaria *avarias;
    int i,posicao,procNumero;
    avarias=vetorAvarias;


    if (*numAvarias!=0)
    {
        procNumero=lerInteiro("Insira o numero da avaria.",1,250);
        posicao=pesquisaAvariasNumAvaria(vetorAvarias,*numAvarias,procNumero);
        if (posicao==-1)
        {
            printf("Avaria nao existe!");

        }
        else
        {

            for (i=posicao; i<*numAvarias-1; i++)
            {
                avarias[i]=avarias[i+1];
            }
            vetorAvarias=realloc(vetorAvarias,(*numAvarias-1)*sizeof(tipoAvaria));
            if (vetorAvarias==NULL && (*numAvarias-1)!=0)
            {
                printf("Erro na alocacao de memoria!");
                vetorAvarias=avarias;
            }
            (*numAvarias)--;
        }

    }
    return vetorAvarias;
}
void listarEquipamentosDisponiveis (tipoEquipamento vetorEquipamentos[],tipoLaboratorio vetorLaboratorios [],int numEquip,int numLab)
{
    /*tipoEquipamento equipamento;*/
    int i,j;


    for(i=0; i<numLab; i++)
    {

        for (j=0; j<numEquip; j++)
        {

            if (strcmp(vetorLaboratorios[i].designacao,vetorEquipamentos[j].localEquipamento)==0)
            {

                if (vetorEquipamentos[j].estado==1)
                {

                    escreveEquipamentos(vetorEquipamentos[j]);
                }
                else
                {
                    printf("\n Nao existem equipamentos disponives para mostrar.\n");
                }
                /* ordenacao por ordem crescente de quantidade de equipamentos disponiveis*/

            }


        }


    }

}
int comparaNumeros (const void *v1,const void *v2)
{
    tipoEquipamento *valor1,*valor2;
    int compara;
    valor1=(tipoEquipamento*) v1;
    valor2=(tipoEquipamento*) v2;
    compara=valor1->numInventario - valor2->numInventario;
    return compara;
}

void ordenaEquip(tipoEquipamento vetorEquipamentos[],int numEquip)
{
    int i;
    if (numEquip==0)
    {
        printf("\n Nao existem dados de equipamentos para mostrar.\n");
    }
    else
    {
        qsort(vetorEquipamentos,numEquip,sizeof(tipoEquipamento),comparaNumeros);
        printf("\n Dados dos Equipamentos.\n");
        for(i=0; i<numEquip; i++)
        {
            escreveEquipamentos(vetorEquipamentos[i]);
        }
    }
}
float custoMedioEquip (tipoEquipamento vetorEquipamentos [EQUIPAMENTOS], int numEquip)
{
    float media,soma;
    int i;
    soma=0.0;
    if (numEquip==0)
    {
        printf("\n Nao existem equipamentos!!\n");
        media=0.0;
    }
    else
    {
        for (i=0; i<numEquip; i++)
        {
            soma+=vetorEquipamentos[i].custo;
        }
        media=soma/numEquip;
        printf(" O custo medio dos equipamentos e: %.2f €",media);
    }
    return media;
}
int contaPercEquipAbatidos (tipoEquipamento vetorEquipamentos[EQUIPAMENTOS], int numEquip, float *percentagemEquipAbatidos)
{
    int i,contaEquipDisponiveis,contaEquipAbatidos;
    contaEquipDisponiveis=0;
    contaEquipAbatidos=0;
    for (i=0; i<numEquip; i++)
    {
        if (vetorEquipamentos[i].estado!=EQUIPAMENTO_INDISPONIVEL)
        {
            contaEquipDisponiveis++;
            if (vetorEquipamentos[i].estado==EQUIPAMENTO_INDISPONIVEL)
            {
                contaEquipAbatidos++;
            }
        }
    }
    if (contaEquipDisponiveis==0)
    {
        *percentagemEquipAbatidos=0.0;
    }
    else
    {
        *percentagemEquipAbatidos=contaEquipAbatidos*100.0/contaEquipDisponiveis;
    }
    return contaEquipAbatidos;
}
int equipAvariadosData (tipoEquipamento vetorEquipamentos[EQUIPAMENTOS],tipoAvaria *vetorAvarias,int numAvarias,int numEquip,tipoData dataAvaria)
{
    int i,contaEquipAvariados;
    contaEquipAvariados=0;
    if(numEquip==0)
    {
        printf("\n Nao existem equipamentos para mostrar.\n");
    }
    else
    {
        for (i=0; i<numEquip; i++)
        {
            if (vetorEquipamentos[i].estado==EQUIPAMENTO_INDISPONIVEL)
            {
                /*contaEquipAvariados=consultaAvariaDataAvaria (vetorAvarias,numAvaria,dataAvaria);*/
                contaEquipAvariados++;
                printf("\n Existem %d equipamentos avariados.\n",contaEquipAvariados);
            }
        }

    }
    return contaEquipAvariados;
}
void reparacoesMaiorCusto (tipoAvaria *vetorAvarias,int numAvarias, float custo)
{
    float maior;
    int i;
    if (numAvarias==0)
    {
        printf("\n Nao existem dados para mostrar.\n");
    }
    else
    {
        maior=vetorAvarias[0].custo;
        for (i=0; i<numAvarias; i++)
        {
            if (vetorAvarias[i].custo>maior)
            {
                maior=vetorAvarias[i].custo;
            }
        }
        printf("\nReparacoes com maior custo: %.2f \n",maior);
        for(i=0; i<numAvarias; i++)
        {
            if(vetorAvarias[i].custo==maior)
            {
                escreveAvarias(vetorAvarias[i]);
            }
        }
    }
}
void labDesignacaoMenorEquipDisponiveis (tipoLaboratorio vetorLaboratorios [LABORATORIOS],tipoEquipamento vetorEquipamentos[EQUIPAMENTOS],char designacao,int numEquip)
{
    int contaEquipDisponiveis,contaEquipIndisponiveis,i;
    float percEuipDisponiveis,menor;
    char nome[MAX_STRING];
    if(numEquip==0)
    {
        printf("\n Nao existem dados a mostrar.\n");
    }
    else
    {
        menor=vetorEquipamentos[0].estado==EQUIPAMENTO_DISPONIVEL;
    }
    for(i=0; i<numEquip; i++)
    {
        if((vetorEquipamentos[i].estado==EQUIPAMENTO_DISPONIVEL)<menor)
        {
            menor=vetorEquipamentos[i].estado==EQUIPAMENTO_DISPONIVEL;
        }
    }
    for(i=0; i<numEquip; i++)
    {
        if(vetorEquipamentos[i].estado==EQUIPAMENTO_DISPONIVEL)
        {
            contaEquipDisponiveis++;
            if (vetorEquipamentos[i].estado==EQUIPAMENTO_INDISPONIVEL)
            {
                contaEquipIndisponiveis++;

                strcpy(vetorLaboratorios[i].designacao,nome);

            }
        }
        if(contaEquipDisponiveis==0)
        {
            percEuipDisponiveis=0.0;
        }
        else
        {
            percEuipDisponiveis=contaEquipDisponiveis*100.0/menor;
            printf("Percentagem de equipamentos disponiveis: %.2f",percEuipDisponiveis);
            printf("\n Os laboratorios com menor percentagem de equipamentos disponiveis sao: %s\n",nome);
        }
    }
    void alteraEstadoEquipamentoAbatido (tipoEquipamento *equipamento)
    {
        char opcao;
        printf("Equipamento: %d",equipamento->numInventario);
        printf("Deseja abater o equipamento? S/N");
        do
        {
            opcao=lerCaracter();
            opcao=toupper(opcao);
        }
        while (opcao!='S' && opcao!='N');
        scanf("%d",&equipamento->estado);
        printf("\n O equipamento numero: %d passou a estar abatido \n",equipamento->numInventario);
    }

    /*void alteraLocalEquipamento (tipoEquipamento vetorEquipamentos [EQUIPAMENTOS]){
    tipoEquipamento equipamento;
    char opcao,localizacao[MAX_STRING];
    int posicao;
        printf("Local do Equipamento: %s",equipamento->localEquipamento);
            posicao=pesquisaEquipamentosLocal(localizacao,vetorEquipamentos,numEquip);
            do{
                printf("\n Deseja alterar o local do equipamento? Sim/Nao.\n");
                if (vetorEquipamentos[posicao].localEquipamento==LOCAL_EQUIPAMENTO){
                    printf("\n O equipamento esta disponivel em laboratorio.\n");
                    opcao=lerCaracter();
                    opcao=toupper(opcao);
                }while(opcao!='S' && opcao!='N');
                scanf("%s",equipamento->localEquipamento);
                }


    }*/
    void gravaFicheiroBinarioAvaria (tipoAvaria *avaria, int numAvarias)
    {
        FILE *fich;
        int contaAvariasEscritas;
        fich=fopen("avarias.dat","wb");
        if (fich==NULL)
        {
            printf("\n Impossivel abrir o ficheiro.\n");
        }
        else
        {
            contaAvariasEscritas=fwrite(&numAvarias,sizeof (int),1,fich);
            if (contaAvariasEscritas!=1)
            {
                printf("\n Erro ao escrever a quantidade de avarias.\n");
            }
            contaAvariasEscritas=fwrite(avaria,sizeof(tipoAvaria),numAvarias,fich);
            if (contaAvariasEscritas!=numAvarias)
            {
                printf("\n Erro ao escrever dados das avarias.\n");
            }
            fclose(fich);
        }

    }
    tipoAvaria *leFicheiroBinarioAvaria (tipoAvaria vetorAvarias[], int *numAvarias)
    {
        FILE *fich;

        fich=fopen("avarias.dat","rb");
        if (fich==NULL)
        {
            printf("\n Impossivel abrir o ficheiro.\n");
            free(vetorAvarias);
            vetorAvarias=NULL;
            *numAvarias=0;
        }
        else
        {
            fread(&(*numAvarias),sizeof(int),1,fich);
            vetorAvarias=realloc(vetorAvarias,(*numAvarias)*sizeof(tipoAvaria));
            if(vetorAvarias==NULL && *numAvarias!=0)
            {
                printf("Erro ao reservar memoria.");
                *numAvarias=0;
            }
            else
            {
                fread(vetorAvarias,sizeof(tipoAvaria),*numAvarias,fich);
            }
            fclose(fich);
        }


        return vetorAvarias;
    }

    void logReparacoes (tipoAvaria avaria)
    {
        FILE *fich;
        int erro=0;
        fich=fopen("logReparaoes.txt","a");
        if (fich==NULL)
        {
            printf("\n Falha a abrir o ficheiro!\n");
        }
        else
        {

            fprintf(fich,"Log: Numero do inventario do equipamento: %d",avaria.numInventario);
            fprintf(fich,"Log: Custo da avaria: %4.2f",avaria.custo);
            fprintf(fich,"Log: Descricao da reparacao: %s",avaria.descricaoAvaria);
            fprintf(fich,"Log: Data de registo da avaria: %2d %2d %4d",avaria.dataAvaria.dia,avaria.dataAvaria.mes,avaria.dataAvaria.ano);

            erro=fclose(fich);
            if (erro!=0)
            {
                printf("Erro %d ao fechar o ficheiro",erro);
            }
        }
    }
    char lerCaracter(void)
    {
        char caracter;

        scanf(" %c",&caracter);
        limparBufferStdin();
        caracter = toupper(caracter);

        return caracter;
    }
}
