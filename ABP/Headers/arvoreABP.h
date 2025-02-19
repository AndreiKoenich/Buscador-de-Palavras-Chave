#ifndef ARVORE_ABP_H
#define ARVORE_ABP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"
#include "listas.h"
#include "gerais.h"

ptrNodoArvore* inicializaArvore (); /* Funcao para criar uma arvore. */
ptrNodoArvore* consultaComum (ptrNodoArvore *a, char *chave); /* Funcao para determinar se uma determinada palavra ja esta inserida na arvore. */
ptrNodoArvore* insereABP (ptrNodoArvore *a, TipoInfoAux chave); /* Funcao para inserir nos na ABP de acordo com a ordem lexicografica das palavras. */
int contaNodos(ptrNodoArvore *a); /* Funcao para determinar o total de nodos de uma arvore binaria. */
int calculaAltura (ptrNodoArvore *a); /* Funcao para determinar a altura de uma arvore cuja raiz e passada como parametro. */
ptrNodoArvore* indexaArvoreABP (ptrNodoArvore *a, char *nomeArquivoEntrada); /* Funcao para realizar as indexacoes das palavras e dos tweets em uma arvore binaria de pesquisa. */
void consultaArvoreABP (ptrNodoArvore *a, char *nomeArquivoConsultas, char *nomeArquivoSaida); /* Funcao para realizar a consulta das palavras do arquivo de consultas na arvore e imprimi-las no arquivo de saida, com seus respectivos tweets. */
void liberaArvore(ptrNodoArvore *raiz); /* Funcao recursiva para desalocar a arvore e suas listas de tweets. */

#endif