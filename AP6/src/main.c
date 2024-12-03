#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int main() {
    int n;
    scanf("%d", &n);

    Heap* h = NovoHeap(n);

    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        Inserir(h, x);
    }

    while (!Vazio(h)) {
        printf("%d ", Remover(h));
    }

    printf("\n");
    DeletaHeap(h);
    return 0;
}
