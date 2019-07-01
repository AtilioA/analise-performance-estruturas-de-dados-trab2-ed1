#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/arvore_binaria.h"
#include "../include/arvore_trie.h"

ArvTrie *cria_ArvTrie()
{
    ArvTrie *nova = (ArvTrie *)malloc(sizeof(ArvTrie));
    *nova = NULL;

    // ???
    // (*nova)->letra = NULL;
    // (*(*nova)->filhoss) = NULL;

    return nova;
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

        libera_Lista((*raiz)->indices);
        free(*raiz);
    }
}

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
