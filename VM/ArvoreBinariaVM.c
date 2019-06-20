#include <stdio.h>
#include <stdlib.h>
#include "arvore_binaria.h" //inclui os Prot�tipos

// Já mesclada com biblioteca arvore_binaria

struct No
{
    int info;
    struct No *esq;
    struct No *dir;
};

ArvBin *cria_ArvBin()
{
    ArvBin *raiz = (ArvBin *)malloc(sizeof(ArvBin));
    if (raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_No(struct No *no)
{
    if (no == NULL)
        return;
    libera_No(no->esq);
    libera_No(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvBin(ArvBin *raiz)
{
    if (raiz == NULL)
        return;
    libera_No(*raiz); //libera cada n�
    free(raiz);       //libera a raiz
}

int insere_ArvBin(ArvBin *raiz, int valor)
{

    if (*raiz == NULL)
    {
        struct No *novo;
        novo = (struct No *)malloc(sizeof(struct No));
        if (novo == NULL)
            return 0;
        novo->info = valor;
        novo->dir = NULL;
        novo->esq = NULL;

        *raiz = novo;
    }
    else
    {
        if (valor == (*raiz)->info)
            return 0; //elemento j� existe
        else if (valor > (*raiz)->info)
            return insere_ArvBin(&(*raiz)->dir, valor);
        else
            return insere_ArvBin(&(*raiz)->esq, valor);
    }
    return 1;
}

// http://www.ime.usp.br/~pf/algoritmos/aulas/binst.html
int remove_ArvBin(ArvBin *raiz, int valor)
{
    if (raiz == NULL)
        return 0;
    struct No *ant = NULL;
    struct No *atual = *raiz;
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

int esta_vazia_ArvBin(ArvBin *raiz)
{
    if (raiz == NULL)
        return 1;
    if (*raiz == NULL)
        return 1;
    return 0;
}

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

int consulta_ArvBin(ArvBin *raiz, int valor)
{
    if (raiz == NULL)
        return 0;
    struct No *atual = *raiz;
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

void preOrdem_ArvBin(ArvBin *raiz)
{
    if (raiz == NULL)
        return;
    if (*raiz != NULL)
    {
        printf("%d\n", (*raiz)->info);
        preOrdem_ArvBin(&((*raiz)->esq));
        preOrdem_ArvBin(&((*raiz)->dir));
    }
}

void emOrdem_ArvBin(ArvBin *raiz)
{
    if (raiz == NULL)
        return;
    if (*raiz != NULL)
    {
        emOrdem_ArvBin(&((*raiz)->esq));
        printf("%d\n", (*raiz)->info);
        emOrdem_ArvBin(&((*raiz)->dir));
    }
}

void posOrdem_ArvBin(ArvBin *raiz)
{
    if (raiz == NULL)
        return;
    if (*raiz != NULL)
    {
        posOrdem_ArvBin(&((*raiz)->esq));
        posOrdem_ArvBin(&((*raiz)->dir));
        printf("%d\n", (*raiz)->info);
    }
}
