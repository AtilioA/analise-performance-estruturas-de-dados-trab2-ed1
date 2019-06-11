#include "../include/ListaEncadeada.h"
// #include "../include/Cartas.h"
// #include "../include/MaosSimples.h"
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

tMonte *CMVazio()
{
    tMonte *monte;
    monte = (tMonte *)malloc(sizeof(tMonte));

    monte->cabeca = (tCelula *)malloc(sizeof(tCelula)); // monte->cabeca será a cabeça do monte AAAAAAAAAA
    monte->ultimo = monte->cabeca;
    monte->ultimo->prox = NULL;
    monte->tamanho = 0;

    return monte;
}

void FMVazio(tMonte *monte)
{
    monte->cabeca = (tCelula *)malloc(sizeof(tCelula)); // monte->cabeca será a cabeça do monte AAAAAAAAAA
    monte->ultimo = monte->cabeca;
    monte->ultimo->prox = NULL;
    monte->tamanho = 0;
}

int EstaVazio(tMonte *monte)
{
    return (QuantidadeMonte(monte) == 0);
}

tCelula CriaCelulaVazia()
{
    tCelula celulaVazia;

    // celulaVazia.carta = CartaVazia();
    celulaVazia.prox = NULL;

    return celulaVazia;
}

int QuantidadeMonte(tMonte *monte)
{
    return (monte->tamanho);
}

int ExisteCarta(int x, tMonte *monte)
{
    if (EstaVazio(monte))
    {
        return 0;
    }
    tCelula *atual = monte->cabeca->prox;

    while (atual != NULL)
    {
        // if ((Valor(Carta(atual)) == Valor(x)) && (Naipe(Carta(atual)) == Naipe(x)))
        // {
        //     return 1;
        // }
        atual = atual->prox;
    }
    return 0;
}

void Insere(int x, tMonte *monte)
{
    if (!ExisteCarta(x, monte))
    {
        monte->ultimo->prox = (tCelula *)malloc(sizeof(tCelula));
        monte->ultimo = monte->ultimo->prox;
        // monte->ultimo->carta = x;
        monte->ultimo->prox = NULL;

        monte->tamanho++;
    }
    else
    {
        printf("A carta ja existe no monte.\n");
    }
}

void Retira(int x, tMonte *monte, int *cartaRetirada)
{
    tCelula *atual, *anterior;

    anterior = monte->cabeca;
    for (atual = monte->cabeca->prox; atual != NULL; atual = atual->prox)
    {
        // if ((Valor(Carta(atual)) == Valor(x)) && (Naipe(Carta(atual)) == Naipe(x)))
        // {
        //     *cartaRetirada = Carta(atual);
        //     anterior->prox = atual->prox;
        //     free(atual);
        //     monte->tamanho--;
        //     return;
        // }
        anterior = atual;
    }
    // *cartaRetirada = CartaVazia();
}
// Usando imprimeCarta
void ImprimeMonte(tMonte *monte)
{
    if (QuantidadeMonte(monte) != 0)
    {
        tCelula *atual = NULL;

        // printf("Quantidade de itens: %i\n", QuantidadeMonte(monte));
        for (atual = monte->cabeca->prox; atual != NULL; atual = atual->prox)
        {
            // ImprimeCarta(Carta(atual));
        }
    }
}

void DestroiMonte(tMonte *monte)
{
    tCelula *anterior, *atual;

    atual = monte->cabeca;
    while (atual != NULL)
    {
        anterior = atual;
        atual = atual->prox;
        free(anterior);
    }

    monte->tamanho = 0;
}
