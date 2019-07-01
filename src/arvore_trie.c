#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/arvore_trie.h"

ArvTrie *cria_ArvTrie()
{
    ArvTrie *nova = (ArvTrie *)malloc(sizeof(ArvTrie));
    *nova = NULL;
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
NoTrie *cria_no(){
    NoTrie *novo = malloc(sizeof(NoTrie));
    novo->pal = NULL;
    for(int i = 0; i < TAM_TRIE; i++){
        novo->filhos[i] = NULL;
    }
    return novo;
}


void insere_trie(Palavra *pal, ArvTrie *raiz){
    if((*raiz) == NULL){
        (*raiz) = cria_no();
        (*raiz)->letra = pal->string[0];
        int k = strlen(pal->string);
        NoTrie *aux = (*raiz);
        for(int i = 1; i < k; i++){
            int ind = indice(pal->string[i]);
            aux->filhos[ind] = cria_no();
            aux->letra = pal->string[i];
            aux = aux->filhos[ind];
        }
        aux->pal = pal;
        return;
    }
    NoTrie *aux = (*raiz);
    

}
