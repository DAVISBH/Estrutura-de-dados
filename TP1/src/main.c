#include <stdio.h>
#include "ordind.h"

int main(int argc, char ** argv){
    char aux[100];
    OrdInd_ptr poi = Cria();
    CarregaArquivo(poi,"cad/entrada2.xcsv");

    int numatrib = NumAtributos(poi);
    
    for (int i = 0; i < numatrib; i++){
        if (NomeAtributo(poi,i,aux)){
            if (!strcmp(aux,"name")||!strcmp(aux,"id")||!strcmp(aux,"address")){
                CriaIndice(poi,i);
                OrdenaSelectionSort(poi, i);     
                OrdenaBubbleSort(poi, i);
                OrdenaQuickSort(poi, i, 0, poi->numRegistros - 1);
                ImprimeOrdenadoIndice (poi, i);
                getchar();
            } 
        }
    }

    Destroi(poi);
    return 0;
}
