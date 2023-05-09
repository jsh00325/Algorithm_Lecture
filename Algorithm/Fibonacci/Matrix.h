#ifndef MY_MATRIX_H
#define MY_MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;
typedef struct {
    int row;
    int column;
    ll** arr;
} Matrix;

Matrix* MT_CreateMat(int r, int c);
Matrix* MT_MultiplyMat(Matrix* a, Matrix* b, ll MOD);
Matrix* MT_PowerMat(Matrix* a, int pow, ll MOD);
void MT_PrintMat(Matrix* m);

#endif