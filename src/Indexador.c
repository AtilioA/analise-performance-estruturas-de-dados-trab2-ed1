#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Indexador.h"

void imprimeVetH(int *vet, int tamVet)
{
    int i = 0;
    
    for (i = 0; i < tamVet; i++)
    {
        printf("%i ", vet[i]);
    }
}
char *String(tPalavra *palavra)
{
    if(palavra == NULL){
        return NULL;
    }
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

void ImprimePalavra(tPalavra *palavra)
{
    printf("Palavra: %s\n", String(palavra));
    printf("Ocorrencias: %i\n\n", Ocorrencias(palavra));
    // nao vo printa vetor
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
    nova->ocorrencias = 1;

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
