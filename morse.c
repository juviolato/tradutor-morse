#include "morse.h"

/*void percorreArvore(Caractere *abp)
{
    if (abp != NULL)
    {
        printf(" - %d", abp->ascii);
        percorreArvore(abp->esq);
        percorreArvore(abp->dir);
    }
    else
        printf(" - folha");
}*/

Caractere* leTabelaMorse(char arquivo[], Caractere* abp)
{
    FILE *morse;
    char ascii, codMorse[MAX_MORSE];

    morse = fopen(arquivo, "r");            //Abre arquivo com tabela morse

    if (morse == NULL)
        puts("A tabela morse nao pode ser aberta.");
    else
    {
        while (!feof(morse))
        {
            fflush(stdin);
            fscanf(morse, " %c    %s", &ascii, codMorse);    //L� caractere em ASCII e seu c�digo morse correspondente

            //printf("\n\n %c", ascii);
            //printf("\n%s", codMorse);

            abp = insereABP(abp, ascii, codMorse);        //Insere caractere em uma ABP
        }

        fclose(morse);
    }

    return abp;
}

Caractere* insereABP(Caractere* abp, int ascii, char morse[MAX_MORSE])
{
    Caractere *novo;

    if (abp == NULL)            //Se a ABP estiver vazia
    {
        novo = (Caractere*)malloc(sizeof(Caractere));
        novo->ascii = ascii;
        strcpy(novo->morse, morse);
        novo->esq = NULL;
        novo->dir = NULL;

        abp = novo;    //Insere o caractere na ra�z
    }
    else                        //Se a ABP n�o estiver vazia
        if (ascii < abp->ascii)             //Se o c�digo ASCII for menor que o do n� analisado
        {
            if(abp->esq == NULL)        //Garante que n�o passar� um nodo nulo na recurs�o
            {
                novo = (Caractere*)malloc(sizeof(Caractere));
                novo->ascii = ascii;
                strcpy(novo->morse, morse);
                novo->esq = NULL;
                novo->dir = NULL;

                abp->esq = novo;
            }
            else
                abp->esq = insereABP(abp->esq, ascii, morse);   //Insere o caractere � esquerda
        }
        else if (ascii > abp->ascii)        //Se o c�gido ASCII for maior
        {
            if(abp->dir == NULL)
            {
                novo = (Caractere*)malloc(sizeof(Caractere));
                novo->ascii = ascii;
                strcpy(novo->morse, morse);
                novo->esq = NULL;
                novo->dir = NULL;

                abp->dir = novo;
            }
            else
                abp->dir = insereABP(abp->dir, ascii, morse);   //Insere o caractere � direita
        }

    return abp;
}

Caractere* consultaABP(Caractere* abp, int ascii, int* comp)
{
    Caractere* aux;
    aux = abp;

    while (aux != NULL)
    {
        if (aux->ascii == ascii)            //V� se j� achou o caractere procurado
        {
            //puts("achou ascii igual");
            *comp = *comp + 1;
            return aux;
        }
        else if (aux->ascii > ascii)        //Procura na sub�rvore esquerda se o c�digo ASCII for menor
        {
            //puts("foi pra subarvore esquerda");
            *comp = *comp + 1;
            aux = aux->esq;
        }
        else                                //Procura na direita se for maior
        {
            *comp = *comp + 1;
            aux = aux->dir;
            //puts("foi pra subarvore direita");
        }
    }
    //puts("chegou em null (erro!!)");
    //printf("\nERRO: %c\n", (char)ascii);
    return aux;
}

int traduzABP(char textoOriginal[], char textoDestino[], Caractere* abp)
{
    FILE *original, *destino;
    int ascii;
    Caractere *morse;

    int comp = 0;
    //int cr;
    //cr = 0;

    original = fopen(textoOriginal, "r");
    destino = fopen(textoDestino, "w+");

    if (original == NULL)
        puts("Texto nao pode ser aberto.");
    else
    {
        while (!feof(original))
        {
            ascii = getc(original); //Le caractere no arquivo original
            //puts("pegou novo caractere");

            morse = consultaABP(abp, toupper(ascii), &comp);
            //puts("procurou na abp");
            if(morse != NULL)
            {
                fputs(morse->morse, destino);   //Insere caractere em morse no arquivo codificado
                putc(' ', destino);             //Separa letras com espa�os
            }
            //cr++;
            //puts("colocou no arquivo novo");
            //printf(" - %d caracteres", cr);
        }

        fclose(original);
        fclose(destino);
    }

    return comp;
}
