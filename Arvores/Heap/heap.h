#ifndef HEAP_H
#define HEAP_H

class Heap{

    public:
        Heap();
        void Insere(int valor);
        void Heapfy(int posicao_inserida, int v[10]);
        void Print();
        int Remove();
        int GetMaiorSucessor(int i, int v[10]);


    private:
        int dados[10];
        int tamanho;
        int MAX_TAM;
};

#endif