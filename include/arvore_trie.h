/* Esta biblioteca contém o código que implementa funções mais básicas
 * relevantes ao TAD árvore trie para o indexador de arquivos.
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
    struct NoTrie *filhos[TAM_TRIE];
} NoTrie;

typedef NoTrie *ArvTrie; // raiz

// Insere uma Palavra na árvore trie
void insere_ArvTrie(Palavra *palavra, ArvTrie *raiz);

// Inicializa uma árvore trie;
ArvTrie *cria_ArvTrie();

// Inicializa um nó de arvore trie
NoTrie *cria_NoTrie();

// Libera os elementos dos nós da árvore trie
void libera_NosTrie(ArvTrie *raiz);

// Libera os elementos dos nós da árvore trie
void libera_ArvTrie(ArvTrie *raiz);

Palavra *busca_ArvTrie(ArvTrie *raiz, char *strat);

#endif
