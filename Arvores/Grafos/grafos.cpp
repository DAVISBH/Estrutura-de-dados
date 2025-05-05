#include <iostream>
#include "grafos.h"

using namespace std;

LinkedList::LinkedList() {
    head = nullptr;
}

LinkedList::~LinkedList() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void LinkedList::insertAtBeginning(int value) {
    Node* newNode = new Node{value, head};
    head = newNode;
}

void LinkedList::insertAtEnd(int value) {
    Node* current = head;

    //Checa se int value já está na lista
    while (current != nullptr){
        if (current->data == value)
            return;
        current = current->next;
    }


    Node* newNode = new Node{value, nullptr};
    if (head == nullptr) {
        head = newNode;
        return;
    }

    current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = newNode;
}

void LinkedList::remove(int value) {
    if (head == nullptr) return;

    if (head->data == value) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* current = head;
    while (current->next != nullptr && current->next->data != value) {
        current = current->next;
    }

    if (current->next != nullptr) {
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }
}

void LinkedList::display() {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " -> ";
        current = current->next;
    }
    cout << "NULL" << endl;
}

int LinkedList::getSize(){
    Node* current = this->head;
    int count = 0;

    while (current != nullptr){
        count += 1;
        current = current->next;
    }

    return count;
}


//====================================================

Grafo::Grafo(){
    this->grafo.vertices = 0;
    this->grafo.arestas = nullptr;
}

void Grafo::InsereVertice() {
    // Novo array com espaço para mais um vértice
    LinkedList* novoArray = new LinkedList[this->grafo.vertices + 1];

    // Copiar as listas antigas para o novo array
    for (int i = 0; i < this->grafo.vertices; ++i) {
        novoArray[i] = this->grafo.arestas[i];  // cópia superficial; pode precisar de cópia profunda se necessário
    }

    // Liberar memória antiga
    delete[] this->grafo.arestas;

    // Atualizar ponteiro e contador
    this->grafo.arestas = novoArray;
    this->grafo.vertices += 1;
}

void Grafo::InsereAresta(int v, int w){
    this->grafo.arestas[v].insertAtEnd(w);
}

ListaAdjacencia Grafo::GetGrafo(){
    return this->grafo;
}

int Grafo::QuantidadeVertices(){
    return (this->grafo.vertices);
}

int Grafo::QuantidadeArestas(){
    int i = 0;
    int count = 0;

    while(i < this->grafo.vertices){
        count += this->grafo.arestas[i].getSize();
        i += 1;
    }

    count = count / 2;
    return count;
}

int Grafo::GrauMinimo(){
    int i = 1;
    int menor = this->grafo.arestas[0].getSize();
    while(i < this->grafo.vertices){
        if (this->grafo.arestas[i].getSize() < menor)
            menor = this->grafo.arestas[i].getSize();
    }

    return menor;
}

int Grafo::GrauMaximo(){
    int i = 1;
    int maior = this->grafo.arestas[0].getSize();
    while(i < this->grafo.vertices){
        if (this->grafo.arestas[i].getSize() > maior)
            maior = this->grafo.arestas[i].getSize();
        i += 1;
    }

    return maior;
}

void Grafo::ImprimeVizinhos(int v){
    this->grafo.arestas[v].display();
}

Grafo::~Grafo() {
    delete[] this->grafo.arestas;
}