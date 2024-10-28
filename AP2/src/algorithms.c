#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algorithms.h"

// Funções auxiliares
void swap(int *xp, int *yp, sortperf_t *s) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
    s->move += 3;
}

// Insertion sort
void insertionSort(int v[], int l, int r, sortperf_t *s) {
    // Implementação da função de ordenação
}

// Selection sort
void selectionSort(int arr[], int l, int r, sortperf_t *s) {
    // Implementação da função de ordenação
}

// Shell sort
void shellSort(int *A, int n, sortperf_t *s) {
    // Implementação da função de ordenação
}

// Quicksort
void quickSort(int *A, int l, int r, sortperf_t *s) {
    // Implementação da função de ordenação
}

// Quicksort com mediana de 3
void quickSort3(int *A, int l, int r, sortperf_t *s) {
    // Implementação da função de ordenação
}

// Quicksort com inserção para pequenas partições
void quickSortIns(int *A, int l, int r, sortperf_t *s) {
    // Implementação da função de ordenação
}

// Quicksort com inserção e mediana de 3
void quickSort3Ins(int *A, int l, int r, sortperf_t *s) {
    // Implementação da função de ordenação
}

// Recursive selection sort
void recursiveSelectionSort(int arr[], int l, int r, sortperf_t *s) {
    // Implementação da função de ordenação
}
