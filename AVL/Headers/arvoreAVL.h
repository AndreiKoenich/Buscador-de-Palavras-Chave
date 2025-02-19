#ifndef ARVOREAVL_H
#define ARVOREAVL_H

#include <stdio.h>
#include <stdlib.h>

#include "estruturas.h"
#include "listas.h"
#include "gerais.h"

ptrNodoArvore* inicializaArvore (); /* Funcao para criar uma arvore. */
ptrNodoArvore* rotacaoDireita(ptrNodoArvore *pt);
ptrNodoArvore* rotacaoEsquerda(ptrNodoArvore *pt);
ptrNodoArvore* rotacaoDuplaDireita (ptrNodoArvore* pt);
ptrNodoArvore* rotacaoDuplaEsquerda (ptrNodoArvore* pt);
ptrNodoArvore* caso1 (ptrNodoArvore* a, int *ok);
ptrNodoArvore* caso2 (ptrNodoArvore *a, int *ok);
ptrNodoArvore* insereAVL (ptrNodoArvore *a, TipoInfoAux x, int *ok); /* Funcao para inserir nos na arvore AVL de acordo com a ordem lexicografica das palavras. */
ptrNodoArvore* consultaComum (ptrNodoArvore *a, char *chave); /* Funcao para determinar se uma determinada palavra ja esta inserida na arvore. */
ptrNodoArvore* indexaArvoreAVL(ptrNodoArvore *a, char *nomeArquivoEntrada);  /* Funcao para realizar as indexacoes das palavras e dos tweets em uma arvore binaria de pesquisa. */
void consultaArvoreAVL (ptrNodoArvore *a, char *nomeArquivoConsultas, char *nomeArquivoSaida); /* Funcao para realizar a consulta das palavras do arquivo de consultas na arvore e imprimi-las no arquivo de saida, com seus respectivos tweets. */
int contaNodos(ptrNodoArvore *a);  /* Funcao para determinar o total de nodos de uma arvore binaria. */
int calculaAltura (ptrNodoArvore *a); /* Funcao para determinar a altura de uma arvore cuja raiz e passada como parametro. */
void liberaArvore(ptrNodoArvore *raiz); /* Funcao recursiva para desalocar a arvore e suas listas de tweets. */

#endif