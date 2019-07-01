#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/arquivos.h"

#define TAM_STRING 80
#define _STRING_BUFFER_ TAM_STRING
#define UNUSED ".,!? "

FILE *le_arquivo(char *string)
{
    FILE *f = fopen(string, "r"); // abre apenas para leitura

    if (f == NULL)
    {
        printf("Erro na leitura do arquivo.\n");
        exit(1);
    }

    return f;
}

int eh_valido(char c)
{
    for (int i = 0; i < strlen(UNUSED); i++)
    {
        if (c == UNUSED[i])
        {
            return 0;
        }
    }

    return 1;
}

// OUTRA VERSÃO DA le_palavra QUE FIZ COM RENAN
char *le_palavra_file(FILE *f, char *str)
{
    char c;
    int i = 0;

    while (((c = fgetc(f)) != EOF) && !isalpha(c));

    if (c != EOF)
    {
        str[i++] = c;
    }
    else
    {
        return NULL;
    }

    while (((c = fgetc(f)) != EOF) && isalpha(c))
    {
        str[i++] = c;
    }

    str[i] = '\0';

    return str;
}

// Lê uma palavra do arquivo, retorna sua posição diretamente e sua string por referência
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
        return 0;
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

    posicao = ftell(f) - strlen(str) + 1;
    return posicao;
}
