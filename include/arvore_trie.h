/* Esta biblioteca contém o código que implementa funções mais básicas
 * relevantes ao TAD árvore binária trie para o indexador de arquivos.
 */

// Guard para evitar dupla inclusão
#ifndef __ARVORE_TRIE_H
#define __ARVORE_TRIE_H

#include "arvore_binaria.h"
#include "indexador.h"
#include "lista_encadeada.h"

#define TAM_TRIE 36 // 26 letras + 10 números

typedef struct NoTrie
{
    char letra;
    struct NoTrie *filhos[TAM_TRIE]; // ponteiro?
    Palavra *pal;
} NoTrie;

typedef NoTrie *ArvTrie; // raiz

void insere_trie(Palavra *pal, ArvTrie *raiz);

ArvTrie *cria_ArvTrie();
void libera_ArvTrie(ArvTrie *raiz);
// int insere_ArvTrie(ArvTrie *raiz, Palavra *pal);
// Palavra *consulta_ArvTrie(ArvTrie *raiz, char *strat);
// void imprime_pre_ordem_ArvTrie(ArvTrie *raiz);
// void imprime_pre_ordem_ArvTrie(ArvTrie *raiz);
// void pos_ordem_ArvTrie(ArvTrie *raiz);

#endif
