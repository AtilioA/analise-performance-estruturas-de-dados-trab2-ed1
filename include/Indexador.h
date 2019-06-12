// Guard para evitar dupla inclusão
#ifndef __INDEXADOR_H
#define __INDEXADOR_H

typedef struct palavra
{
    char *string;
    int ocorrencias;
    int *posicoes;
} tPalavra;


char *String(tPalavra *palavra);

int Ocorrencias(tPalavra *palavra);

int *Posicoes(tPalavra *palavra);

void imprimePalavra(tPalavra *palavra);
tPalavra *criaPalavra(char *string);
tPalavra *iniciaPalavra();

// Libera os elementos de uma palavra
void DestroiPalavra(tPalavra *palavra);

/* Limpa a tela do terminal */
void clrscr();

#endif
