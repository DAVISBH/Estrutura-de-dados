#include <stdio.h>
#include "ordind.h"

void printOrdInd(const OrdInd_t *ordInd) {
    // Verifica se o ponteiro é válido
    if (!ordInd) {
        printf("Estrutura inválida.\n");
        return;
    }

    // Imprime os atributos
    //printf("Atributos (%d):\n", ordInd->numAtributos);
    for (int i = 0; i < ordInd->numAtributos; i++) {
        if (ordInd->atributos[i]) {
            //printf("  [%d]: %s\n", i, ordInd->atributos[i]);
        }
    }

    // Imprime os registros
    printf("Registros (%d):\n", ordInd->numRegistros);
    for (int i = 0; i < ordInd->numRegistros; i++) {
        printf("  Registro %d:\n", i+1);
        for (int j = 0; j < ordInd->numAtributos; j++) {
            if (ordInd->registros[i][j]) {
                printf("    [%d]: %s\n", j, ordInd->registros[i][j]);
            }
        }
    }
}

int main(int argc, char ** argv){
    char aux[100];
    OrdInd_ptr poi = Cria();
    CarregaArquivo(poi,"cad/entrada.xcsv");
    //printOrdInd(poi);

    int numatrib = NumAtributos(poi);
    
    for (int i = 0; i<numatrib; i++){
        if (NomeAtributo(poi,i,aux)){
            if (!strcmp(aux,"name")||!strcmp(aux,"id")||!strcmp(aux,"address")){
                CriaIndice(poi,i);
                for(int i = 0; i < poi->numRegistros; i++){
                    printf("%d ", poi->indices[2][i]);
                }
                OrdenaIndice (poi,i);
                //ImprimeOrdenadoIndice (poi,i);
            } 
        }
    }

    Destroi(poi);
    return 0;

}
