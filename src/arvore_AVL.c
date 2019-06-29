#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/arvore_AVL.h" //inclui os Prot�tipos

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

void pre_ordem_ArvAVL(ArvAVL *raiz)
{
    if (raiz == NULL)
        return;
    if (*raiz != NULL)
    {
        //printf("%d\n",(*raiz)->info);
        //printf("No %d: %d\n",(*raiz)->info,fator_balanceamento_No(*raiz));
        //printf("No %d: %d\n", (*raiz)->info, altura_No(*raiz));
        imprime_Palavra((*raiz)->pal);
        pre_ordem_ArvAVL(&((*raiz)->esq));
        pre_ordem_ArvAVL(&((*raiz)->dir));
    }
}

void em_ordem_ArvAVL(ArvAVL *raiz)
{
    if (raiz == NULL)
        return;
    if (*raiz != NULL)
    {
        em_ordem_ArvAVL(&((*raiz)->esq));
        //printf("%d\n",(*raiz)->info);
        imprime_Palavra((*raiz)->pal);
        em_ordem_ArvAVL(&((*raiz)->dir));
    }
}

void pos_ordem_ArvAVL(ArvAVL *raiz)
{
    if (raiz == NULL)
        return;
    if (*raiz != NULL)
    {
        pos_ordem_ArvAVL(&((*raiz)->esq));
        pos_ordem_ArvAVL(&((*raiz)->dir));
        imprime_Palavra((*raiz)->pal);
    }
}

Palavra *consulta_ArvAVL(ArvAVL *raiz, char *strat)
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

//=================================
void rotacao_LL(ArvAVL *A)
{ //LL
    //printf("rotacao_LL\n");
    struct No *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(altura_No((*A)->esq), altura_No((*A)->dir)) + 1;
    B->altura = maior(altura_No(B->esq), (*A)->altura) + 1;
    *A = B;
}

void rotacao_RR(ArvAVL *A)
{ //RR
    //printf("rotacao_RR\n");
    struct No *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(altura_No((*A)->esq), altura_No((*A)->dir)) + 1;
    B->altura = maior(altura_No(B->dir), (*A)->altura) + 1;
    (*A) = B;
}

void rotacao_LR(ArvAVL *A)
{ //LR
    rotacao_RR(&(*A)->esq);
    rotacao_LL(A);
}

void rotacao_RL(ArvAVL *A)
{ //RL
    rotacao_LL(&(*A)->dir);
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
                    rotacao_LL(raiz);
                }
                else
                {
                    rotacao_LR(raiz);
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
                        rotacao_RL(raiz);
                    }
                }
            }
        }
        else
        {
            insereOcorre(atual->pal->ocorrencias, pal->ocorrencias->primeiro->ocorreu);
            atual->pal->ocorrencias->qtd++;
            destroi_Palavra(pal);
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
/*
int remove_ArvAVL(ArvAVL *raiz, int valor)
{
    if (*raiz == NULL)
    { // valor n�o existe
        printf("valor n�o existe!!\n");
        return 0;
    }

    int res;
    if (valor < (*raiz)->info)
    {
        if ((res = remove_ArvAVL(&(*raiz)->esq, valor)) == 1)
        {
            if (fator_balanceamento_No(*raiz) >= 2)
            {
                if (altura_No((*raiz)->dir->esq) <= altura_No((*raiz)->dir->dir))
                    rotacao_RR(raiz);
                else
                    rotacao_RL(raiz);
            }
        }
    }

    if ((*raiz)->info < valor)
    {
        if ((res = remove_ArvAVL(&(*raiz)->dir, valor)) == 1)
        {
            if (fator_balanceamento_No(*raiz) >= 2)
            {
                if (altura_No((*raiz)->esq->dir) <= altura_No((*raiz)->esq->esq))
                    rotacao_LL(raiz);
                else
                    rotacao_LR(raiz);
            }
        }
    }

    if ((*raiz)->info == valor)
    {
        if (((*raiz)->esq == NULL || (*raiz)->dir == NULL))
        { // n� tem 1 filho ou nenhum
            struct No *oldNode = (*raiz);
            if ((*raiz)->esq != NULL)
                *raiz = (*raiz)->esq;
            else
                *raiz = (*raiz)->dir;
            free(oldNode);
        }
        else
        { // n� tem 2 filhos
            struct No *temp = procura_menor((*raiz)->dir);
            (*raiz)->info = temp->info;
            remove_ArvAVL(&(*raiz)->dir, (*raiz)->info);
            if (fator_balanceamento_No(*raiz) >= 2)
            {
                if (altura_No((*raiz)->esq->dir) <= altura_No((*raiz)->esq->esq))
                    rotacao_LL(raiz);
                else
                    rotacao_LR(raiz);
            }
        }
        if (*raiz != NULL)
            (*raiz)->altura = maior(altura_No((*raiz)->esq), altura_No((*raiz)->dir)) + 1;
        return 1;
    }

    (*raiz)->altura = maior(altura_No((*raiz)->esq), altura_No((*raiz)->dir)) + 1;

    return res;
}*/
