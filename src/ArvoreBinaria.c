#include "../include/ArvoreBinaria.h"
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

int estaVazia_ArvBin(ArvBin *raiz)
{
    if (raiz == NULL)
        return 1;
    if (*raiz == NULL)
        return 1;
    return 0;
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
Conta o número de nós-folha de uma árvore binária
retorna: Numero de nós folha
*/
int totalFolhaArvbin(ArvBin *raiz)
{
    int folhas = 0;
    if (raiz != NULL && *raiz != NULL)
    {
        if (ehFolha(*raiz))
        {
            folhas++;
        }
        if ((*raiz)->esq != NULL)
        {
            int folhasEsq = totalFolhaArvbin(&((*raiz)->esq));
        }
        if ((*raiz)->dir != NULL)
        {
            int folhasDir = totalFolhaArvbin(&((*raiz)->dir));
        }
    }

    return folhas;
}

/**
Conta o número de folhas de uma árvore binária.
retorna: Numero de nós folhas
*/
int totalFolhaArvbin(ArvBin *raiz);

/*conta o número de nós de uma árvore binária. */
int totalNO_ArvBin(ArvBin *raiz)
{
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = totalNO_ArvBin(&((*raiz)->esq));
    int alt_dir = totalNO_ArvBin(&((*raiz)->dir));
    return (alt_esq + alt_dir + 1);
}

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

int remove_ArvBin(ArvBin *raiz, int valor)
{
    if (raiz == NULL)
        return 0;
    struct NO *ant = NULL;
    struct NO *atual = *raiz;
    while (atual != NULL)
    {
        if (valor == atual->info)
        {
            if (atual == *raiz)
                *raiz = remove_atual(atual);
            else
            {
                if (ant->dir == atual)
                    ant->dir = remove_atual(atual);
                else
                    ant->esq = remove_atual(atual);
            }
            return 1;
        }
        ant = atual;
        if (valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

int consulta_ArvBin(ArvBin *raiz, int valor)
{
    if (raiz == NULL)
        return 0;
    struct NO *atual = *raiz;
    while (atual != NULL)
    {
        if (valor == atual->info)
        {
            return 1;
        }
        if (valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

void libera_NO(struct NO *no)
{
    if (no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
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
