/* Esta biblioteca contém o código que implementa funções mais básicas
 * relevantes ao TAD lista encadeada para o indexador de arquivos.
 */

// Guard para evitar dupla inclusão
#ifndef __LISTA_ENCADEADA_H
#define __LISTA_ENCADEADA_H

#include "../include/Indexador.h"

// Lista encadeada que abstrai um conjunto de itens
typedef struct celula
{
    tPalavra *palavra; // PONTEIRO??
    struct celula *prox;
} tCelula;

typedef struct
{
    tCelula *cabeca, *ultimo;
    char *nomeArquivo;
    // int tamanho;
} tLista;

/* Funções para acessar estrutura opaca */
// Retorna a quantidade de elementos da lista
// int QuantidadeLista(tLista *lista);

// Faz a lista (lista) ficar vazia
void FMVazio(tLista *lista);

// Preenche o baralho com todas as cartas possíveis de um baralho padrão de bisca
void CriaBaralho(tLista *lista);

// Verifica se o lista está vazio
int EstaVazio(tLista *lista);

// Cria uma célula vazia e retorna-a
tCelula *CriaCelulaVazia();

// Verifica se uma carta existe no lista
int ExistePalavra(tPalavra *x, tLista *lista);

// Insere uma carta no lista
void Insere(tPalavra *x, tLista *lista);

// Retira uma carta do lista e retorna o elemento por referência
void Retira(int x, tLista *lista, int *cartaRetirada);

// Imprime as cartas do lista
void ImprimeLista(tLista *lista);

// Libera as células de um lista e define seu tamanho para 0
void DestroiLista(tLista *lista);

// Libera os elementos de uma célula
void DestroiCelula(tCelula *celula);

tLista *Cria_Lista();
void Insere_Lista(tPalavra *x, tLista *l);

#endif
