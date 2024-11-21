#include <stdio.h>
#include <ordind.h>
#include <string.h>

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
        return 0;
    }

    char linha[1024];

    // Ler cabeçalho
    if (fgets(linha, sizeof(linha), file)) {
        char *token = strtok(linha, ",");
        while (token) {
            // Remover possíveis caracteres indesejados (\n, \r)
            token[strcspn(token, "\r\n")] = '\0';

            // Realocar memória para os atributos
            char **novoAtributos = realloc(poi->atributos, (poi->numAtributos + 1) * sizeof(char *));
            if (!novoAtributos) {
                fprintf(stderr, "Erro: Falha ao alocar memória para os atributos.\n");
                fclose(file);
                return 0;
            }
            poi->atributos = novoAtributos;

            // Copiar o nome do atributo
            poi->atributos[poi->numAtributos] = strdup(token);
            if (!poi->atributos[poi->numAtributos]) {
                fprintf(stderr, "Erro: Falha ao duplicar o atributo.\n");
                fclose(file);
                return 0;
            }

            poi->numAtributos++;
            token = strtok(NULL, ",");
        }
    } else {
        fprintf(stderr, "Erro: Arquivo vazio ou inválido.\n");
        fclose(file);
        return 0;
    }

    // Ler registros
    while (fgets(linha, sizeof(linha), file)) {
        // Realocar memória para os registros
        char ***novoRegistros = realloc(poi->registros, (poi->numRegistros + 1) * sizeof(char **));
        if (!novoRegistros) {
            fprintf(stderr, "Erro: Falha ao alocar memória para os registros.\n");
            fclose(file);
            return 0;
        }
        poi->registros = novoRegistros;

        // Alocar memória para as colunas do novo registro
        poi->registros[poi->numRegistros] = malloc(poi->numAtributos * sizeof(char *));
        if (!poi->registros[poi->numRegistros]) {
            fprintf(stderr, "Erro: Falha ao alocar memória para as colunas do registro.\n");
            fclose(file);
            return 0;
        }

        // Preencher as colunas do registro
        char *token = strtok(linha, ",");
        for (int i = 0; i < poi->numAtributos; i++) {
            if (token) {
                // Remover possíveis caracteres indesejados (\n, \r)
                token[strcspn(token, "\r\n")] = '\0';

                // Duplicar o valor do campo
                poi->registros[poi->numRegistros][i] = strdup(token);
                if (!poi->registros[poi->numRegistros][i]) {
                    fprintf(stderr, "Erro: Falha ao duplicar o campo do registro.\n");
                    fclose(file);
                    return 0;
                }
                token = strtok(NULL, ",");
            } else {
                // Caso o número de colunas seja menor que o esperado
                fprintf(stderr, "Erro: Registro incompleto na linha %d.\n", poi->numRegistros + 1);
                fclose(file);
                return 0;
            }
        }
        poi->numRegistros++;
    }

    fclose(file);
    return 1;
}

int NumAtributos(OrdInd_ptr poi){
    return poi->numAtributos;
}