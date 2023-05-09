#include "Fibonacci.h"

/** n��° �Ǻ���ġ ���� ��͸� �̿��Ͽ� ���ϴ� �Լ�
 *  @details O(2^N)�� �ð����⵵�� ����
 *  @param n ���ϰ��� �ϴ� �Ǻ���ġ ���� ����
 *  @param MOD ū ���� ��츦 ���� MOD������ �� ��
 *  @return n��° �Ǻ���ġ���� MOD�� ���� ������ */
ll FBNC_recursion(int n, ll MOD) {
    if (n <= 1) return n;
    else return (FBNC_recursion(n-1, MOD) + FBNC_recursion(n-2, MOD)) % MOD;
}

/** n��° �Ǻ���ġ ���� DP�� �̿��Ͽ� ���ϴ� �Լ�
 *  @details O(N)�� �ð����⵵�� ����
 *  @param n ���ϰ��� �ϴ� �Ǻ���ġ ���� ����
 *  @param MOD ū ���� ��츦 ���� MOD������ �� ��
 *  @return n��° �Ǻ���ġ���� MOD�� ���� ������ */
ll FBNC_Dynamic_Programming(int n, ll MOD) {
    ll* dp = (ll*) malloc(sizeof(ll) * (n+1));
    dp[0] = 0; dp[1] = 1;
    for (ll i = 2; i <= n; i++)
        dp[i] = (dp[i-1] + dp[i-2]) % MOD;
    ll rslt = dp[n];
    free(dp);
    return rslt;
}

/** n��° �Ǻ���ġ ���� ����� �ŵ������� �̿��Ͽ� ���ϴ� �Լ�
 *  @details O(lgN)�� �ð����⵵�� ����
 *  @param n ���ϰ��� �ϴ� �Ǻ���ġ ���� ����
 *  @param MOD ū ���� ��츦 ���� MOD������ �� ��
 *  @return n��° �Ǻ���ġ���� MOD�� ���� ������ */
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
