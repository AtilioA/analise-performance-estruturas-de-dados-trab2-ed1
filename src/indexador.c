#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/indexador.h"

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
    return palavra->ocorrencias->qtd;
}

ListaOcorrencias *get_posicoes(Palavra *palavra)
{
    return palavra->ocorrencias;
}

void imprime_Palavra(Palavra *palavra)
{
    printf("Palavra: %s\n", get_string(palavra));
    printf("Ocorrencias: ");
    tOcorre *aux = get_posicoes(palavra)->primeiro;
    for (int i = 0; i < get_ocorrencias(palavra); i++)
    {
        printf("%d ", aux->ocorreu);
        aux = aux->prox;
    } // mas eu vo, caralho
    printf("\n");
}

ListaOcorrencias *nova_Ocorrencias()
{
    ListaOcorrencias *novo = malloc(sizeof(ListaOcorrencias));
    novo->primeiro = NULL;
    novo->ultimo = NULL;
    novo->qtd = 0;
    return novo;
}

void insere_Ocorrencias(ListaOcorrencias *l, int ocorre)
{
    tOcorre *nova = malloc(sizeof(tOcorre));
    nova->prox = NULL;
    nova->ocorreu = ocorre;
    if (l->primeiro == NULL)
    {
        l->primeiro = nova;
        l->ultimo = nova;
        return;
    }
    l->ultimo->prox = nova;
    l->ultimo = nova;
    return;
}

Palavra *cria_Palavra(char *string, int ocorre)
{
    Palavra *nova = (Palavra *)malloc(sizeof(Palavra)); // ponteiro?
    nova->string = malloc(sizeof(char) * strlen(string) + 1);
    nova->ocorrencias = nova_Ocorrencias();
    nova->ocorrencias->qtd = 1;
    strcpy(nova->string, string);
    insere_Ocorrencias(nova->ocorrencias, ocorre);
    return nova;
}

void destroi_Ocorrencias(ListaOcorrencias *ocorres)
{
    tOcorre *ant = NULL;
    tOcorre *aux = ocorres->primeiro;
    while (aux != NULL)
    {
        ant = aux;
        aux = aux->prox;
        free(ant);
    }
    free(ocorres);
}

void destroi_Palavra(Palavra *palavra)
{
    free(palavra->string);
    destroi_Ocorrencias(palavra->ocorrencias);
    free(palavra);
}

SentRandPal *cria_RandPal()
{
    SentRandPal *novo = malloc(sizeof(SentRandPal));
    novo->primeiro = NULL;
    novo->ultimo = NULL;
    novo->qtd = 0;
    return novo;
}

void insere_RandPal(char *strat, SentRandPal *l)
{
    tRandPal *pal = malloc(sizeof(tRandPal));
    pal->string = malloc(sizeof(char) * strlen(strat) + 1);
    strcpy(pal->string, strat);
    pal->prox = NULL;
    if (l->primeiro == NULL)
    {
        l->primeiro = pal;
        l->ultimo = pal;
        return;
    }
    l->ultimo->prox = pal;
    l->ultimo = l->ultimo->prox;
    l->qtd++;
}

void destroi_RandPal(SentRandPal *l)
{
    tRandPal *ant;
    tRandPal *aux = l->primeiro;
    while (aux != NULL)
    {
        ant = aux;
        aux = aux->prox;
        free(ant->string);
        free(ant);
    }
    free(l);
}

char *busca_RandPal(int indice, SentRandPal *l)
{
    tRandPal *aux = l->primeiro;
    for (int i = 0; i < indice && i < l->qtd; i++)
    {
        aux = aux->prox;
    }
    return aux->string;
}

void clr_scr()
{
#ifdef __unix__
    system("clear");
#elif defined(WIN32) || defined(WIN64)
    system("cls");
#endif
}
