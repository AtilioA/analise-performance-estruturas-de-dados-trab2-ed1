#include "../include/lista_encadeada.h"
#include "../include/indexador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
int esta_vazia_Lista(Lista *lista)
{
    return lista->cabeca == NULL;
}

Celula *cria_Celula_vazia()
{
    Celula *celulaVazia = (Celula *)malloc(sizeof(Celula));
    celulaVazia->prox = NULL;

    return celulaVazia;
}

// int QuantidadeLista(Lista *lista)
// {
//     return (lista->tamanho);
// }

int existe_palavra(Palavra *x, Lista *lista)
{
    if (esta_vazia_Lista(lista))
    {
        return 0;
    }
    Celula *atual = lista->cabeca;

    while (atual != NULL)
    {
        if (get_string(x) == get_string(atual))
        {
            return 1;
        }
        atual = atual->prox;
    }
    return 0;
}

int indice_Palavra(Palavra *x, Lista *lista)
{
    if (esta_vazia_Lista(lista))
    {
        printf("Lista vazia.\n");
        return -1;
    }
    Celula *atual = lista->cabeca;

    int i = 0;
    while (atual != NULL)
    {
        printf("%i <- oi\n", strcmp(get_string(x), get_string(atual)));
        if (strcmp(get_string(x), get_string(atual)) == 0)
        {
            printf("achei\n");
            return i;
        }
        atual = atual->prox;
        i++;
    }

    return -1;
}

void insere_Lista_antigo(Palavra *x, Lista *lista)
{
    int i = 0;
    int indicePalavra = indice_Palavra(x, lista);
    printf("Inserindo...\n");
    if (indicePalavra == -1) // Palavra não existe na lista
    {
        printf("Palavra NAO existe na lista\n");
        lista->ultimo->prox = (Celula *)malloc(sizeof(Celula));
        lista->ultimo = lista->ultimo->prox;
        lista->ultimo->palavra = x;
        lista->ultimo->prox = NULL;
        // lista->tamanho++;
    }
    else // Palavra existe na lista
    {
        printf("Palavra existe na lista\n");
        Celula *atual = lista->cabeca;
        for (i = 1; i < indicePalavra; i++) // Buscando posição da célula da palavra
        {
            atual = atual->prox;
        }
        atual->palavra->ocorrencias++;
        realloc(atual->palavra->posicoes, get_ocorrencias(atual) + 1);
         atual->palavra->posicoes ...
    }
}

void retira_Lista(int x, Lista *lista, int *cartaRetirada)
{
    Celula *atual, *anterior;

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
*/
void imprime_lista(Lista *lista)
{
    Celula *aux = lista->cabeca;
    while (aux != NULL)
    {
        imprime_Palavra(aux->palavra);
        aux = aux->prox;
    }
}

void destroi_celula(Celula *cel){
    destroi_Palavra(cel->palavra);
    free(cel);
}

void destroi_lista(Lista *lista){
    Celula * ant = NULL;
    Celula *aux = lista->cabeca;
    while(aux != NULL){
        ant = aux;
        aux = aux->prox;
        destroi_celula(ant);
    }
    free(lista);
}
/*
void destroi_Celula(Celula *celula)
{
    destroi_Palavra(celula->palavra);
}

void destroi_Lista(Lista *lista)
{
    Celula *anterior, *atual;

    atual = lista->cabeca;
    while (atual != NULL)
    {
        anterior = atual;
        atual = atual->prox;
        destroi_Celula(anterior);
    }

    // lista->tamanho = -1;
}
*/
//vam ve se essa parte aqui de baixo vamo
Lista *cria_Lista()
{
    Lista *nova = malloc(sizeof(Lista));
    nova->cabeca = NULL;
    nova->ultimo = NULL;
    return nova;
}

void insere_Lista(Palavra *x, Lista *l)
{
    Celula *nova = malloc(sizeof(Celula));
    nova->palavra = x; //passa o endereço
    nova->prox = NULL;
    if(l->cabeca == NULL){
        l->cabeca = nova;
        l->ultimo = nova;
        return;
    }
    Celula *aux = l->cabeca;
    while(aux->prox != NULL && strcasecmp(get_string(aux->palavra), get_string(x))){
        aux = aux->prox;
    }
    if(!strcasecmp(get_string(aux->palavra), get_string(x))){
        insereOcorre(get_posicoes(aux->palavra), get_posicoes(x)->ult->ocorreu);
        aux->palavra->ocorrencias->n++;
        destroi_celula(nova);
        return;
    }
    l->ultimo->prox = nova;
    l->ultimo = nova;
    return;
}
Palavra *busca_Lista(char *strat, Lista *l){
    Celula *aux = l->cabeca;
    printf("Buscando %s em lista\n", strat);
    while(aux != NULL && strcasecmp(get_string(aux->palavra), strat)){
        aux = aux->prox;
    }
    if(aux == NULL){
        return NULL;
    }
    if(!strcasecmp(get_string(aux->palavra), strat)){
        return aux->palavra;
    }
    return NULL;
}
