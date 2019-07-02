#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include "../include/tabela_hash.h"

// uma implementação diferenciada

TabelaHash *cria_Hash()
{
    TabelaHash *nova = malloc(sizeof(TabelaHash));

    for (int i = 0; i < TAM_HASH; i++)
    {
        nova->hash[i] = cria_ArvAVL();
    }

    nova->colisoes = 0;
    nova->qtd = 0;
    nova->pesos = lista_Pesos();

    return nova;
}

int *lista_Pesos()
{
    struct timeval t; // Para gerar semente do srand
    int *lista_p = malloc(sizeof(int) * 80);

    gettimeofday(&t, NULL); // Para gerar semente do srand
    srand((unsigned int)t.tv_usec);

    for (int i = 0; i < 80; i++)
    {
        lista_p[i] = rand() % 10000;
    }

    return lista_p;
}

int calc_Hash(int *peso, char *strat)
{
    int sum = 0;

    for (int i = 0; i < strlen(strat); i++)
    {
        sum += peso[i] * tolower(strat[i]);
    }
    return sum % TAM_HASH;
}

void insere_Hash(Palavra *pal, TabelaHash *tab)
{
    int indice = calc_Hash(tab->pesos, pal->string);

    if (indice < 0)
    {
        indice = (-1) * indice;
    }
    if (*(tab->hash[indice]) != NULL)
    {
        tab->colisoes++;
    }
    insere_ArvAVL(tab->hash[indice], pal);
    tab->qtd++;
}

void printar_Hash(TabelaHash *tab)
{
    for (int i = 0; i < TAM_HASH; i++)
    {
        if (*(tab->hash[i]) != NULL)
        {
            printf("\n\nIndice da arvore: %d\n\n", i);
            imprime_pre_ordem_ArvAVL(tab->hash[i]);
        }
    }
}

Palavra *busca_Hash(char *strat, TabelaHash *tab)
{
    int indice = calc_Hash(tab->pesos, strat);
    if (indice < 0)
    {
        indice = (-1) * indice;
    }
    return busca_ArvAVL(tab->hash[indice], strat);
}

void libera_Hash(TabelaHash *tab)
{
    for (int i = 0; i < TAM_HASH; i++)
    {
        libera_ArvAVL(tab->hash[i]);
    }

    free(tab->pesos);
    free(tab);
}


/*
void Imprime(TipoDicionario Tabela)
{
    int i;
    for (i = 0; i < M; i++)
    {
        printf("%d: ", i);
        if (!Vazia(&Tabela[i]))
            imprime_Lista(Tabela[i]);
        putchar('\n');
    }
}

int n_elementos(TipoDicionario tabela)
{
    int i = 0, qtd = 0;

    for (i = 0; i < M; i++)
    {
        qtd += tabela[i].qtd;
    }

    return qtd;
}

int n_colisoes(TipoDicionario tabela)
{
    int i = 0, colisoes = 0;

    for (i = 0; i < M; i++)
    {
        colisoes += tabela[i].colisoes;
    }

    return colisoes;
}

float carga_pesada(TipoDicionario tabela)
{
    int qtd = n_elementos(tabela);

    return (float)qtd / M;
}

*/
