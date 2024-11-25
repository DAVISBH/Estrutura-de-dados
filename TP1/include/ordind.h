#ifndef ORDIND_H    // Guarda de inclusão
#define ORDIND_H

#include <stdio.h>  // Incluir outras bibliotecas necessárias
#include <stdlib.h> // Para malloc, free
#include <string.h> // Para manipulação de strings

// Definição de tipos
typedef struct OrdInd {
    char **atributos;    // Nomes dos atributos
    int numAtributos;    // Número de atributos
    char ***registros;   // Matriz de registros [n_registros][n_atributos]
    int numRegistros;    // Número de registros
    int **indices;       // Vetores de índices para ordenação
} OrdInd_t, *OrdInd_ptr;

// Declarações de funções
OrdInd_ptr Cria();
int Destroi(OrdInd_ptr poi);
int CarregaArquivo(OrdInd_ptr poi, char *nomeentrada);
int NumAtributos(OrdInd_ptr poi);
int NomeAtributo(OrdInd_ptr poi, int pos, char *nome);
int CriaIndice(OrdInd_ptr poi, int atribid);
int OrdenaSelectionSort(OrdInd_ptr poi, int atrbid);
void OrdenaBubbleSort(OrdInd_ptr poi, int atribid);
void OrdenaQuickSort(OrdInd_ptr poi, int atribid, int low, int high);
int Particao(OrdInd_ptr poi, int atribid, int low, int high);
void ImprimeOrdenadoIndice(OrdInd_ptr poi, int atribid);

#endif // ORDIND_H
