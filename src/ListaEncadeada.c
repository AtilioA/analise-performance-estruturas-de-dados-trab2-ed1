#include "../include/ListaEncadeada.h"
#include "../include/Indexador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tLista *CMVazio()
{
    tLista *lista;
    lista = (tLista *)malloc(sizeof(tLista));

    lista->cabeca = (tCelula *)malloc(sizeof(tCelula));
    lista->ultimo = lista->cabeca;
    lista->ultimo->prox = NULL;
    // lista->tamanho = 0;

    return lista;
}

void FMVazio(tLista *lista)
{
    lista->cabeca = (tCelula *)malloc(sizeof(tCelula));
    lista->ultimo = lista->cabeca;
    lista->ultimo->prox = NULL;
    // lista->tamanho = 0;
}

int EstaVazio(tLista *lista)
{
    return lista->cabeca == NULL;
}

tCelula *CriaCelulaVazia()
{
    tCelula *celulaVazia = (tCelula *)malloc(sizeof(tCelula));

    celulaVazia->prox = NULL;

    return celulaVazia;
}

// int QuantidadeLista(tLista *lista)
// {
//     return (lista->tamanho);
// }

int ExistePalavra(tPalavra *x, tLista *lista)
{
    if (EstaVazio(lista))
    {
        return 0;
    }
    tCelula *atual = lista->cabeca;

    while (atual != NULL)
    {
        if (String(x) == String(atual))
        {
            return 1;
        }
        atual = atual->prox;
    }
    return 0;
}

int IndicePalavra(tPalavra *x, tLista *lista)
{
    if (EstaVazio(lista))
    {
        printf("Lista vazia.\n");
        return -1;
    }
    tCelula *atual = lista->cabeca;

    int i = 0;

    while (atual != NULL)
    {
        printf("%i <- oi\n", strcmp(String(x), String(atual)));
        if (strcmp(String(x), String(atual)) == 0)
        {
            printf("achei\n");
            return i;
        }
        atual = atual->prox;
        i++;
    }

    return -1;
}

void Insere(tPalavra *x, tLista *lista)
{
    int i = 0, indicePalavra = IndicePalavra(x, lista);
    printf("Inserindo...\n");
    if (indicePalavra == -1) // Palavra não existe na lista
    {
        printf("Palavra NAO existe na lista\n");
        lista->ultimo->prox = (tCelula *)malloc(sizeof(tCelula));
        lista->ultimo = lista->ultimo->prox;
        lista->ultimo->palavra = x;
        lista->ultimo->prox = NULL;
        // lista->tamanho++;
    }
    else // Palavra existe na lista
    {
        printf("Palavra existe na lista\n");
        tCelula *atual = lista->cabeca;
        for (i = 1; i < indicePalavra; i++) // Buscando posição da célula da palavra
        {
            atual = atual->prox;
        }
        atual->palavra->ocorrencias++;
        realloc(atual->palavra->posicoes, Ocorrencias(atual) + 1);
        /* atual->palavra->posicoes ... */
    }
}

void Retira(int x, tLista *lista, int *cartaRetirada)
{
    tCelula *atual, *anterior;

    anterior = lista->cabeca;
    for (atual = lista->cabeca; atual != NULL; atual = atual->prox)
    {
        // if ((Valor(Carta(atual)) == Valor(x)) && (Naipe(Carta(atual)) == Naipe(x)))
        // {
        //     *cartaRetirada = Carta(atual);
        //     anterior->prox = atual->prox;
        //     free(atual);
            // lista->tamanho--;
        //     return;
        // }
        anterior = atual;
    }
    // *cartaRetirada = CartaVazia();
}

void ImprimeLista(tLista *lista)
{
    if (!EstaVazio(lista))
    {
        tCelula *atual = NULL;
        // printf("Quantidade de itens: %i\n", QuantidadeLista(lista));
        for (atual = lista->cabeca; atual != NULL; atual = atual->prox)
        {
            ImprimePalavra(atual->palavra);
        }
    }
}

void DestroiCelula(tCelula *celula)
{
    DestroiPalavra(celula->palavra);
}

void DestroiLista(tLista *lista)
{
    tCelula *anterior, *atual;

    atual = lista->cabeca;
    while (atual != NULL)
    {
        anterior = atual;
        atual = atual->prox;
        DestroiCelula(anterior);
    }

    // lista->tamanho = 0;
}
