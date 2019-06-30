/* Esta biblioteca contém o código que implementa funções mais básicas
 * relevantes à estrutura tabela hash.
 */


#ifndef _TABELA_HASH_
#define _TABELA_HASH_
#define TAM_HASH 20
#include "../include/arvore_AVL.h"
#include "../include/indexador.h"

typedef struct tabelahash{
    ArvAVL *hash[TAM_HASH];
    int colisoes;
    int qtd;
    int *pesos;
}TabelaHash;

TabelaHash *criaHash();

void insere_Hash(Palavra *pal, TabelaHash *tab);

int *lista_Pesos();

void printar_Hash(TabelaHash *tab);

Palavra *busca_Hash(char* strat, TabelaHash *tab);

void libera_Hash(TabelaHash *tab);

#endif

/*
// Guard para evitar dupla inclusão
#ifndef __TABELA_HASH_H_
#define __TABELA_HASH_H_

#include <stdio.h>
#include "lista_encadeada.h"

// #include <stdlib.h>
// #include <sys/time.h>
// #include <string.h>

#define M 97            // número primo alto placeholderson
#define N 30            // tamanho máximo da string
#define TAMALFABETO 256 // vmzice?

 typedef unsigned int  TipoPesos[n]; 

typedef unsigned int Indice;
typedef unsigned TipoPesos[N][TAMALFABETO];
typedef char TipoChave[N];

// typedef struct Celula *Celula;*


typedef struct ListaHash
{
    Celula *primeiro, *ultimo;
    int qtd;
    int colisoes;
} ListaHash;

typedef ListaHash TipoDicionario[M];

void cria_ListaHash(ListaHash *Lista);

short Vazia(ListaHash *lista);

void Ins(Palavra x, ListaHash *Lista);

void Ret(Celula *p, ListaHash *Lista, Palavra *Item);

void GeraPesos(TipoPesos p);

Indice h(TipoChave Chave, TipoPesos p);

void Inicializa(TipoDicionario T);

// Celula *Pesquisa(TipoChave Ch, TipoPesos p, TipoDicionario T);

void Insere(Palavra x, TipoPesos p, TipoDicionario T);

void Retira(Palavra x, TipoPesos p, TipoDicionario T);

void Imp(ListaHash Lista);

void Imprime(TipoDicionario Tabela);

int n_elementos(TipoDicionario tabela);
int n_colisoes(TipoDicionario tabela);
float carga_pesada(TipoDicionario tabela);

#endif*/
