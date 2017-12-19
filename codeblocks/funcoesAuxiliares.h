#ifndef FUNCOESAUXILIARES_H_INCLUDED
#define FUNCOESAUXILIARES_H_INCLUDED

#define TEXTO_LONGO 100
#define TEXTO_BREVE 20

int lerInteiro (char msg[TEXTO_LONGO], int limMin, int limMax);
float lerFloat (char msg[TEXTO_LONGO], float limMin, float limMax);
void lerString(char msg[TEXTO_LONGO], char str[TEXTO_LONGO], int tamanho);
void lerMatricula(char msg[TEXTO_LONGO], char str[TEXTO_LONGO], int isSearch);
void limparBuffer (void);


#endif // FUNCOESAUXILIARES_H_INCLUDED
