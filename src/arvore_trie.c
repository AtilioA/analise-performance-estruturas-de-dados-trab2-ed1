#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/arvore_trie.h"

NoTrie *cria_no(){
    NoTrie *novo = malloc(sizeof(NoTrie));
    novo->pal = NULL;
    for(int i = 0; i < TAM_TRIE; i++){
        novo->filhos[i] = NULL;
    }
    return novo;
}

ArvTrie *cria_ArvTrie()
{
    ArvTrie *nova = (ArvTrie *)malloc(sizeof(ArvTrie));
    *nova = cria_no();
    return nova;
}

int indice(char c){
    if(isalpha(c)){
        return tolower(c) - 'a';
    }else{
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

void libera_Trie(ArvTrie *raiz)
{
    if (raiz != NULL && *raiz != NULL)
    {
        int i = 0;

        for (i = 0; i < TAM_TRIE; i++)
        {
            libera_Trie(&((*raiz)->filhos[i]));
        }

        // percorreL_int((*raiz)->indices, liberaL_int_celula, 0);

        // libera_Lista((*raiz)->indices);
        free(*raiz);
    }
}
/*
// imprime_pre_ordem
void imprime_pre_ordem_Trie(ArvTrie *trie)
{
    if (trie == NULL)
        return;

    if (*trie == NULL)
        return;

    int i = 0;

    printf("%c\n", (*trie)->letra);
    for (i = 0; i < TAM_TRIE; i++)
    {
        imprime_pre_ordem_Trie(&((*trie)->filhos[i]));
    }
}
*/



void insere_trie(Palavra *pal, ArvTrie *raiz){
    NoTrie *aux = (*raiz);
    int k = strlen(pal->string); 
    for(int i = 0; i < k; i++){
        int ind = indice(pal->string[i]);
        if(aux->filhos[ind] == NULL){
            aux->filhos[ind] = cria_no();
        }
        aux = aux->filhos[ind];
        aux->letra = pal->string[i];
    }
    if(aux->pal == NULL){
        aux->pal = pal;
        return;
    }
    insere_Ocorrencias(aux->pal->ocorrencias, pal->ocorrencias->ultimo->ocorreu);
    aux->pal->ocorrencias->qtd++;
}
