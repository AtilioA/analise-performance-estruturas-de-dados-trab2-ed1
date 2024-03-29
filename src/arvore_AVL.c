#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/arvore_AVL.h"

ArvAVL *cria_ArvAVL()
{
    ArvAVL *raiz = (ArvAVL *)malloc(sizeof(ArvAVL));
    if (raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_ArvAVL(ArvAVL *raiz)
{
    if (raiz != NULL)
    {
        libera_No(*raiz); // libera cada nó
        free(raiz);       // libera a raiz
    }
}

int altura_No(struct No *no)
{
    if (no == NULL)
    {
        return -1;
}
    else
    {
        return no->altura;
    }
}

int fator_balanceamento_No(struct No *no)
{
    return labs(altura_No(no->esq) - altura_No(no->dir));
}

int maior(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}

void imprime_pre_ordem_ArvAVL(ArvAVL *raiz)
{
    if (raiz == NULL)
        return;
    if (*raiz != NULL)
    {
        imprime_Palavra((*raiz)->palavra);
        imprime_pre_ordem_ArvAVL(&((*raiz)->esq));
        imprime_pre_ordem_ArvAVL(&((*raiz)->dir));
    }
}

void imprime_em_ordem_ArvAVL(ArvAVL *raiz)
{
    if (raiz == NULL)
        return;
    if (*raiz != NULL)
    {
        imprime_em_ordem_ArvAVL(&((*raiz)->esq));
        imprime_Palavra((*raiz)->palavra);
        imprime_em_ordem_ArvAVL(&((*raiz)->dir));
    }
}

Palavra *busca_ArvAVL(ArvAVL *raiz, char *stringBuscada)
{
    if (raiz == NULL)
    {
        return 0;
    }
    struct No *atual = *raiz;
    while (atual != NULL)
    {
        if (!strcasecmp(atual->palavra->string, stringBuscada))
        {
            return atual->palavra;
        }
        if (strcasecmp(stringBuscada, atual->palavra->string) > 0)
        {
            atual = atual->dir;
        }
        else
        {
            atual = atual->esq;
        }
    }
    return NULL;
}

/* LR = Left rotation
 * RR = Right rotation
 * LRR = Left-right rotation
 * RLR = Right-left rotation
 */

void rotacao_LR(ArvAVL *A)
{
    struct No *B;

    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(altura_No((*A)->esq), altura_No((*A)->dir)) + 1;
    B->altura = maior(altura_No(B->esq), (*A)->altura) + 1;
    *A = B;
}

void rotacao_RR(ArvAVL *A)
{
    struct No *B;

    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(altura_No((*A)->esq), altura_No((*A)->dir)) + 1;
    B->altura = maior(altura_No(B->dir), (*A)->altura) + 1;
    (*A) = B;
}

void rotacao_LRR(ArvAVL *A)
{
    rotacao_RR(&(*A)->esq);
    rotacao_LR(A);
}

void rotacao_RLR(ArvAVL *A)
{
    rotacao_LR(&(*A)->dir);
    rotacao_RR(A);
}

int insere_ArvAVL(ArvAVL *raiz, Palavra *palavra)
{
    int res;
    if (*raiz == NULL)
    { //Arvore vazia ou no folha
        struct No *novo;
        novo = (struct No *)malloc(sizeof(struct No));
        if (novo == NULL)
            return 0;

        novo->palavra = palavra;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct No *atual = *raiz;
    if (strcasecmp(palavra->string, atual->palavra->string) < 0)
    {
        if ((res = insere_ArvAVL(&(atual->esq), palavra)) == 1)
        {
            if (fator_balanceamento_No(atual) >= 2)
            {
                if (strcasecmp(palavra->string, atual->esq->palavra->string) < 0)
                {
                    rotacao_LR(raiz);
                }
                else
                {
                    rotacao_LRR(raiz);
                }
            }
        }
    }
    else
    {
        if (strcasecmp(palavra->string, atual->palavra->string) > 0)
        {
            if ((res = insere_ArvAVL(&(atual->dir), palavra)) == 1)
            {
                if (fator_balanceamento_No(atual) >= 2)
                {
                    if (strcasecmp((*raiz)->dir->palavra->string, palavra->string) < 0)
                    {
                        rotacao_RR(raiz);
                    }
                    else
                    {
                        rotacao_RLR(raiz);
                    }
                }
            }
        }
        else
        {
            insere_Arq(palavra->arquivos->primeiro->nomeArquivo, atual->palavra->arquivos, palavra->arquivos->primeiro->ocorrencias->primeiro->ocorreu);
            libera_Palavra(palavra);
            //  printf("Valor duplicado!!\n");
            return 0;
        }
    }

    atual->altura = maior(altura_No(atual->esq), altura_No(atual->dir)) + 1;

    return res;
}
