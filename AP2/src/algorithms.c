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
    inccalls(s, 1);  // Conta a chamada para o insertionSort

    int i, j, aux;

    // Laço para percorrer o array do segundo elemento até o final
    for (i = l + 1; i <= r; i++) {
        aux = v[i];
        incmove(s, 1);  // Conta o movimento de salvar `aux`
        j = i - 1;

        inccmp(s, 1);
        // Desloca elementos maiores que `aux` para uma posição à frente
        while (j >= 0 && aux < v[j]) {
            inccmp(s, 1);  // Conta uma comparação
            v[j + 1] = v[j];
            incmove(s, 1);  // Conta o movimento do deslocamento
            j--;
        }
        
        // Insere `aux` na posição correta
        v[j + 1] = aux;
        incmove(s, 1);  // Conta o movimento de colocar `aux` em `v[j + 1]`
    }
}

// Selection sort
void selectionSort(int arr[], int l, int r, sortperf_t *s) {
    inccalls(s, 1);
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

// Particao para Quicksort
void Particao(int Esq, int Dir, int *i, int *j, int *A, sortperf_t *s) {
    inccalls(s, 1);
    int x, w;
    *i = Esq; 
    *j = Dir;
    x = A[(*i + *j) / 2]; // obtém o pivô x
    do {
        while (A[*i] < x) {
            inccmp(s, 1);
            (*i)++;  // Comparação com o pivô           
        }
        while (A[*j] > x){
            inccmp(s, 1);
            (*j)--;  // Comparação com o pivô
        }
        inccmp(s, 1);
        if (*i <= *j) {
            // Troca A[*i] com A[*j]
            w = A[*i];
            A[*i] = A[*j];
            A[*j] = w;
            incmove(s, 3); // Incremento de operações de movimentação
            (*i)++; 
            (*j)--;
        }
        inccmp(s, 1);
    } while (*i <= *j);
}

// QuickSort
void quickSort(int Esq, int Dir, int *A, sortperf_t *s) {
    inccalls(s, 1);
    int i, j;
    // Chama a função de partição para dividir o array
    Particao(Esq, Dir, &i, &j, A, s);

    // Chama QuickSort recursivamente nas duas subparte
    if (Esq < j) quickSort(Esq, j, A, s); // Ordena a parte esquerda
    if (i < Dir) quickSort(i, Dir, A, s); // Ordena a parte direita
}

// shellsort
void shellSort(int *A, int n, sortperf_t * s) {
    inccalls(s, 1);
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = A[i];
            int j;
            inccmp(s, 1);
            incmove(s, 1);
            for (j = i; j >= gap && A[j - gap] > temp; j -= gap) {
                A[j] = A[j - gap];
                incmove(s, 1);
                inccmp(s, 1); 
            }
            A[j] = temp;
            incmove(s, 1);
        }
    }
}

// recursive selection sort
void recursiveSelectionSort(int arr[], int l, int r, sortperf_t * s)
{
    // find the minimum element in the unsorted subarray [i…n-1]
    // and swap it with arr[i]
    int min = l;
    inccalls(s,1);
    for (int j = l + 1; j <= r; j++)
    {
        // if arr[j] is less, then it is the new minimum
	inccmp(s,1);
        if (arr[j] < arr[min]) {
            min = j;    // update the index of minimum element
        }
    }

    // swap the minimum element in subarray arr[i…n-1] with arr[i]
    if (min!=l)
      swap(&arr[min], &arr[l], s);

    if (l + 1 < r) {
        recursiveSelectionSort(arr, l + 1, r, s);
    }
}

