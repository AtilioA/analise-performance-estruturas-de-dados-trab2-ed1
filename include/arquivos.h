/* Esta biblioteca contém o código que implementa funções mais básicas
 * relevantes à abertura e manipulação de arquivos.
 */

// Guard para evitar dupla inclusão
#ifndef __ARQUIVOS_H
#define __ARQUIVOS_H

#include <stdio.h>

FILE *le_arquivo(char *string);
int le_palavra(FILE *f, char *str);

#endif
