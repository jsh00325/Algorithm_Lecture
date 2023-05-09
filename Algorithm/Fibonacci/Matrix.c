#include "Matrix.h"

/** ���ο� ��� ����
 *  @param row ���� ����� ���� ��
 *  @param col ���� ����� ���� ��
 *  @return �����Ҵ�� ��� */
Matrix* MT_CreateMat(int row, int col) {
    Matrix* newMat = (Matrix*) malloc(sizeof(Matrix));
    newMat->row = row;
    newMat->column = col;
    newMat->arr = (ll**) malloc(sizeof(ll*) * row);
    for (int i = 0; i < row; i++)
        newMat->arr[i] = (ll*) malloc(sizeof(ll) * col);
    return newMat;
}

/** �� ����� ���ϴ� �Լ�
 *  @param a ���� ù��° ���
 *  @param b ���� �ι�° ���
 *  @param MOD ū ���� ��츦 ���� MOD������ �� ��
 *  @return a * b�� ��� (���� �� ������ NULL) */
Matrix* MT_MultiplyMat(Matrix* a, Matrix* b, ll MOD) {
    // �迭�� ���� �� ���� ���
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

/** ����� �����ϴ� �Լ�
 *  @param a ������ ���
 *  @param pow �� ��������
 *  @param MOD ū ���� ��츦 ���� MOD������ �� ��
 *  @return a^pow�� ��� */
Matrix* MT_PowerMat(Matrix* a, int pow, ll MOD) {
    
}

/** ��� ���
 *  @param m ����� ��� */
void MT_PrintMat(Matrix* m) {
    for (int i = 0; i < m->row; i++) {
        for (int j = 0; j < m->column; j++) 
            printf("%7ld ", m->arr[i][j]);
        printf("\n");
    } printf("\n");
}
