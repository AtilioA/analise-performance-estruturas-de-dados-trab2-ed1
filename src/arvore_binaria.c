#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/indexador.h"
#include "../include/arvore_binaria.h"

ArvBin *cria_ArvBin()
{
    ArvBin *nova = (ArvBin *)malloc(sizeof(ArvBin));
    (*nova) = NULL;
    return nova;
}

void imprime_em_ordem_ArvBin(ArvBin *raiz)
{
    if (raiz != NULL)
    {
        if ((*raiz)->esq != NULL)
        {
            imprime_em_ordem_ArvBin(&((*raiz)->esq));
        }
        imprime_Palavra((*raiz)->palavra);
        if ((*raiz)->dir != NULL)
        {
            imprime_em_ordem_ArvBin(&((*raiz)->dir));
        }
    }
}

int insere_ArvBin(ArvBin *raiz, Palavra *palavra)
{
    if (raiz != NULL)
    {
        No *novo = malloc(sizeof(No));
        novo->esq = NULL;
        novo->dir = NULL;
        novo->palavra = palavra;
        No *aux = (*raiz);
        if ((*raiz) == NULL)
        {
            (*raiz) = novo;
            aux = (*raiz);
            return 1;
        }

        while (aux->esq != NULL || aux->dir != NULL)
        {

            if (strcasecmp(palavra->string, aux->palavra->string) < 0)
            {
                if (aux->esq == NULL)
                {
                    break;
                }
                aux = aux->esq;
            }
            else if (strcasecmp(palavra->string, aux->palavra->string) > 0)
            {
                if (aux->dir == NULL)
                {
                    break;
                }
                aux = aux->dir;
            }
            else
            {
                insere_Arq(palavra->arquivos->primeiro->nomeArquivo, aux->palavra->arquivos, palavra->arquivos->primeiro->ocorrencias->primeiro->ocorreu);
                libera_No(novo);
                return 0; // Valor já presente na árvore
            }
        }

        if (strcasecmp(palavra->string, aux->palavra->string) < 0)
        {
            aux->esq = novo;
            return 1;
        }
        else if (strcasecmp(palavra->string, aux->palavra->string) > 0)
        {
            aux->dir = novo;
            return 1;
        }
        else
        {
            insere_Arq(palavra->arquivos->primeiro->nomeArquivo, aux->palavra->arquivos, palavra->arquivos->primeiro->ocorrencias->primeiro->ocorreu);
            libera_No(novo);
            return 0; // Valor já presente na árvore
        }
    }
    else
    {
        return 0;
    }
}

Palavra *busca_ArvBin(ArvBin *raiz, char *strat)
{
    if (raiz == NULL)
        return 0;
    struct No *atual = *raiz;
    while (atual != NULL)
    {
        if (!strcasecmp(atual->palavra->string, strat))
        {
            return atual->palavra;
        }
        if (strcasecmp(strat, atual->palavra->string) > 0)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return NULL;
}

void libera_No(struct No *no)
{
    if (no != NULL)
    {
        libera_Palavra(no->palavra);
        libera_No(no->esq);
        libera_No(no->dir);
        free(no);
        no = NULL;
    }
}

void libera_ArvBin(ArvBin *raiz)
{
    if (raiz == NULL)
    {
        return;
    }
    libera_No(*raiz);
    free(raiz);
}
