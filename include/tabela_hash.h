/* Esta biblioteca contém o código que implementa funções mais básicas
 * relevantes à estrutura tabela hash.
 */

// Guard para evitar dupla inclusão
#ifndef __TABELA_HASH_H_
#define __TABELA_HASH_H_

#define TAM_HASH 997

#include "../include/arvore_AVL.h"
#include "../include/indexador.h"

typedef struct tabelahash
{
    ArvAVL *hash[TAM_HASH];
    int colisoes;
    int qtd;
    int *pesos;
} TabelaHash;

TabelaHash *cria_Hash();

void insere_Hash(Palavra *pal, TabelaHash *tab);

int *lista_Pesos();

void imprime_Hash(TabelaHash *tab);

Palavra *busca_Hash(char* strat, TabelaHash *tab);

void libera_Hash(TabelaHash *tab);

#endif

/*
int n_elementos(TipoDicionario tabela);
int n_colisoes(TipoDicionario tabela);
float carga_pesada(TipoDicionario tabela);
*/
