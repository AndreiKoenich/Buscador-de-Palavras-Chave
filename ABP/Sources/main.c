#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../Headers/constantes.h"
#include "../Headers/estruturas.h"
#include "../Headers/arvoreABP.h"

int comparacoes = 0;

int main ()
{
    char nomeArquivoEntrada[MAXIMOCARACTERES];
    char nomeArquivoConsultas[MAXIMOCARACTERES];
    char nomeArquivoSaida[MAXIMOCARACTERES];

    system("clear");
    printf("BUSCADOR DE PALAVRAS-CHAVE COM ARVORE BINARIA DE PESQUISA\n");
    printf("\nAUTOR: Andrei Pochmann Koenich\n");
    printf("\n--------------------------------\n");

    printf("\nDigite o nome do arquivo texto de entrada, contendo os tweets:\n");
    scanf("%s", nomeArquivoEntrada);

    clock_t starting_time, finishing_time;
    starting_time = clock();

    ptrNodoArvore *raizABP = inicializaArvore();
    raizABP = indexaArvoreABP (raizABP, nomeArquivoEntrada);

    printf("\nDigite o nome do arquivo texto de consultas:\n");
    scanf("%s", nomeArquivoConsultas);
    printf("\nEscolha o nome do arquivo de saida:\n");
    scanf("%s", nomeArquivoSaida);
    system("clear");

    consultaArvoreABP (raizABP, nomeArquivoConsultas, nomeArquivoSaida); 

    printf("Operacoes realizadas com sucesso.\n");
    finishing_time = clock();
    printf("\nTempo de execucao: %ld ms\n", finishing_time - starting_time);

    liberaArvore(raizABP);

    return 0; 
}
