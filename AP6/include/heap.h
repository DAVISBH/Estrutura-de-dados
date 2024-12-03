#ifndef HEAP_H
#define HEAP_H

typedef struct s_heap {
    int tamanho;
    int capacidade;
    int* dados;
} Heap;

Heap* NovoHeap(int maxsize);
void DeletaHeap(Heap* h);
void Inserir(Heap* h, int x);
int Remover(Heap* h);
int GetAncestral(Heap* h, int posicao);
int GetSucessorEsq(Heap* h, int posicao);
int GetSucessorDir(Heap* h, int posicao);
int Vazio(Heap* h);
void HeapifyPorBaixo(Heap* h, int posicao);
void HeapifyPorCima(Heap* h, int posicao);

#endif
