#ifndef LISTAS_H
#define LISTAS_H

#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"

ptrLista* inicializaLista (); /* Funcao para criar uma lista. */
ptrLista* insereInicioLista (ptrLista *first, int number); /* Funcao para inserir nos contendo numeros no final de uma lista simplesmente encadeada. */
int consultaLSE (ptrLista *ptrListaTweet, int number); /* Funcao para determinar se um determinado tweet ja esta inserido na lista. */
void imprimeListaArquivo (ptrLista* ptrListaTweet, FILE *arq); /* Funcao para a impressao de toda a lista de numeros em um arquivo texto, utilizando comando iterativo. */
void liberaLista(ptrLista *lista); /* Funcao para desalocar a lista simplesmente encadeada de tweets. */

#endif