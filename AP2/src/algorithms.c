#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algorithms.h"
#include "utils.h"


// Funções auxiliares
void swap(int *xp, int *yp, sortperf_t *s) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
    s->move += 3;
}

// Insertion sort
void insertionSort(int v[], int l, int r, sortperf_t *s) {
    for (int i = l + 1; i <= r; i++) {
        int aux = v[i];
        int j = i - 1;

        // Move os elementos que são maiores que aux para uma posição à frente
        while (j >= l && v[j] > aux) {
            v[j + 1] = v[j];  
            inccmp(s, 1);     
            incmove(s, 1);    
            j--;
        }
        v[j + 1] = aux;      
        incmove(s, 1);        
    }
}

// Selection sort
void selectionSort(int arr[], int l, int r, sortperf_t *s) {

    int i, j, Min;

    for(i = l; i <= r ; i++){
        Min = i;
        for(j = i+1; j <= r; j++){
            inccmp(s, 1);
            if (arr[j] < arr[Min])
                Min = j;
        }

        // Troca somente se Min mudou
        if (Min != i) {
            swap(&arr[i], &arr[Min], s);
        }
    }
}


/*
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
*/