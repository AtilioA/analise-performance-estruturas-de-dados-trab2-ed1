/* Esta biblioteca contém o código que implementa funções mais básicas
 * relevantes ao TAD lista encadeada para o indexador de arquivos.
 */

// Guard para evitar dupla inclusão
#ifndef __LISTA_ENCADEADA_H
#define __LISTA_ENCADEADA_H

#include "../include/indexador.h"

// Lista encadeada que abstrai um conjunto de Palavras
typedef struct Celula
{
    Palavra *palavra;
    struct celula *prox;
} Celula;

typedef struct Lista
{
    Celula *primeiro, *ultimo;
} Lista;


// Cria uma lista vazia
Lista *cria_Lista();

// Imprime as Palavras da lista
void imprime_Lista(Lista *lista);

// Libera os elementos de uma célula
void libera_Celula(Celula *celula);

// Libera as células de uma lista
void libera_Lista(Lista *lista);

/* Insere uma Palavra na lista.
 * Não insere palavras repetidas (percorre a lista em busca de repetição)
 */
void insere_Lista(Palavra *x, Lista *lista);

/* Busca na lista se existe uma célula com uma Palavra com
 * string igual à string de entrada,
 * retorna a Palavra da célula se for encontrada
 * NULL caso contrário
 */
Palavra *busca_Lista(char *strat, Lista *lista);
#endif
