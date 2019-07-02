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
    Palavra *palavra;
    struct NoTrie *filhos[TAM_TRIE]; // ponteiro?
} NoTrie;

typedef NoTrie *ArvTrie; // raiz

void insere_trie(Palavra *palavra, ArvTrie *raiz);

ArvTrie *cria_ArvTrie();
void libera_ArvTrie(ArvTrie *raiz);
void insere_trie(Palavra *palavra, ArvTrie *raiz);
// Palavra *busca_ArvTrie(ArvTrie *raiz, char *strat);

#endif
