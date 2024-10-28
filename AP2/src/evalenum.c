#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "algorithms.h"
#include "utils.h"

int main(int argc, char **argv) {
    sortperf_t s;
    int *vet;
    char buf[200];
    char pref[100];
    opt_t opt;
    struct timespec inittp, endtp, restp;

    parse_args(argc, argv, &opt);

    vet = (int *)malloc((opt.size + 1) * sizeof(int));

    resetcounter(&s);
    srand48(opt.seed);
    initVector(vet, opt.size);
    vet[opt.size] = vet[0]; // for heapsort

    clock_gettime(CLOCK_MONOTONIC, &inittp);

    switch (opt.alg) {
        case ALGINSERTION:
            insertionSort(vet, 0, opt.size - 1, &s);
            break;
        case ALGSELECTION:
            selectionSort(vet, 0, opt.size - 1, &s);
            break;
            /*
        case ALGQSORT:
            quickSort(vet, 0, opt.size - 1, &s);
            break;
        case ALGQSORT3:
            quickSort3(vet, 0, opt.size - 1, &s);
            break;
        case ALGQSORTINS:
            quickSortIns(vet, 0, opt.size - 1, &s);
            break;
        case ALGQSORT3INS:
            quickSort3Ins(vet, 0, opt.size - 1, &s);
            break;
        case ALGSHELLSORT:
            // Chamar heapsort
            break;
        case ALGRECSEL:
            recursiveSelectionSort(vet, 0, opt.size - 1, &s);
            break;
            */
        default:
            fprintf(stderr, "Algoritmo inválido.\n");
            exit(1);
    }

    clock_gettime(CLOCK_MONOTONIC, &endtp);
    clkDiff(inittp, endtp, &restp);

    printf("%s\n", printsortperf(&s, buf, "alg"));
    printf("Tempo: %ld.%09ld segundos\n", restp.tv_sec, restp.tv_nsec);

    free(vet);
    return 0;
}
