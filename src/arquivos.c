#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/arquivos.h"

#define TAMSTRING 80
#define _STRING_BUFFER_ TAMSTRING
#define UNUSED ".,!? \n^´"

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
        if (c != UNUSED[i])
        {
            return 1;
        }
    }
    return 0;
}

// pqp
char *le_palavra_file(FILE *f)
{
    char *str = malloc(2 * sizeof(char));
    char c;
    int i = 0;

    while ((c = fgetc(f)) != EOF)
    {
        if (eh_valido(c))
        {
            str[i] = c;
        }
        else
        {
            str[i] = '\0';
            return str;
        }
        i++;

        printf("%c", c);
    }
}

//dps a gnt faz outra
int le_palavra(FILE *f, char *str)
{
    int i = 0;
    char caractere;

    while ((caractere = fgetc(f)) != EOF)
        if (isalpha((int)caractere) || isdigit((int)caractere))
            break;

    if (caractere != EOF)
    {
        str[i++] = caractere;
    }
    else
    {
        return 0;
    }

    while (i < _STRING_BUFFER_ - 1 && (caractere = fgetc(f)) != EOF && (isalpha((int)caractere) || isdigit((int)caractere)))
    {
        str[i++] = caractere;
    }

    str[i] = '\0';

    return ftell(f) - i;
}

/*
int main()
{
    char *string = malloc(sizeof(char *) * TAMSTRING);

    // printf("pqp");
    FILE *f = le_arquivo("../lorem-ipsum.txt");
    string = le_palavra_file(f);
    printf("\n\nString lida. Printando:\n%s\n", string);
    // for(int i = 0; i < 10; i++){
    // strcpy(c, le_palavra_file(TAMSTRING));
    // printf("%s \n", c);
    // }

    free(string);
    fclose(f);

    return 0;
}

 */
