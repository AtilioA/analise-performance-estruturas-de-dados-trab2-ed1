/* Esta biblioteca contém o código que implementa funções mais básicas
 * relevantes ao TAD lista encadeada para o indexador de arquivos.
 */

// Guard para evitar dupla inclusão
#ifndef __LISTA_ENCADEADA_H
#define __LISTA_ENCADEADA_H

#include "../include/indexador.h"

// Lista encadeada que abstrai um conjunto de itens
typedef struct Celula
{
    Palavra *palavra; // PONTEIRO??
    struct celula *prox;
} Celula;

typedef struct
{
    Celula *cabeca, *ultimo;
    char *nomeArquivo;
    // int tamanho;
} Lista;

/* Funções para acessar estrutura opaca */
// Retorna a quantidade de elementos da lista
// int QuantidadeLista(Lista *lista);

// Cria uma lista vazia
Lista *cria_Lista();

// Verifica se o lista está _vazia
int esta_vazia_Lista(Lista *lista);

// Cria uma célula vazia e retorna-a
Celula *cria_Celula_vazia();

// Verifica se uma carta existe na lista
int existe_Palavra(Palavra *x, Lista *lista);
int indice_Palavra(Palavra *x, Lista *lista);

// Insere uma carta na lista
void insere_Lista_antiga(Palavra *x, Lista *lista);

// retira_Lista uma carta do lista e retorna o elemento por referência
void retira_Lista(int x, Lista *lista, int *cartaRetirada);

// Imprime as cartas do lista
void imprime_Lista(Lista *lista);

// Libera as células de um lista e define seu tamanho para 0
void destroi_Lista(Lista *lista);

// Libera os elementos de uma célula
void destroi_Celula(Celula *celula);

void insere_Lista(Palavra *x, Lista *l);

#endif
