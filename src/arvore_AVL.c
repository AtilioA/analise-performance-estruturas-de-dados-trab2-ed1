#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/arvore_AVL.h"

ArvAVL *cria_ArvAVL()
{
    ArvAVL *raiz = (ArvAVL *)malloc(sizeof(ArvAVL));
    if (raiz != NULL)
        *raiz = NULL;
    return raiz;
}

/*
void libera_No(struct No *no)
{
    if (no == NULL)
        return;
    libera_No(no->esq);
    libera_No(no->dir);
    free(no);
    no = NULL;
}
*/

void libera_ArvAVL(ArvAVL *raiz)
{
    if (raiz == NULL)
        return;
    libera_No(*raiz); //libera cada n�
    free(raiz);       //libera a raiz
}

int altura_No(struct No *no)
{
    if (no == NULL)
        return -1;
    else
        return no->altura;
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

int esta_vazia_arv_avl(ArvAVL *raiz)
{
    if (raiz == NULL)
        return 1;
    if (*raiz == NULL)
        return 1;
    return 0;
}

int total_No_ArvAVL(ArvAVL *raiz)
{
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = total_No_ArvAVL(&((*raiz)->esq));
    int alt_dir = total_No_ArvAVL(&((*raiz)->dir));
    return (alt_esq + alt_dir + 1);
}

int altura_ArvAVL(ArvAVL *raiz)
{
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvAVL(&((*raiz)->esq));
    int alt_dir = altura_ArvAVL(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return (alt_dir + 1);
}

void imprime_pre_ordem_ArvAVL(ArvAVL *raiz)
{
    if (raiz == NULL)
        return;
    if (*raiz != NULL)
    {
        //printf("No %d: %d\n",(*raiz)->info,fator_balanceamento_No(*raiz));
        //printf("No %d: %d\n", (*raiz)->info, altura_No(*raiz));
        imprime_Palavra((*raiz)->pal);
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
        imprime_Palavra((*raiz)->pal);
        imprime_em_ordem_ArvAVL(&((*raiz)->dir));
    }
}

void imprime_pos_ordem_ArvAVL(ArvAVL *raiz)
{
    if (raiz == NULL)
        return;
    if (*raiz != NULL)
    {
        imprime_pos_ordem_ArvAVL(&((*raiz)->esq));
        imprime_pos_ordem_ArvAVL(&((*raiz)->dir));
        imprime_Palavra((*raiz)->pal);
    }
}

Palavra *busca_ArvAVL(ArvAVL *raiz, char *strat)
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


/* LR = Left rotation
 * RL = Right rotation
 * LRR = Left-right rotation
 * RLR = Right-left rotation
 */

void rotacao_LR(ArvAVL *A)
{
    //printf("rotacao_LR\n");
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
    //printf("rotacao_RR\n");
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
{ //RL
    rotacao_LR(&(*A)->dir);
    rotacao_RR(A);
}

int insere_ArvAVL(ArvAVL *raiz, Palavra *pal)
{
    int res;
    if (*raiz == NULL)
    { //Arvore vazia ou no folha
        struct No *novo;
        novo = (struct No *)malloc(sizeof(struct No));
        if (novo == NULL)
            return 0;

        novo->pal = pal;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct No *atual = *raiz;
    if (strcasecmp(pal->string, atual->pal->string) < 0)
    {
        if ((res = insere_ArvAVL(&(atual->esq), pal)) == 1)
        {
            if (fator_balanceamento_No(atual) >= 2)
            {
                if (strcasecmp(pal->string, atual->esq->pal->string) < 0)
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
        if (strcasecmp(pal->string, atual->pal->string) > 0)
        {
            if ((res = insere_ArvAVL(&(atual->dir), pal)) == 1)
            {
                if (fator_balanceamento_No(atual) >= 2)
                {
                    if (strcasecmp((*raiz)->dir->pal->string, pal->string) < 0)
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
            insere_Arq(x->arquivos->primeiro->nomeArquivo, aux->palavra->arquivos, x->arquivos->primeiro->ocorrencias->primeiro->ocorreu);
            libera_Palavra(pal);
            //  printf("Valor duplicado!!\n");
            return 0;
        }
    }

    atual->altura = maior(altura_No(atual->esq), altura_No(atual->dir)) + 1;

    return res;
}

struct No *procura_menor(struct No *atual)
{
    struct No *no1 = atual;
    struct No *no2 = atual->esq;
    while (no2 != NULL)
    {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}
