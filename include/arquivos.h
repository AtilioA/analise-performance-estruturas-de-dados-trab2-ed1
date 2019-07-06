/* Esta biblioteca contém o código que implementa funções mais básicas
 * relevantes à abertura e manipulação de arquivos.
 */

// Guard para evitar dupla inclusão
#ifndef __ARQUIVOS_H
#define __ARQUIVOS_H

#include <stdio.h>

// Retorna 1 se o arquivo de entrada (abre o arquivo dentro da função com a string passada) for vazio
int arquivo_vazio(char *nomeArquivo);

// Abre um arquivo em modo leitura. Retorna NULL se não for possível abri-lo ou se estiver vazio
FILE *le_arquivo(char *nomeArquivo);

// Lê uma string do arquivo, retorna sua posição diretamente e sua string por referência
int le_palavra(FILE *f, char *str);

#endif
