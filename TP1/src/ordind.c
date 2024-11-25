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

int OrdenaSelectionSort(OrdInd_ptr poi, int atribid) {
    // Verifica se os registros estão disponíveis
    if (!poi || !poi->registros || poi->numRegistros <= 0 || atribid < 0 || atribid >= poi->numAtributos) {
        fprintf(stderr, "Erro: Estrutura de registros inválida ou atributo fora do intervalo.\n");
        return 0;
    }

    // Inicializa o vetor de índices para o atributo atribid, se necessário
    if (!poi->indices) {
        poi->indices = malloc(sizeof(int *) * poi->numAtributos);
        for (int i = 0; i < poi->numAtributos; i++) {
            poi->indices[i] = NULL;
        }
    }
    if (!poi->indices[atribid]) {
        poi->indices[atribid] = malloc(sizeof(int) * poi->numRegistros);
        for (int i = 0; i < poi->numRegistros; i++) {
            poi->indices[atribid][i] = i;  // Inicializa o vetor de índices com a ordem natural
        }
    }

    // Pega o vetor de índices para o atributo especificado
    int *indice = poi->indices[atribid];

    // Selection Sort para ordenar indiretamente pelo atributo atribid
    for (int i = 0; i < poi->numRegistros - 1; i++) {
        int menor = i;  // Assume que o menor elemento está em `i`

        for (int j = i + 1; j < poi->numRegistros; j++) {
            // Compara os valores do atributo especificado
            if (strcmp(poi->registros[indice[j]][atribid], poi->registros[indice[menor]][atribid]) < 0) {
                menor = j;  // Atualiza a posição do menor elemento
            }
        }

        // Troca os índices para refletir a nova ordem
        if (menor != i) {
            int temp = indice[i];
            indice[i] = indice[menor];
            indice[menor] = temp;
        }
    }

    return 1;  // Sucesso
}

void OrdenaQuickSort(OrdInd_ptr poi, int atribid, int low, int high) {
    if (low < high) {
        int p = Particao(poi, atribid, low, high);
        
        // Verifica se a partição foi bem-sucedida
        if (p == -1) {
            fprintf(stderr, "Erro durante a partição.\n");
            return;  // Sai em caso de erro
        }

        OrdenaQuickSort(poi, atribid, low, p - 1);
        OrdenaQuickSort(poi, atribid, p + 1, high);
    }
}

int Particao(OrdInd_ptr poi, int atribid, int low, int high) {
    // Verifica se o ponteiro e os dados são válidos
    if (!poi || !poi->registros || !poi->indices || atribid < 0 || atribid >= poi->numAtributos) {
        fprintf(stderr, "Erro: Dados inválidos ou índice fora do limite.\n");
        return -1;  // Retorna -1 para indicar erro
    }

    int *indice = poi->indices[atribid];
    if (indice == NULL) {
        fprintf(stderr, "Erro: Índice para o atributo %d não alocado.\n", atribid);
        return -1;
    }

    // Verifica se o índice de registros está dentro do intervalo
    if (high >= poi->numRegistros || low < 0) {
        fprintf(stderr, "Erro: Índice fora do intervalo de registros.\n");
        return -1;
    }

    char *pivot = poi->registros[indice[high]][atribid];  // Pivô é o último elemento
    int i = low - 1;

    for (int j = low; j < high; j++) {
        // Verifica se as strings são válidas antes de comparar
        char *current_value = poi->registros[indice[j]][atribid];
        if (current_value == NULL || pivot == NULL) {
            fprintf(stderr, "Erro: Valor nulo encontrado durante a comparação.\n");
            return -1;  // Retorna erro se houver valor nulo
        }

        // Compara os valores do atributo, levando em conta a ordem lexicográfica
        if (strcmp(current_value, pivot) < 0) {
            i++;
            // Troca os índices
            int temp = indice[i];
            indice[i] = indice[j];
            indice[j] = temp;
        }
    }

    // Coloca o pivô na posição correta
    int temp = indice[i + 1];
    indice[i + 1] = indice[high];
    indice[high] = temp;

    return i + 1;  // Retorna a posição do pivô
}

void OrdenaBubbleSort(OrdInd_ptr poi, int atribid) {
    if (!poi || !poi->registros || poi->numRegistros <= 0 || atribid < 0 || atribid >= poi->numAtributos) {
        fprintf(stderr, "Erro: Estrutura de registros inválida ou atributo fora do intervalo.\n");
        return;
    }

    int *indice = poi->indices[atribid];

    for (int i = 0; i < poi->numRegistros - 1; i++) {
        for (int j = 0; j < poi->numRegistros - i - 1; j++) {
            if (strcmp(poi->registros[indice[j]][atribid], poi->registros[indice[j + 1]][atribid]) > 0) {
                // Troca os índices
                int temp = indice[j];
                indice[j] = indice[j + 1];
                indice[j + 1] = temp;
            }
        }
    }
}

void ImprimeOrdenadoIndice(OrdInd_ptr poi, int atribid) {
    
    int larguras[poi->numRegistros];
    for(int i = 0; i < poi->numRegistros; i++){
        larguras[i] = 0;
    }

    // Passo 1: Determinar larguras máximas para cada coluna
    for (int j = 0; j < poi->numAtributos; j++) {
        for (int i = 0; i < poi->numRegistros; i++) {
            if (poi->registros[i][j]) {
                int comprimento = strlen(poi->registros[i][j]);
                if (comprimento > larguras[j]) {
                    larguras[j] = comprimento;
                }
            }
        }
    }

    // Passo 2: Imprimir registros alinhados
    for (int i = 0; i < poi->numRegistros; i++) {
        printf("[%d] ", i+1);
        for (int j = 0; j < poi->numAtributos; j++) {
            if (poi->registros[i][j]) {
                printf("%-*s\t", larguras[j], poi->registros[poi->indices[atribid][i]][j]);
            }
        }
        printf("\n");
    }
}

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
