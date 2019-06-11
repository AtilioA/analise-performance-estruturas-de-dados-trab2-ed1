/* Esta biblioteca contém o código que implementa funções mais básicas
 * relevantes ao TAD lista encadeada para o indexador de arquivos.
 */

// Guard para evitar dupla inclusão
#ifndef __LISTA_ENCADEADA_H
#define __LISTA_ENCADEADA_H

// Lista encadeada que abstrai um conjunto de itens
typedef struct tCelula
{
    /* item */
    struct tCelula *prox;
} tCelula;

typedef struct
{
    int tamanho;
    tCelula *cabeca, *ultimo;
} tMonte;

/* Funções para acessar estrutura opaca */
// Retorna a quantidade de cartas do monte
int QuantidadeMonte(tMonte *monte);

// Faz a lista (monte) ficar vazia
void FMVazio(tMonte *monte);

// Preenche o baralho com todas as cartas possíveis de um baralho padrão de bisca
void CriaBaralho(tMonte *monte);

// Verifica se o monte está vazio
int EstaVazio(tMonte *monte);

// Cria uma célula vazia e retorna-a
tCelula CriaCelulaVazia();

// Verifica se uma carta existe no monte
int ExisteCarta(int x, tMonte *monte);

// Insere uma carta no monte
void Insere(int x, tMonte *monte);

// Retira uma carta do monte e retorna o elemento por referência
void Retira(int x, tMonte *monte, int *cartaRetirada);

// Imprime as cartas do monte
void ImprimeMonte(tMonte *monte);

// Libera as células de um monte e define seu tamanho para 0
void DestroiMonte(tMonte *monte);

#endif
