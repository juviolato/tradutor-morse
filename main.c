#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "morse.h"

//o codigo comentado aqui eh pra mudar dps pra funcionar na linha de comando eu tava com preguicite de aprender como usa
//pra testar la hihi
//codigo comentado na morse.c (<- la) eh pra debugzinho

int main(/*int nArquivos, char* nomes[]*/)
{
    int compABP, compSplay;
    Caractere *abp;
    char morse[] = {"codigomorse.txt"}, original[] = {"capitulo1.txt"}, destino[] = {"traduzido.txt"};

    abp = NULL;

    /*if (nArquivos!= 4)
    {
        printf ("Numero incorreto de parametros.\n Para chamar o programa digite: exemplo <arq_morse> <arq_original> <arq_destino>\n");
        return 1;
    }
    else
    {*/
        abp = leTabelaMorse(/*nomes[1]*/morse, abp);
        abp = insereABP(abp, 32, "/");

        compABP = traduzABP(/*nomes[2]*/original, /*nomes[3]*/destino, abp);

        printf("\n\nComparacoes feitas na arvore binaria de pesquisa: %d\n", compABP);

        return 0;
    /*}*/
}
