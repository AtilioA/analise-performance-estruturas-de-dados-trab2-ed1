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
/*
int get_ocorrencias(Palavra *palavra)
{
    return palavra->ocorrencias->qtd;
}

ListaOcorr *get_posicoes(Palavra *palavra)
{
    return palavra->ocorrencias;
}
*/
void imprime_Palavra(Palavra *palavra)
{
    printf("\nPalavra: %s\n", get_string(palavra));
    Arq *aux = palavra->arquivos->primeiro;
    while(aux != NULL){
        printf("Arquivo: %s\n", aux->nomeArquivo);
        CelulaOcorr *ocorres = aux->ocorrencias->primeiro;
        printf("Ocorrencias: ");
        while(ocorres != NULL){
            printf("%d ", ocorres->ocorreu);
            ocorres = ocorres->prox;
        }
        aux = aux->prox;
        printf("\n");
    }
    printf("\n\n");
}

ListaOcorr *nova_Ocorrencias()
{
    ListaOcorr *novo = malloc(sizeof(ListaOcorr));
    novo->primeiro = NULL;
    novo->ultimo = NULL;
    novo->qtd = 0;
    return novo;
}

void insere_Ocorrencias(ListaOcorr *l, int ocorre)
{
    CelulaOcorr *nova = malloc(sizeof(CelulaOcorr));
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

ListaArq *cria_Arq(){
    ListaArq *novo = malloc(sizeof(ListaArq));
    novo->primeiro = NULL;
    novo->ultimo = NULL;
    return novo;
}

Palavra *cria_Palavra(char *nomeArquivo, char* string, int ocorre){
    Palavra *nova = malloc(sizeof(Palavra));
    nova->string = malloc(sizeof(char) * strlen(string) + 1);
    strcpy(nova->string, string);
    nova->arquivos = cria_Arq();
    insere_Arq(nomeArquivo, nova->arquivos, ocorre);
    return nova;
}

void insere_Arq(char *nomeArquivo, ListaArq *arquivos, int ocorre){
    Arq *aux = arquivos->primeiro;
    if(aux == NULL)
    {
        arquivos->primeiro = malloc(sizeof(Arq));
        arquivos->primeiro->nomeArquivo = nomeArquivo;
        arquivos->primeiro->ocorrencias = nova_Ocorrencias();
        insere_Ocorrencias(arquivos->primeiro->ocorrencias, ocorre);
        arquivos->primeiro->prox = NULL;
        arquivos->ultimo = arquivos->primeiro;
        return;
    }

    Arq *ant = NULL;
    while(aux != NULL && strcmp(nomeArquivo, aux->nomeArquivo))
    {
        aux = aux->prox;
    }
    if(aux == NULL)
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



/*
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
*/
void libera_Ocorrencias(ListaOcorr *ocorres)
{
    CelulaOcorr *ant = NULL;
    CelulaOcorr *aux = ocorres->primeiro;
    while (aux != NULL)
    {
        ant = aux;
        aux = aux->prox;
        free(ant);
    }
    free(ocorres);
}

void libera_Arqs(ListaArq *arquivos){
    Arq *aux = arquivos->primeiro;
    Arq *ant = NULL;
    while(aux != NULL){
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

void libera_RandPal(SentRandPal *l)
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

char *busca_RandPal(int indice, SentRandPal *l)
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
