#ifndef ARVOREBINARIA_H
#define ARVOREBINARIA_H

class TipoItem{
    public:
        void SetChave(int valor);
        int GetChave();

    private:
    int chave;
};

class TipoNo
{
    public:
        TipoNo();

    private:
        TipoItem item;
        TipoNo *esq;
        TipoNo *dir;

    friend class ArvoreBinaria;
};


class ArvoreBinaria
{
public:
    ArvoreBinaria();
    ~ArvoreBinaria();

    void Insere(TipoItem item);
    void Caminha(int tipo);
    void Limpa();

private:
    void InsereRecursivo(TipoNo* &p, TipoItem item);
    void ApagaRecursivo(TipoNo* p);
    void PorNivel();
    void PreOrdem(TipoNo* p);
    void InOrdem(TipoNo* p);
    void PosOrdem(TipoNo* p);

    TipoNo* raiz;
};


#endif