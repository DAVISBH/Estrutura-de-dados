#include <iostream>
#include <sstream>
#include <string>
#include "grafos.h"

using namespace std;

int main() {
    int vertices;
    string linha;
    
    Grafo G;

    // Lê o número de vértices
    cin >> vertices;
    cin.ignore();

    for (int i = 0; i < vertices; i++) {
        G.InsereVertice(); // adiciona o vértice i

        getline(cin, linha);
        stringstream ss(linha);

        int num_arestas;
        ss >> num_arestas;

        for (int j = 0; j < num_arestas; j++) {
            int destino;
            ss >> destino;
            G.InsereAresta(i, destino);
        }
    }

    // Teste: imprimir os vizinhos de cada vértice
    for (int i = 0; i < G.QuantidadeVertices(); i++) {
        cout << "Vizinhos de " << i << ": ";
        G.ImprimeVizinhos(i);
    }

    return 0;
}
