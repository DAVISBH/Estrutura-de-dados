#include <iostream>
#include "arvorebinaria.h"

using namespace std;

int TipoItem::GetChave(){
    return this->chave;
}

void TipoItem::SetChave(int valor){
    this->chave = valor;
}

//==================================================================================================================

TipoNo::TipoNo(){
    this->item.SetChave(-1);
    this->dir = nullptr;
    this->esq = nullptr; 
}

//==================================================================================================================

ArvoreBinaria::ArvoreBinaria(){
    raiz = nullptr;
}

ArvoreBinaria::~ArvoreBinaria(){
    this->Limpa();
}

void ArvoreBinaria::Insere(TipoItem item){
    InsereRecursivo(this->raiz,item);
}

void ArvoreBinaria::InsereRecursivo(TipoNo* &p, TipoItem item){
    if(p==NULL){
        p = new TipoNo();
        p->item = item;
    }
    else{
        if(item.GetChave() < p->item.GetChave())
            InsereRecursivo(p->esq, item);
        else
            InsereRecursivo(p->dir, item);
    }
}

void ArvoreBinaria::Limpa(){
    ApagaRecursivo(this->raiz);
}

void ArvoreBinaria::ApagaRecursivo(TipoNo* p){
    if (p != nullptr){
        ApagaRecursivo(p->esq);
        ApagaRecursivo(p->dir);
        delete p;
        p = nullptr; // <--- importante
    }
}

void ArvoreBinaria::Caminha(int tipo){
    switch(tipo){
        case 1:
            this->PreOrdem(this->raiz);
            break;
        case 2:
            this->InOrdem(this->raiz);
            break;
        case 3:
            this->PosOrdem(this->raiz);
            break;
        case 4:
            this->PorNivel();
            break;
    }
}

void ArvoreBinaria::InOrdem(TipoNo* p){
    if (p != nullptr){
        InOrdem(p->esq);
        cout << p->item.GetChave() << endl;
        InOrdem(p->dir);
    }
}

void ArvoreBinaria::PreOrdem(TipoNo* p){
    if (p != nullptr){
        cout << p->item.GetChave() << endl;
        PreOrdem(p->esq);
        PreOrdem(p->dir);
    }
}

void ArvoreBinaria::PosOrdem(TipoNo* p){
    if (p != nullptr){
        PosOrdem(p->esq);
        PosOrdem(p->dir);
        cout << p->item.GetChave() << endl;
    }
}

void ArvoreBinaria::PorNivel(){

}