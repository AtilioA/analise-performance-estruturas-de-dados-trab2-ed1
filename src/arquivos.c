#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/arquivos.h"
#define _STRING_BUFFER_ 80
#define UNUSED " \n^´"

int charcmp(char c)
{
    for (int i = 0; i < strlen(UNUSED); i++)
    {
        if (c == UNUSED[i])
        {
            return 1;
        }
    }
    return 0;
}

char *lePoLePo(int t)
{
    char *str = malloc(sizeof(char) * t);
    char c;
    for (int i = 0; i < t; i++)
    {
        scanf("%c", &c);
        if (!charcmp(c))
        {
            str[i] = c;
        }
        else
        {
            str[i] = '\0';
            break;
        }
    }
    return str;
}

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
int main(){
    char c[80];
    for(int i = 0; i < 10; i++){
        strcpy(c, lePoLePo(80));
        printf("%s ", c);
    }
    return 0;
}
*/
