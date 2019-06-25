#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/arquivos.h"
#define _STRING_BUFFER_ 80

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
