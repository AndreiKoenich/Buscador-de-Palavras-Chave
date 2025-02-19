#include "../Headers/listas.h"

ptrLista* inicializaLista () /* Funcao para criar uma lista. */
{
    return NULL;
}

ptrLista* insereInicioLista (ptrLista *first, int number) /* Funcao para inserir nos contendo numeros no final de uma lista simplesmente encadeada. */
{
    ptrLista *novo; 

    novo = (ptrLista*) malloc (sizeof(ptrLista)); 
    novo->tweet = number; 
    novo->prox = first; 

    return novo; 
}

void imprimeListaArquivo (ptrLista* ptrListaTweet, FILE *arq) /* Funcao para a impressao de toda a lista de numeros em um arquivo texto, utilizando comando iterativo. */
{
    ptrLista *ptaux;

    if (ptrListaTweet == NULL)
        fprintf (arq, "A lista esta vazia.\n");
    else 
    {
        for (ptaux = ptrListaTweet; ptaux != NULL; ptaux = ptaux->prox)
            fprintf (arq, "%d, ", ptaux->tweet);
    }
}

int consultaLSE (ptrLista *ptrListaTweet, int number) /* Funcao para determinar se um determinado tweet ja esta inserido na lista. */
{
    if (ptrListaTweet == NULL)
        return 0;

    else if (ptrListaTweet->tweet == number)
        return 1;

    else
        return 0;
}

void liberaLista(ptrLista *lista) /* Funcao para desalocar a lista simplesmente encadeada de tweets. */
{
    ptrLista *aux;
    while (lista != NULL) 
    {
        aux = lista; 
        lista = lista->prox; 
        free(aux);
    }
}

