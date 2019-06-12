#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Indexador.h"


char *String(tPalavra *palavra)
{
    return palavra->string;
}

int Ocorrencias(tPalavra *palavra)
{
    return palavra->ocorrencias;
}

int *Posicoes(tPalavra *palavra)
{
    return palavra->posicoes;
}

tPalavra *criaPalavra(char *string)
{
    tPalavra *nova = (tPalavra *)malloc(sizeof(tPalavra)); // ponteiro?

    nova->string = (char *)malloc((strlen(string) + 1) * sizeof(char));
    if (nova->string == NULL)
    {
        return NULL;
    }
    strcpy(nova->string, string);
    nova->posicoes = (int *)malloc(sizeof(int));
    if (nova->posicoes == NULL)
    {
        return NULL;
    }
    nova->ocorrencias = 0;

    return nova;
}

tPalavra *iniciaPalavra()
{
    tPalavra *nova = (tPalavra *)malloc(sizeof(tPalavra)); // ponteiro?

    nova->string = (char *)malloc(sizeof(char));
    if (nova->string == NULL)
    {
        return NULL;
    }
    nova->posicoes = (int *)malloc(sizeof(int));
    if (nova->posicoes == NULL)
    {
        return NULL;
    }
    nova->ocorrencias = 0;

    return nova;
}

void DestroiPalavra(tPalavra *palavra)
{
    free(palavra->string);
    free(palavra->posicoes);
    palavra->ocorrencias = -1;
}

void clrscr()
{
#ifdef __unix__
    system("clear");
#elif defined(WIN32) || defined(WIN64)
    system("cls");
#endif
}
