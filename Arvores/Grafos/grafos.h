#ifndef GRAFOS_H
#define GRAFOS_H

// Estrutura de um nó da lista encadeada
struct Node {
    int data;
    Node* next;
};

// Classe da lista encadeada
class LinkedList {
private:
    Node* head;

public:
    LinkedList();
    ~LinkedList();

    void insertAtBeginning(int value);
    void insertAtEnd(int value);
    void remove(int value);
    void display();
    int getSize();
};

//===============================================================================================================

struct ListaAdjacencia{
    int vertices;
    LinkedList* arestas;
};

//=================================================================================================================================


class Grafo{
    public:
        Grafo();
        ~Grafo();
        void InsereVertice();
        void InsereAresta(int v, int w);
        int QuantidadeVertices();
        int QuantidadeArestas();
        int GrauMinimo();
        int GrauMaximo();
        void ImprimeVizinhos(int v);
        ListaAdjacencia GetGrafo();
    
    private:
        ListaAdjacencia grafo;

   };

#endif