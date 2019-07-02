#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/arvore_trie.h"

NoTrie *cria_no()
{
    NoTrie *novo = malloc(sizeof(NoTrie));

    novo->palavra = NULL;
    for (int i = 0; i < TAM_TRIE; i++)
    {
        novo->filhos[i] = NULL;
    }

    return novo;
}

void libera_NoTrie(NoTrie *no)
{
    libera_Palavra(no->palavra);
    free(no);
}

ArvTrie *cria_ArvTrie()
{
    ArvTrie *nova = (ArvTrie *)malloc(sizeof(ArvTrie));
    *nova = cria_no();
    return nova;
}

int indice_ArvTrie(char c)
{
    if (isalpha(c))
    {
        return tolower(c) - 'a';
    }
    else
    {
        return c - 22;
    }
}

void to_lower_string(char *string)
{
    int i = 0;

    for (i = 0; i < strlen(string); i++)
    {
        string[i] = tolower(string[i]);
    }
}

// zoadão
void libera_ArvTrie(ArvTrie *raiz)
{
    if((*raiz) == NULL){
        return;
    }
    if(raiz == NULL){
        return;
    }
    for(int i = 0; i < TAM_TRIE; i++){
        libera_ArvTrie(&((*raiz)->filhos[i]));
    }
    if((*raiz)->palavra != NULL){
        libera_Palavra((*raiz)->palavra);
    }
    free(*raiz);
}

void insere_ArvTrie(Palavra *palavra, ArvTrie *raiz)
{
    NoTrie *aux = (*raiz);
    int tamPalavra = strlen(palavra->string);

    for (int i = 0; i < tamPalavra; i++)
    {
        int ind = indice_ArvTrie(palavra->string[i]);
        if (aux->filhos[ind] == NULL)
        {
            aux->filhos[ind] = cria_no();
        }
        aux = aux->filhos[ind];
        aux->letra = palavra->string[i];
    }

    if (aux->palavra == NULL)
    {
        aux->palavra = palavra;
    }
    else
    {
        insere_Ocorrencias(aux->palavra->ocorrencias, palavra->ocorrencias->ultimo->ocorreu);
        aux->palavra->ocorrencias->qtd++;
        libera_Palavra(palavra);
    }
}

Palavra *busca_ArvTrie(ArvTrie *raiz, char *strat){
    NoTrie *aux = (*raiz);
    int tamPalavra = strlen(strat);
    for(int i = 0; i < tamPalavra; i++){
        int ind = indice_ArvTrie(strat[i]);
        aux = aux->filhos[ind];
        if(aux == NULL){
            break;
        }
    }
    if(aux == NULL){
        return NULL;
    }
    return aux->palavra;
    
}

void imprime_ArvTrie(ArvTrie *raiz){
    if((*raiz) == NULL){
        return;
    }
    if(raiz == NULL){
        return;
    }
    for(int i = 0; i < TAM_TRIE; i++){
        imprime_ArvTrie(&((*raiz)->filhos[i]));
    }
    if((*raiz)->palavra != NULL){
        imprime_Palavra((*raiz)->palavra);
    }
}
