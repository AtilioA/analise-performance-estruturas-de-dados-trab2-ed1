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

void imprime_Palavra(Palavra *palavra)
{
    printf("\nPalavra: %s\n", get_string(palavra));
    Arq *aux = palavra->arquivos->primeiro;
    while (aux != NULL)
    {
        printf("Arquivo: %s\n", aux->nomeArquivo);
        CelulaOcorre *ocorres = aux->ocorrencias->primeiro;
        printf("Ocorrencias: ");
        while (ocorres != NULL)
        {
            printf("%d ", ocorres->ocorreu);
            ocorres = ocorres->prox;
        }
        aux = aux->prox;
        printf("\n");
    }
    printf("\n\n");
}

ListaOcorre *nova_Ocorrencias()
{
    ListaOcorre *novo = malloc(sizeof(ListaOcorre));
    novo->primeiro = NULL;
    novo->ultimo = NULL;
    novo->qtd = 0;
    return novo;
}

void insere_Ocorrencias(ListaOcorre *l, int ocorre)
{
    CelulaOcorre *nova = malloc(sizeof(CelulaOcorre));
    nova->prox = NULL;
    nova->ocorreu = ocorre;
    if (l->primeiro == NULL)
    {
        l->primeiro = nova;
        l->ultimo = nova;
        l->qtd = 1;
        return;
    }
    l->ultimo->prox = nova;
    l->ultimo = nova;
    l->qtd++;
    return;
}

ListaArq *cria_Arq()
{
    ListaArq *novo = malloc(sizeof(ListaArq));
    novo->primeiro = NULL;
    novo->ultimo = NULL;
    return novo;
}

Palavra *cria_Palavra(char *nomeArquivo, char *string, int ocorre)
{
    Palavra *nova = malloc(sizeof(Palavra));
    nova->string = malloc(sizeof(char) * strlen(string) + 1);
    strcpy(nova->string, string);
    nova->arquivos = cria_Arq();
    insere_Arq(nomeArquivo, nova->arquivos, ocorre);
    return nova;
}

void insere_Arq(char *nomeArquivo, ListaArq *arquivos, int ocorre)
{
    Arq *aux = arquivos->primeiro;
    if (aux == NULL)
    {
        arquivos->primeiro = malloc(sizeof(Arq));
        arquivos->primeiro->nomeArquivo = nomeArquivo;
        arquivos->primeiro->ocorrencias = nova_Ocorrencias();
        insere_Ocorrencias(arquivos->primeiro->ocorrencias, ocorre);
        arquivos->primeiro->prox = NULL;
        arquivos->ultimo = arquivos->primeiro;
        return;
    }

    while (aux != NULL && strcmp(nomeArquivo, aux->nomeArquivo))
    {
        aux = aux->prox;
    }
    if (aux == NULL)
    {
        arquivos->ultimo->prox = malloc(sizeof(Arq));
        arquivos->ultimo = arquivos->ultimo->prox;
        arquivos->ultimo->nomeArquivo = nomeArquivo;
        arquivos->ultimo->prox = NULL;
        arquivos->ultimo->ocorrencias = nova_Ocorrencias();
        insere_Ocorrencias(arquivos->ultimo->ocorrencias, ocorre);
        return;
    }
    insere_Ocorrencias(aux->ocorrencias, ocorre);
}

void libera_Ocorrencias(ListaOcorre *ocorres)
{
    CelulaOcorre *ant = NULL;
    CelulaOcorre *aux = ocorres->primeiro;
    while (aux != NULL)
    {
        ant = aux;
        aux = aux->prox;
        free(ant);
    }
    free(ocorres);
}

void libera_Arqs(ListaArq *arquivos)
{
    Arq *aux = arquivos->primeiro;
    Arq *ant = NULL;
    while (aux != NULL)
    {
        ant = aux;
        aux = aux->prox;
        libera_Ocorrencias(ant->ocorrencias);
        free(ant);
    }
    free(arquivos);
}

void libera_Palavra(Palavra *palavra)
{
    free(palavra->string);
    libera_Arqs(palavra->arquivos);
    free(palavra);
}

ListaRandPal *cria_RandPal()
{
    ListaRandPal *novo = malloc(sizeof(ListaRandPal));
    novo->primeiro = NULL;
    novo->ultimo = NULL;
    novo->qtd = 0;
    return novo;
}

void insere_RandPal(char *strat, ListaRandPal *l)
{
    CelulaRandPal *palavra = malloc(sizeof(CelulaRandPal));
    palavra->string = malloc(sizeof(char) * strlen(strat) + 1);
    strcpy(palavra->string, strat);
    palavra->prox = NULL;
    if (l->primeiro == NULL)
    {
        l->primeiro = palavra;
        l->ultimo = palavra;
        return;
    }
    l->ultimo->prox = palavra;
    l->ultimo = l->ultimo->prox;
    l->qtd++;
}

void libera_RandPal(ListaRandPal *l)
{
    CelulaRandPal *ant;
    CelulaRandPal *aux = l->primeiro;
    while (aux != NULL)
    {
        ant = aux;
        aux = aux->prox;
        free(ant->string);
        free(ant);
    }
    free(l);
}

char *busca_RandPal(int indice, ListaRandPal *l)
{
    CelulaRandPal *aux = l->primeiro;
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
