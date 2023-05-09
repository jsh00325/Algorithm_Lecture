#include "Matrix.h"

/** 새로운 행렬 생성
 *  @param row 만들 행렬의 행의 수
 *  @param col 만들 행렬의 열의 수
 *  @return 동적할당된 행렬 */
Matrix* MT_CreateMat(int row, int col) {
    Matrix* newMat = (Matrix*) malloc(sizeof(Matrix));
    newMat->row = row;
    newMat->column = col;
    newMat->arr = (ll**) malloc(sizeof(ll*) * row);
    for (int i = 0; i < row; i++)
        newMat->arr[i] = (ll*) malloc(sizeof(ll) * col);
    return newMat;
}

/** 두 행렬을 곱하는 함수
 *  @param a 곱할 첫번째 행렬
 *  @param b 곱할 두번째 행렬
 *  @param MOD 큰 값의 경우를 위해 MOD연산을 할 값
 *  @return a * b의 결과 (곱할 수 없으면 NULL) */
Matrix* MT_MultiplyMat(Matrix* a, Matrix* b, ll MOD) {
    // 배열을 곱할 수 없는 경우
    if (a->column != b->row) return NULL;

    Matrix* rslt = MT_CreateMat(a->row, b->column);
    for (int i = 0; i < rslt->row; i++)
        memset(rslt->arr[i], 0, sizeof(ll) * rslt->column);

    for (int i = 0; i < rslt->row; i++)
        for (int j = 0; j < rslt->column; j++)
            for (int k = 0; k < a->column; k++)
                rslt->arr[i][j] = (rslt->arr[i][j] + (a->arr[i][k] * b->arr[k][j]) % MOD) % MOD;
    return rslt;
}

/** 행렬을 제곱하는 함수
 *  @param a 제곱할 행렬
 *  @param pow 몇 제곱인지
 *  @param MOD 큰 값의 경우를 위해 MOD연산을 할 값
 *  @return a^pow의 결과 */
Matrix* MT_PowerMat(Matrix* a, int pow, ll MOD) {
    
}

/** 행렬 출력
 *  @param m 출력할 행렬 */
void MT_PrintMat(Matrix* m) {
    for (int i = 0; i < m->row; i++) {
        for (int j = 0; j < m->column; j++) 
            printf("%7ld ", m->arr[i][j]);
        printf("\n");
    } printf("\n");
}
