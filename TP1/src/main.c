    #include <stdio.h>
    #include "ordind.h"

int main(int argc, char ** argv){
    //char aux[100];
    OrdInd_ptr poi = Cria();
    CarregaArquivo(poi,"entrada.xcsv");
    
    /*
    int numatrib = NumAtributos(poi);
    for (int i = 0; i<numatrib; i++){
        if (NomeAtributo(poi,i,aux)>0){
            if (!strcmp(aux,"Nome")||!strcmp(aux,"CPF")||!strcmp(aux,"End")){
                CriaIndice(poi,i);
                OrdenaIndice (poi,i);
                ImprimeOrdenadoIndice (poi,i);
            }
        }
    }*/
    Destroi(poi);
    return 0;
}