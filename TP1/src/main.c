#include <stdio.h>
#include "ordind.h"
#include <time.h>
#include <sys/time.h>   


int main(int argc, char **argv) {
    char aux[100];
    clock_t start, end;
    double cpu_time_used;

    for (int algorithm_op = 0; algorithm_op < 3; algorithm_op ++){  // Realiza o processo de ordenacao com cada algoritmo (3 vezes)
        OrdInd_ptr poi = Cria();
        if(argc != 2){
            return 1;
        }

        start = clock();
        CarregaArquivo(poi, argv[1]);
        int numatrib = NumAtributos(poi);

        for (int i = 0; i < numatrib; i++) {        // Realiza o processo de ordenacao para cada um dos atributos
            if (NomeAtributo(poi, i, aux)) {
                if (!strcmp(aux, "name") || !strcmp(aux, "id") || !strcmp(aux, "address")) {
                    switch (algorithm_op){
                        case 0:
                            CriaIndice(poi, i);
                            OrdenaQuickSort(poi, i, 0, poi->numRegistros - 1);
                            //ImprimeOrdenadoIndice(poi, i, argv[1]); 
                            break;
                        case 1:
                            CriaIndice(poi, i);
                            OrdenaBubbleSort(poi, i);
                            //ImprimeOrdenadoIndice(poi, i, argv[1]);
                            break;       
                        case 2:
                            CriaIndice(poi, i);
                            OrdenaSelectionSort(poi, i);
                            //ImprimeOrdenadoIndice(poi, i, argv[1]);
                            break;  
                        default:
                            break;
                    }            
                }
            }   

        }
        Destroi(poi);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Tempo de execução: %.6f segundos\n", cpu_time_used);
    }

    return 0;
}