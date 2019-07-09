#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <ctype.h>
#include "../include/tabela_hash.h"

TabelaHash *cria_Hash()
{
    TabelaHash *nova = malloc(sizeof(TabelaHash));

    for (int i = 0; i < TAM_HASH; i++)
    {
        nova->hash[i] = cria_ArvAVL();
    }

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

void insere_Hash(Palavra *palavra, TabelaHash *tab)
{
    int indice = calc_Hash(tab->pesos, palavra->string);

    if (indice < 0)
    {
        indice = (-1) * indice;
    }
    insere_ArvAVL(tab->hash[indice], palavra);
}

void imprime_Hash(TabelaHash *tab)
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
