#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <stddef.h>

#define ALGINSERTION 1
#define ALGSELECTION 2
#define ALGQSORT     3
#define ALGQSORT3    4
#define ALGQSORTINS  5
#define ALGQSORT3INS 6
#define ALGSHELLSORT 7
#define ALGRECSEL    8

// Estrutura de desempenho
typedef struct sortperf {
    int cmp;
    int move;
    int calls;
} sortperf_t;

// Funções de ordenação
void insertionSort(int *v, int l, int r, sortperf_t *s);
void selectionSort(int arr[], int l, int r, sortperf_t *s);
/*
void shellSort(int *A, int n, sortperf_t *s);
void quickSort(int *A, int l, int r, sortperf_t *s);
void quickSort3(int *A, int l, int r, sortperf_t *s);
void quickSortIns(int *A, int l, int r, sortperf_t *s);
void quickSort3Ins(int *A, int l, int r, sortperf_t *s);
void recursiveSelectionSort(int arr[], int l, int r, sortperf_t *s);
*/
#endif // ALGORITHMS_H
