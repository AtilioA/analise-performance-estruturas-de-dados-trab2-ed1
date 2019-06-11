#include "ArvoreBinaria.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct NO
{
    int info;
    struct NO *esq;
    struct NO *dir;
} tNo;

ArvBin *criaArvBin()
{
    ArvBin *nova = (ArvBin *)malloc(sizeof(ArvBin));
    (*nova) = NULL;
    return nova;
}

int ehFolha(tNo *no)
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

// Calma, tô implementando
/*
Conta o número de nós não-folha de uma árvore binária
retorna: Numero de nós não folha
*/
int totalNaoFolhaArvbin(ArvBin *raiz)
{
    if (raiz != NULL)
    {
        printf("%d\n", (*raiz)->info);
        if ((*raiz)->esq != NULL)
        {
            preOrdemArvBin(&((*raiz)->esq));
        }
        if ((*raiz)->dir != NULL)
        {
            preOrdemArvBin(&((*raiz)->dir));
        }
    }
}

/**
Conta o número de folhas de uma árvore binária.
retorna: Numero de nós folhas
*/
int totalFolhaArvbin(ArvBin *raiz);

/*conta o número de nós de uma árvore binária. */
int totalNOsArvBin(ArvBin *raiz);


/** Imprime em pré-ordem */
void preOrdemArvBin(ArvBin *raiz)
{
    if (raiz != NULL)
    {
        printf("%d\n", (*raiz)->info);
        if ((*raiz)->esq != NULL)
        {
            preOrdemArvBin(&((*raiz)->esq));
        }
        if ((*raiz)->dir != NULL)
        {
            preOrdemArvBin(&((*raiz)->dir));
        }
    }
}

/** Imprime em-ordem */
void emOrdemArvBin(ArvBin *raiz)
{
    if (raiz != NULL)
    {
        if ((*raiz)->esq != NULL)
        {
            preOrdemArvBin(&((*raiz)->esq));
        }
        printf("%d\n", (*raiz)->info);
        if ((*raiz)->dir != NULL)
        {
            preOrdemArvBin(&((*raiz)->dir));
        }
    }
}

/** Imprime em pós-ordem */
void posOrdemArvBin(ArvBin *raiz)
{
    if (raiz != NULL)
    {
        if ((*raiz)->esq != NULL)
        {
            preOrdemArvBin(&((*raiz)->esq));
        }
        if ((*raiz)->dir != NULL)
        {
            preOrdemArvBin(&((*raiz)->dir));
        }
        printf("%d\n", (*raiz)->info);
    }
}

int insereArvBin(ArvBin *raiz, int valor)
{
    if (raiz != NULL)
    {
        tNo *novo = malloc(sizeof(tNo));
        novo->esq = NULL;
        novo->dir = NULL;
        novo->info = valor;
        tNo *aux = (*raiz);

        if ((*raiz) == NULL)
        {
            (*raiz) = novo;
            return 1;
        }

        while (aux->esq != NULL || aux->dir != NULL)
        {
            if (valor < aux->info)
            {
                if (aux->esq == NULL)
                {
                    break;
                }
                aux = aux->esq;
            }
            else if (valor > aux->info)
            {
                if (aux->dir == NULL)
                {
                    break;
                }
                aux = aux->dir;
            }
            else
            {
                return 0; // Valor já presente na árvore
            }
        }

        if (valor < aux->info)
        {
            aux->esq = novo;
            return 1;
        }
        else if (valor > aux->info)
        {
            aux->dir = novo;
            return 1;
        }
    }
    else
    {
        return 0;
    }
}


int consultaArvBin(ArvBin *raiz, int valor)
{
    tNo *aux = (*raiz);
    if (raiz != NULL)
    {
        while (aux->esq != NULL || aux->dir != NULL)
        {
            if (valor < aux->info)
            {
                if (aux->esq == NULL)
                {
                    break;
                }
                aux = aux->esq;
            }
            else if (valor > aux->info)
            {
                if (aux->dir == NULL)
                {
                    break;
                }
                aux = aux->dir;
            }
            else
            {
                return 1; // Valor presente na árvore
            }
        }

        return 0;
    }
    else
    {
        return 1;
    }

    return 0;
}

/** Libera em pós-ordem */
void liberaArvBin(ArvBin *raiz)
{
    if (raiz != NULL)
    {
        if ((*raiz)->esq != NULL)
        {
            liberaArvBin(&((*raiz)->esq));
        }
        if ((*raiz)->dir != NULL)
        {
            liberaArvBin(&((*raiz)->dir));
        }
        free((*raiz));
    }
}
