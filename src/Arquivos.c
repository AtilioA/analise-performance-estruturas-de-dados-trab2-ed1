#include <stdio.h>
#include <stdlib.h>
#include "../include/Arquivos.h"

// alterar essa budega
int lePalavra(FILE *f, char *str, int BUFFER)
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

    while (i < BUFFER - 1 && (caractere = fgetc(f)) != EOF && (isalpha((int)caractere) || isdigit((int)caractere)))
    {
        str[i++] = caractere;
    }

    str[i] = '\0';

    return ftell(f) - i;
}
