#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Indexador.h"

void imprime_vet_h(int *vet, int tamVet)
{
    int i = 0;

    for (i = 0; i < tamVet; i++)
    {
        printf("%i ", vet[i]);
    }
}
char *get_string(Palavra *palavra)
{
    if (palavra == NULL)
    {
        return NULL;
    }
    return palavra->string;
}

int get_ocorrencias(Palavra *palavra)
{
    return palavra->ocorrencias;
}

int *get_posicoes(Palavra *palavra)
{
    return palavra->posicoes;
}

void imprime_Palavra(Palavra *palavra)
{
    printf("Palavra: %s\n", get_string(palavra));
    printf("Ocorrencias: %i\n\n", Ocorrencias(palavra));
    // nao vo printa vetor
}

Palavra *cria_Palavra(char *string)
{
    Palavra *nova = (Palavra *)malloc(sizeof(Palavra)); // ponteiro?

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

Palavra *inicia_Palavra()
{
    Palavra *nova = (Palavra *)malloc(sizeof(Palavra)); // ponteiro?

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

void destroi_Palavra(Palavra *palavra)
{
    free(palavra->string);
    free(palavra->posicoes);
    palavra->ocorrencias = -1;
}

void clr_scr()
{
#ifdef __unix__
    system("clear");
#elif defined(WIN32) || defined(WIN64)
    system("cls");
#endif
}
