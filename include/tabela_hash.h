/* Esta biblioteca contém o código que implementa funções mais básicas
 * relevantes à estrutura tabela hash.
 */

// Guard para evitar dupla inclusão
#ifndef __TABELA_HASH_H_
#define __TABELA_HASH_H_

#define TAM_HASH 100003 // número primo grande

#include "../include/arvore_AVL.h"
#include "../include/indexador.h"

/* Estrutura de dados tabela hash implementada com árvores AVL
 * Os nós das AVL guardarão as Palavras
 */
typedef struct tabelahash
{
    ArvAVL *hash[TAM_HASH];
    int colisoes;
    int qtd;
    int *pesos;
} TabelaHash;

// Inicializa uma tabela hash
TabelaHash *cria_Hash();

// Insere uma Palavra na tabela hash
void insere_Hash(Palavra *palavra, TabelaHash *tab);

// Cria a lista de pesos da tabela hash
int *lista_Pesos();

// Imprime os elementos da tabela hash
void imprime_Hash(TabelaHash *tab);

// Busca uma Palavra na tabela hash dada uma string
Palavra *busca_Hash(char *strat, TabelaHash *tab);

// Libera os elementos da tabela hash
void libera_Hash(TabelaHash *tab);

#endif
