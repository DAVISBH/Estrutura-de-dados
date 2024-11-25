#include <stdio.h>
#include "ordind.h"
#include <sys/time.h>

int main(int argc, char **argv) {
    char aux[100];
    OrdInd_ptr poi = Cria();
    
    CarregaArquivo(poi, "cad/entrada3.xcsv");

    int numatrib = NumAtributos(poi);
    char *opcao = argv[1];

    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (int i = 0; i < numatrib; i++) {
        if (NomeAtributo(poi, i, aux)) {
            if (!strcmp(aux, "name") || !strcmp(aux, "id") || !strcmp(aux, "address")) {
                CriaIndice(poi, i);
                switch (*opcao) {
                    case 'q':
                        OrdenaQuickSort(poi, i, 0, poi->numRegistros - 1);
                        break; // Adiciona o break
                    case 's':
                        OrdenaSelectionSort(poi, i);
                        break; // Adiciona o break
                    case 'b': 
                        OrdenaBubbleSort(poi, i);
                        break; // Adiciona o break
                    // ImprimeOrdenadoIndice(poi, i);
                }
            }
        }
    }

    gettimeofday(&end, NULL);
    double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("Tempo de execução: %f segundos\n", time_taken);

    Destroi(poi);
    return 0;
}