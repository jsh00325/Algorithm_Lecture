#include "Matrix.h"
#include "Fibonacci.h"
#include <time.h>

const ll MOD = 0x7fffffff;

void recursion(int n) {
    clock_t start = clock();
    ll rslt = FBNC_recursion(n, MOD);
    clock_t end = clock();
    printf("[    재귀   ] %10ld (%.3fs)\n", rslt, (double)(end - start) / CLOCKS_PER_SEC);
}
void dynamic_programming(int n) {
    clock_t start = clock();
    ll rslt = FBNC_Dynamic_Programming(n, MOD);
    clock_t end = clock();
    printf("[동적 계획법] %10ld (%.3fs)\n", rslt, (double)(end - start) / CLOCKS_PER_SEC);
}
void matrix_exponentiation(int n) {
    clock_t start = clock();
    ll rslt = FBNC_Matrix_Exponentiation(n, MOD);
    clock_t end = clock();
    printf("[ 행렬 제곱 ] %10ld (%.3fs)\n", rslt, (double)(end - start) / CLOCKS_PER_SEC);
}

int main() {
    int n;
    printf("몇번째 피보나치 수? : ");
    scanf("%d", &n);

    printf("\n[%d번째 피보나치 수] (%ld의 나머지...)\n", n, MOD);
    recursion(n);
    dynamic_programming(n);
    matrix_exponentiation(n);
}