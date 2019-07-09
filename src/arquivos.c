#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/arquivos.h"

#define TAM_STRING 80

int arquivo_vazio(char *nomeArquivo)
{
    FILE *f = fopen(nomeArquivo, "r");

    fgetc(f);
    int eof = feof(f);

    fclose(f);
    return eof;
}

FILE *le_arquivo(char *nomeArquivo)
{
    FILE *f = fopen(nomeArquivo, "r"); // abre apenas para leitura

    if (f == NULL)
    {
        printf("Erro na leitura do arquivo.\n");
        return NULL;
    }
    else if (arquivo_vazio(nomeArquivo))
    {
        printf("Arquivo vazio.\n");
        fclose(f);
        return NULL;
    }

    return f;
}

int le_palavra(FILE *f, char *str)
{
    int i = 0;
    int c;
    int posicao = 0;

    while ((c = fgetc(f)) != EOF)
    {
        if (isalpha(c) || isdigit(c))
        {
            break;
        }
    }

    if (c == EOF)
    {
        return -1;
    }
    else
    {
        str[i++] = c;
    }

    while (i < TAM_STRING - 1 && (c = fgetc(f)) != EOF && (isalpha(c) || isdigit(c)))
    {
        str[i++] = c;
    }
    str[i] = '\0';

    posicao = ftell(f) - strlen(str);
    return posicao;
}
