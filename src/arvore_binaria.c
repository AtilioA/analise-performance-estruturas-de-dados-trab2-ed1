#include <stdio.h>
#include <stdlib.h>
#include "../include/indexador.h"
#include "../include/arvore_binaria.h"

ArvBin *criaArvBin()
{
    ArvBin *nova = (ArvBin *)malloc(sizeof(ArvBin));
    (*nova) = NULL;
    return nova;
}

int esta_vazia_ArvBin(ArvBin *raiz)
{
    if (raiz == NULL)
        return 1;
    if (*raiz == NULL)
        return 1;
    return 0;
}

int eh_folha(No *no)
{
    if (no == NULL)
    {
        return 0;
    }
    else
    {
        return no->esq == no->dir == NULL;
    }
}

/* Não lembro se está funcionando
Conta o número de nós-folha de uma árvore binária
retorna: Numero de nós folha
*/
int total_folha_ArvBin(ArvBin *raiz)
{
    int folhas = 0;
    if (raiz != NULL && *raiz != NULL)
    {
        if (eh_folha(*raiz))
        {
            folhas++;
        }
        if ((*raiz)->esq != NULL)
        {
            int folhasEsq = total_folha_ArvBin(&((*raiz)->esq));
        }
        if ((*raiz)->dir != NULL)
        {
            int folhasDir = total_folha_ArvBin(&((*raiz)->dir));
        }
    }

    return folhas;
}

/**
Conta o número de folhas de uma árvore binária.
retorna: Numero de nós folhas
*/
int total_folha_ArvBin(ArvBin *raiz);

/*conta o número de nós de uma árvore binária. */
int total_No_ArvBin(ArvBin *raiz)
{
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = total_No_ArvBin(&((*raiz)->esq));
    int alt_dir = total_No_ArvBin(&((*raiz)->dir));
    return (alt_esq + alt_dir + 1);
}
/*
* Imprime em pré-ordem /
void imprime_pre_ordem_ArvBin(ArvBin *raiz)
{
    if (raiz != NULL)
    {
        printf("%d\n", (*raiz)->info);
        if ((*raiz)->esq != NULL)
        {
            imprime_pre_ordem_ArvBin(&((*raiz)->esq));
        }
        if ((*raiz)->dir != NULL)
        {
            imprime_pre_ordem_ArvBin(&((*raiz)->dir));
        }
    }
}
*/
// Imprime em-ordem
void imprime_em_ordem_ArvBin(ArvBin *raiz)
{
    if (raiz != NULL)
    {
        if ((*raiz)->esq != NULL)
        {
            imprime_em_ordem_ArvBin(&((*raiz)->esq));
        }
        imprime_Palavra((*raiz)->pal);
        if ((*raiz)->dir != NULL)
        {
            imprime_em_ordem_ArvBin(&((*raiz)->dir));
        }
    }
}

/*Imprime em pós-ordem
void imprime_pos_ordem_ArvBin(ArvBin *raiz)
{
    if (raiz != NULL)
    {
        if ((*raiz)->esq != NULL)
        {
            imprime_pos_ordem_ArvBin(&((*raiz)->esq));
        }
        if ((*raiz)->dir != NULL)
        {
            imprime_pos_ordem_ArvBin(&((*raiz)->dir));
        }
        printf("%d\n", (*raiz)->info);
    }
}

/*
int altura_ArvBin(ArvBin *raiz)
{
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvBin(&((*raiz)->esq));
    int alt_dir = altura_ArvBin(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return (alt_dir + 1);
}
*/

int insere_ArvBin(ArvBin *raiz, Palavra *pal)
{
    if (raiz != NULL)
    {
        No *novo = malloc(sizeof(No));
        novo->esq = NULL;
        novo->dir = NULL;
        novo->pal = pal;
        No *aux = (*raiz);
        if ((*raiz) == NULL)
        {
            (*raiz) = novo;
            aux = (*raiz);
            return 1;
        }

        while (aux->esq != NULL || aux->dir != NULL)
        {

            if (strcasecmp(pal->string, aux->pal->string) < 0)
            {
                if (aux->esq == NULL)
                {
                    break;
                }
                aux = aux->esq;
            }
            else if (strcasecmp(pal->string, aux->pal->string) > 0)
            {
                if (aux->dir == NULL)
                {
                    break;
                }
                aux = aux->dir;
            }
            else
            {
                insere_Ocorrencias(aux->pal->ocorrencias, pal->ocorrencias->primeiro->ocorreu);
                aux->pal->ocorrencias->qtd++;
                libera_No(novo);
                return 0; // Valor já presente na árvore
            }
        }

        if (strcasecmp(pal->string, aux->pal->string) < 0)
        {
            aux->esq = novo;
            return 1;
        }
        else if (strcasecmp(pal->string, aux->pal->string) > 0)
        {
            aux->dir = novo;
            return 1;
        }
        else
        {
            insere_Ocorrencias(aux->pal->ocorrencias, pal->ocorrencias->primeiro->ocorreu);
            aux->pal->ocorrencias->qtd++;
            libera_No(novo);
            return 0; // Valor já presente na árvore
        }
    }
    else
    {
        return 0;
    }
}

Palavra *consulta_ArvBin(ArvBin *raiz, char *strat)
{
    if (raiz == NULL)
        return 0;
    struct No *atual = *raiz;
    while (atual != NULL)
    {
        if (!strcasecmp(atual->pal->string, strat))
        {
            return atual->pal;
        }
        if (strcasecmp(strat, atual->pal->string) > 0)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return NULL;
}

void libera_No(struct No *no)
{
    if (no == NULL)
        return;
    libera_Palavra(no->pal);
    libera_No(no->esq);
    libera_No(no->dir);
    free(no);
    no = NULL;
}

/** Libera em pós-ordem */
void libera_ArvBin(ArvBin *raiz)
{
    if (raiz == NULL)
    {
        return;
    }
    libera_No(*raiz);
    free(raiz);
}
