#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_MORSE 8

typedef struct abpNo Caractere;

struct abpNo
{
    int ascii;
    char morse[MAX_MORSE];
    Caractere* esq;
    Caractere* dir;
};

/*void percorreArvore(Caractere *abp);*/

Caractere* leTabelaMorse(char arquivo[], Caractere* abp);

Caractere* insereABP(Caractere* abp, int ascii, char morse[MAX_MORSE]);

Caractere* consultaABP(Caractere* abp, int ascii, int* comp);

int traduzABP(char textoOriginal[], char textoDestino[], Caractere* abp);
