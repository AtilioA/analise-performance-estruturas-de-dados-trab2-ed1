#include "../include/ListaEncadeada.h"
#include "../include/Indexador.h"
#include <sys/time.h>
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
// Usando imprimeCarta
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

/* MERGE SORT SAFADO DE INDIANO */
tCelula *SortedMerge(tCelula *a, tCelula *b);
void FrontBackSplit(tCelula *source, tCelula **frontRef, tCelula **backRef);

/* sorts the linked list by changing prox pointers (not palavra) */
void MergeSort(tCelula **headRef)
{
    tCelula *head = *headRef;
    tCelula *a;
    tCelula *b;

    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->prox == NULL))
    {
        return;
    }

    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit(head, &a, &b);

    /* Recursively sort the sublists */
    MergeSort(&a);
    MergeSort(&b);

    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge(a, b);
}

/* See https:// www.geeksforgeeks.org/?p=3622 for details of this
function */
tCelula *SortedMerge(tCelula *a, tCelula *b)
{
    tCelula *result = NULL;

    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    /* Pick either a or b, and recur */
    if (a->palavra <= b->palavra)
    {
        result = a;
        result->prox = SortedMerge(a->prox, b);
    }
    else
    {
        result = b;
        result->prox = SortedMerge(a, b->prox);
    }
    return (result);
}

/* UTILITY FUNCTIONS */
/* Split the tCelulas of the given list into front and back halves,
    and return the two lists using the reference parameters.
    If the length is odd, the extra tCelula should go in the front list.
    Uses the fast/slow pointer strategy. */
void FrontBackSplit(tCelula *source,
                    tCelula **frontRef, tCelula **backRef)
{
    tCelula *fast;
    tCelula *slow;
    slow = source;
    fast = source->prox;

    /* Advance 'fast' two tCelulas, and advance 'slow' one tCelula */
    while (fast != NULL)
    {
        fast = fast->prox;
        if (fast != NULL)
        {
            slow = slow->prox;
            fast = fast->prox;
        }
    }

    /* 'slow' is before the midpoint in the list, so split it in two
    at that point. */
    *frontRef = source;
    *backRef = slow->prox;
    slow->prox = NULL;
}
