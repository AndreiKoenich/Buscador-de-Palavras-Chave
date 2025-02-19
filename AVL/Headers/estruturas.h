#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include "constantes.h"

typedef struct pLista /* Estrutura com informacoes de cada no da lista de tweets que pertence a cada um dos nos da arvore. */
{
    int tweet; 
    struct pLista *prox; 

} ptrLista;

typedef struct /* Estrutura com informacoes dos nos na arvore. */
{
    ptrLista *ptrListaTweet; 
    char palavra[MAXIMOCARACTERES]; 

} TipoInfo;

typedef struct /* Estrutura auxiliar a ser usada durante a indexacao. */
{
    int numero;
    char word[MAXIMOCARACTERES]; 

} TipoInfoAux;

typedef struct TNodoA /* Estrutura contendo os filhos dos nos. */
{
    TipoInfo info; 
    int FB; 
    struct TNodoA *esq; 
    struct TNodoA *dir; 

} ptrNodoArvore;

#endif