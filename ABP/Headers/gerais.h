#ifndef GERAIS_H
#define GERAIS_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "estruturas.h"
#include "arvoreABP.h"

void imprimeEstatisticas (FILE *arqSaida, ptrNodoArvore *a, int aux_comparacoes_index); /* Funcao para realizar as impressoes dos dados das estatisticas de indexacao e consulta no arquivo de saida. */
void converteMinuscula (char *s); /* Funcao para converter os caracteres de uma string em minusculo. */

#endif