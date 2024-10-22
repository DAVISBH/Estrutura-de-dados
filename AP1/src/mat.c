#include "mat.h"
#include "msgassert.h"
#include <stdlib.h>
#include <stdio.h>

void criaMatriz(mat_tipo * mat, int tx, int ty, int id) {
    erroAssert(tx > 0, "Dimensao nula");
    erroAssert(ty > 0, "Dimensao nula");
    erroAssert(tx <= MAXTAM, "Dimensao maior que permitido");
    erroAssert(ty <= MAXTAM, "Dimensao maior que permitido");

    mat->tamx = tx;
    mat->tamy = ty;
    mat->id = id;
}

void inicializaMatrizNula(mat_tipo * mat) {
    for (int i = 0; i < MAXTAM; i++) {
        for (int j = 0; j < MAXTAM; j++) {
            mat->m[i][j] = 0;
        }
    }
}

void inicializaMatrizAleatoria(mat_tipo * mat) {
    inicializaMatrizNula(mat);
    for (int i = 0; i < mat->tamx; i++) {
        for (int j = 0; j < mat->tamy; j++) {
            mat->m[i][j] = rand() % INITRANDOMRANGE;
        }
    }
}

double acessaMatriz(mat_tipo * mat) {
    double s = 0.0;
    for (int i = 0; i < mat->tamx; i++) {
        for (int j = 0; j < mat->tamy; j++) {
            s += mat->m[i][j];
        }
    }
    return s;
}

void imprimeMatriz(mat_tipo * mat) {
    erroAssert(mat->tamx <= MAXTAM, "Dimensao maior que permitido");
    erroAssert(mat->tamy <= MAXTAM, "Dimensao maior que permitido");

    printf("%9s", " ");
    for (int j = 0; j < mat->tamy; j++)
        printf("%8d ", j);
    printf("\n");

    for (int i = 0; i < mat->tamx; i++) {
        printf("%8d ", i);
        for (int j = 0; j < mat->tamy; j++) {
            printf("%8.2f ", mat->m[i][j]);
        }
        printf("\n");
    }
}

void salvaMatriz(mat_tipo * mat, FILE * out) {
    fprintf(out, "%d %d\n", mat->tamx, mat->tamy);
    for (int i = 0; i < mat->tamx; i++) {
        for (int j = 0; j < mat->tamy; j++) {
            fprintf(out, "%.6f ", mat->m[i][j]);
        }
        fprintf(out, "\n");
    }
}

void escreveElemento(mat_tipo * mat, int x, int y, double v) {
    erroAssert((x >= 0) && (x < mat->tamx), "Indice invalido");
    erroAssert((y >= 0) && (y < mat->tamy), "Indice invalido");
    mat->m[x][y] = v;
}

double leElemento(mat_tipo * mat, int x, int y) {
    erroAssert((x >= 0) && (x < mat->tamx), "Indice invalido");
    erroAssert((y >= 0) && (y < mat->tamy), "Indice invalido");
    return mat->m[x][y];
}

void copiaMatriz(mat_tipo *src, mat_tipo * dst, int dst_id) {
    criaMatriz(dst, src->tamx, src->tamy, dst_id);
    inicializaMatrizNula(dst);
    for (int i = 0; i < src->tamx; i++) {
        for (int j = 0; j < src->tamy; j++) {
            dst->m[i][j] = src->m[i][j];
        }
    }
}

void somaMatrizes(mat_tipo *a, mat_tipo *b, mat_tipo *c) {
    erroAssert(a->tamx == b->tamx, "Dimensoes incompativeis");
    erroAssert(a->tamy == b->tamy, "Dimensoes incompativeis");

    criaMatriz(c, a->tamx, a->tamy, c->id);
    inicializaMatrizNula(c);

    for (int i = 0; i < a->tamx; i++) {
        for (int j = 0; j < a->tamy; j++) {
            c->m[i][j] = a->m[i][j] + b->m[i][j];
        }
    }
}

void multiplicaMatrizes(mat_tipo *a, mat_tipo *b, mat_tipo *c) {
    erroAssert(a->tamy == b->tamx, "Dimensoes incompativeis");

    criaMatriz(c, a->tamx, b->tamy, c->id);
    inicializaMatrizNula(c);

    for (int i = 0; i < c->tamx; i++) {
        for (int j = 0; j < c->tamy; j++) {
            for (int k = 0; k < a->tamy; k++) {
                c->m[i][j] += a->m[i][k] * b->m[k][j];
            }
        }
    }
}

void transpoeMatriz(mat_tipo *a) {
    for (int i = 0; i < a->tamx; i++) {
        for (int j = i + 1; j < a->tamy; j++) {
            double temp = a->m[i][j];
            a->m[i][j] = a->m[j][i];
            a->m[j][i] = temp;
        }
    }
    int temp = a->tamx;
    a->tamx = a->tamy;
    a->tamy = temp;
}

void destroiMatriz(mat_tipo *a) {
    avisoAssert(((a->tamx > 0) && (a->tamy > 0)), "Matriz já foi destruida");
    a->id = a->tamx = a->tamy = -1;
}
