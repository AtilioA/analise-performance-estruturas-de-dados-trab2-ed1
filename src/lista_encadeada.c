#include "../include/lista_encadeada.h"
#include "../include/indexador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Lista *cria_Lista()
{
    Lista *nova = malloc(sizeof(Lista));

    nova->primeiro = NULL;
    nova->ultimo = NULL;

    return nova;
}

void imprime_Lista(Lista *lista)
{
    Celula *aux = lista->primeiro;
    while (aux != NULL)
    {
        imprime_Palavra(aux->palavra);
        aux = aux->prox;
    }
}

void libera_Celula(Celula *cel)
{
    libera_Palavra(cel->palavra);
    free(cel);
}

void libera_Lista(Lista *lista)
{
    Celula *ant = NULL;
    Celula *aux = lista->primeiro;

    while (aux != NULL)
    {
        ant = aux;
        aux = aux->prox;
        libera_Celula(ant);
    }

    free(lista);
}

// Não insere palavras repetidas (percorre a lista em busca de repetição)
void insere_Lista(Palavra *x, Lista *l)
{
    Celula *nova = malloc(sizeof(Celula));
    nova->palavra = x; //passa o endereço
    nova->prox = NULL;
    if (l->primeiro == NULL)
    {
        l->primeiro = nova;
        l->ultimo = nova;
        return;
    }
    Celula *aux = l->primeiro;
    while (aux->prox != NULL && strcasecmp(aux->palavra->string, x->string))
    {
        aux = aux->prox;
    }
    if (!strcasecmp(aux->palavra->string, x->string))
    {
        insere_Arq(x->arquivos->primeiro->nomeArquivo, aux->palavra->arquivos, x->arquivos->primeiro->ocorrencias->primeiro->ocorreu);
        libera_Celula(nova);
        return;
    }
    l->ultimo->prox = nova;
    l->ultimo = nova;
    return;
}

Palavra *busca_Lista(char *strat, Lista *l)
{
    Celula *aux = l->primeiro;
    while (aux != NULL && strcasecmp(aux->palavra->string, strat))
    {
        aux = aux->prox;
    }
    if (aux == NULL)
    {
        return NULL;
    }
    if (!strcasecmp(aux->palavra->string, strat))
    {
        return aux->palavra;
    }
    return NULL;
}
