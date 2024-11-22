#include <stdio.h>
#include <ordind.h>
#include <string.h>

#define MAX_LINE_SIZE 4096

OrdInd_ptr Cria() {
    OrdInd_ptr poi = (OrdInd_ptr)malloc(sizeof(OrdInd_t));
    poi->atributos = NULL;
    poi->numAtributos = 0;
    poi->registros = NULL;
    poi->numRegistros = 0;
    poi->indices = NULL;
    return poi;
}

int Destroi(OrdInd_ptr poi) {
    if (poi) {
        // Liberar atributos
        if (poi->atributos) {
            for (int i = 0; i < poi->numAtributos; i++) {
                free(poi->atributos[i]);
            }
            free(poi->atributos);
        }

        // Liberar registros
        if (poi->registros) {
            for (int i = 0; i < poi->numRegistros; i++) {
                if (poi->registros[i]) {
                    for (int j = 0; j < poi->numAtributos; j++) {
                        free(poi->registros[i][j]);
                    }
                    free(poi->registros[i]);
                }
            }
            free(poi->registros);
        }

        // Liberar índices
        if (poi->indices) {
            for (int i = 0; i < poi->numAtributos; i++) {
                free(poi->indices[i]);
            }
            free(poi->indices);
        }

        // Liberar a estrutura principal
        free(poi);
    }
    return 1;
}

int CarregaArquivo(OrdInd_ptr poi, char *nomeentrada) {
    FILE *file = fopen(nomeentrada, "r");
    if (!file) {
        fprintf(stderr, "Erro: Não foi possível abrir o arquivo '%s'.\n", nomeentrada);
        return 1;
    }

    char linha[MAX_LINE_SIZE];

    // Lê a primeira linha do arquivo
    if (fgets(linha, sizeof(linha), file) != NULL) {
        // Converte a string da linha para um número inteiro
        int num_atributos = atoi(linha) - 1;  // atoi converte a string para int
        //printf("Número de atributos: %d\n", num_atributos);
        poi->numAtributos = num_atributos;
    }

    // Aloca memória para o vetor de atributos
    poi->atributos = (char **)malloc(poi->numAtributos * sizeof(char *));
    if (!poi->atributos) {
        fprintf(stderr, "Erro ao alocar memória para o vetor de atributos.\n");
        fclose(file);
        return 1;
    }

    int count = 0;

    // Lê as linhas do arquivo para os atributos
    while (count < poi->numAtributos && fgets(linha, sizeof(linha), file) != NULL) {
        size_t len = strlen(linha);
        //printf("Linha lida: %s", linha);

        // Verifica se a linha termina com ",s"
        if (len >= 3 && linha[len - 3] == ',' && linha[len - 2] == 's' && linha[len - 1] == '\n') {
            // Remove o '\n' do final da linha, se houver
            linha[len - 3] = '\0';

            // Aloca memória para armazenar a linha no vetor de atributos
            poi->atributos[count] = (char *)malloc((len + 1) * sizeof(char));
            if (!poi->atributos[count]) {
                fprintf(stderr, "Erro ao alocar memória para atributo[%d].\n", count);
                
                // Libera a memória já alocada antes de sair
                for (int i = 0; i < count; i++) {
                    free(poi->atributos[i]);
                }
                free(poi->atributos);
                fclose(file);
                return 1;
            }

            strcpy(poi->atributos[count], linha);  // Copia a linha para atributos[count]
            count++;
        }
    }

    fgets(linha, sizeof(linha), file);

    // Lê a linha do arquivo que indica o numero de registros
    if (fgets(linha, sizeof(linha), file) != NULL) {
        int num_registros = atoi(linha);  // atoi converte a string para int
        poi->numRegistros = num_registros;
    }

    // Aloca memória para o vetor de registros
    poi->registros = (char ***)malloc(poi->numRegistros * sizeof(char **));
    if (!poi->registros) {
        fprintf(stderr, "Erro ao alocar memória para os registros.\n");
        fclose(file);
        return 1;
    }

    // Lê os registros do arquivo
    int registroCount = 0;
    while (fgets(linha, sizeof(linha), file) && registroCount < poi->numRegistros) {
        
        // Aloca memória para as colunas do registro
        poi->registros[registroCount] = (char **)malloc(poi->numAtributos * sizeof(char *));
        if (!poi->registros[registroCount]) {
            fprintf(stderr, "Erro ao alocar memória para as colunas do registro %d.\n", registroCount);
            fclose(file);
            return 1;
        }

        // Inicializa o token com o primeiro campo da linha
        char *token = strtok(linha, ",");
        int count = 0;

        // Divide a linha em tokens e armazena nas colunas do registro
        while (token != NULL && count < poi->numAtributos) {
            poi->registros[registroCount][count] = strdup(token);
            token = strtok(NULL, ",");
            count++;
        }

        // Se o número de tokens extraídos for menor que o número de atributos, ignora a linha
        if (count < poi->numAtributos) {
            // Linha incompleta, não fazer nada e passar para o próximo registro
            continue;
        }

        registroCount++;
    }
    
    fclose(file);
    return 0;   
}

int NomeAtributo(OrdInd_ptr poi, int pos, char *nome){
    if (!poi || !poi->atributos || pos < 0 || !nome)
        return 0; // Erro: ponteiro nulo ou posição inválida
    
    strcpy(nome, poi->atributos[pos]); // Copia o nome para o buffer fornecido
    
    if(nome == NULL)
        return 0;

    return 1; // Sucesso
}

int NumAtributos(OrdInd_ptr poi){
    if(poi)
        return poi->numAtributos;
    return -1;
}

int CriaIndice(OrdInd_ptr poi, int atribid) {
    if (atribid >= poi->numAtributos) return 0;

    poi->indices = realloc(poi->indices, (atribid + 1) * sizeof(int *));
    poi->indices[atribid] = malloc(poi->numRegistros * sizeof(int));
    for (int i = 0; i < poi->numRegistros; i++)
        poi->indices[atribid][i] = i;

    return 1;
}

// Função de comparação para a ordenação dos índices com base no atributo
int comparaIndice(const void *a, const void *b, void *param) {
    OrdInd_ptr poi = (OrdInd_ptr)param;
    int indexA = *(int *)a;
    int indexB = *(int *)b;

    // Comparar os valores dos registros de acordo com o atributo (atribid)
    return strcmp(poi->registros[indexA][*(int *)param], poi->registros[indexB][*(int *)param]);
}

// Função para ordenar os índices (ordenar indiretamente os registros)
int OrdenaIndice(OrdInd_ptr poi, int atribid) {
    if (!poi || atribid >= poi->numAtributos || !poi->indices || !poi->indices[atribid]) return 0;

    int *indice = poi->indices[atribid];

    // Passa o parâmetro 'poi' para a função de comparação
    qsort_r(indice, poi->numRegistros, sizeof(int), comparaIndice, (void *)poi);
    
    return 1;
}