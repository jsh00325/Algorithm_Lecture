#include "Fibonacci.h"

/** n번째 피보나치 수를 재귀를 이용하여 구하는 함수
 *  @details O(2^N)의 시간복잡도를 가짐
 *  @param n 구하고자 하는 피보나치 수의 순서
 *  @param MOD 큰 값의 경우를 위해 MOD연산을 할 값
 *  @return n번째 피보나치수를 MOD로 나눈 나머지 */
ll FBNC_recursion(int n, ll MOD) {
    if (n <= 1) return n;
    else return (FBNC_recursion(n-1, MOD) + FBNC_recursion(n-2, MOD)) % MOD;
}

/** n번째 피보나치 수를 DP를 이용하여 구하는 함수
 *  @details O(N)의 시간복잡도를 가짐
 *  @param n 구하고자 하는 피보나치 수의 순서
 *  @param MOD 큰 값의 경우를 위해 MOD연산을 할 값
 *  @return n번째 피보나치수를 MOD로 나눈 나머지 */
ll FBNC_Dynamic_Programming(int n, ll MOD) {
    ll* dp = (ll*) malloc(sizeof(ll) * (n+1));
    dp[0] = 0; dp[1] = 1;
    for (ll i = 2; i <= n; i++)
        dp[i] = (dp[i-1] + dp[i-2]) % MOD;
    ll rslt = dp[n];
    free(dp);
    return rslt;
}

/** n번째 피보나치 수를 행렬의 거듭제곱을 이용하여 구하는 함수
 *  @details O(lgN)의 시간복잡도를 가짐
 *  @param n 구하고자 하는 피보나치 수의 순서
 *  @param MOD 큰 값의 경우를 위해 MOD연산을 할 값
 *  @return n번째 피보나치수를 MOD로 나눈 나머지 */
ll FBNC_Matrix_Exponentiation(int n, ll MOD) {
    Matrix* base = MT_CreateMat(2, 2);
    Matrix* rslt = MT_CreateMat(2, 2);
    Matrix* end = MT_CreateMat(2, 1);
    base->arr[0][0] = base->arr[0][1] = base->arr[1][0] = 1; base->arr[1][1] = 0;
    rslt->arr[0][0] = rslt->arr[1][1] = 1; rslt->arr[0][1] = rslt->arr[1][0] = 0;
    end->arr[0][0] = 1; end->arr[1][0] = 0;
    while (n > 0) {
        if (n & 1) {
            Matrix* temp = rslt;
            rslt = MT_MultiplyMat(temp, base, MOD);
            free(temp);
        }
        Matrix* temp = base;
        base = MT_MultiplyMat(temp, temp, MOD);
        free(temp);
        n >>= 1;
    }
    Matrix* temp = rslt;
    rslt = MT_MultiplyMat(temp, end, MOD);
    free(temp);

    ll answer = rslt->arr[1][0];
    free(base); free(rslt); free(end);
    return answer;
}
