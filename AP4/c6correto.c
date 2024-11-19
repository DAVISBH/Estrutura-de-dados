#include <stdlib.h>
#include <stdint.h>

struct _List {
    int32_t* data;
    int32_t length;
};
typedef struct _List List;

List* resizeArray(List* array) {
    // Aloca mais memória para os dados (realoca o array)
    int32_t*dPtr = realloc(array->data, 15 * sizeof(int32_t)); // Aloca 15 inteiros
    
    if (dPtr) {
        return array;
    }
    // Atualiza o ponteiro 'data' de array
    array->data =dPtr;
    return array;
}

int main() {
    List* array = calloc(1, sizeof(List));
    array->data = calloc(10, sizeof(int32_t));
    array = resizeArray(array);

    free(array->data);
    free(array);
    return 0;
}
