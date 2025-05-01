#include <iostream>
#include "heap.h"

using namespace std;

int GetAncestral(int i){
    return (i-1)/2;
}

Heap::Heap(){
    this->tamanho = 0;
    this->MAX_TAM = 10;

    for (int i = 0; i < 10; i++){
        this->dados[i] = -1;
    }
}

void Heap::Insere(int valor){
    this->dados[this->tamanho] = valor;
    this->tamanho += 1;

    Heapfy(this->tamanho - 1, this->dados);
}

int Heap::GetMaiorSucessor(int i, int v[10]){
    int filhoesq = (i*2)+1;
    int filhodir = (i*2) + 2;

    // Nenhum filho existe
    if (filhoesq >= this->tamanho)
        return -1;

    // Só o filho esquerdo existe
    if (filhodir >= this->tamanho)
        return filhoesq;

    // Ambos existem
    return (v[filhoesq] > v[filhodir]) ? filhoesq : filhodir;
}

void Heap::Heapfy(int posicao_inserida, int v[10]){
    int aux;

    if (posicao_inserida > 0){
        int pai = GetAncestral(posicao_inserida);

        if (v[pai] < v[posicao_inserida])
        {
            aux = v[pai];
            v[pai] = v[posicao_inserida];
            v[posicao_inserida] = aux;

            Heapfy(pai, v);
        }
    }
}

void Heap::Print(){
    for (int i = 0; i < this->tamanho; i++){
        cout << this->dados[i] << " ";
    }
}

int Heap::Remove(){
    if (this->tamanho > 0){
        int x = this->dados[0];
        this->dados[0] = this->dados[this->tamanho - 1];
        this->tamanho -= 1;

        int i = 0;
        int s = GetMaiorSucessor(i, this->dados);
        int aux;

        while((this->dados[i] < this->dados[s]) && (s != -1)){
            aux = this->dados[i];
            this->dados[i] = this->dados[s];
            this->dados[s] = aux;
            i = s;
            s = GetMaiorSucessor(i, this->dados);
        }
        
        return x;
    }

    return -1;
}