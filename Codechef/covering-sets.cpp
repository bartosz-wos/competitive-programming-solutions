#include<bits/stdc++.h>
using namespace std;

const int N = 2e6 + 10, MOD = 1000000007;

typedef long long ll;

ll F[N],A[N],B[N], C[N], pow_2[25],n, m, res;

int getCnt(int x)
{
    int tem = 0;
    while (x > 0) {
        if (x & 1) tem++;
        x = x >> 1;
    }

    return tem;
}
int count_of_one(int x) {
    int ret = 0;
    while (x) {
        if (x & 1) {
            ret++;
        }
        x >>= 1;
    }
    return ret;
}
int main()
{
    cin >> n;
    m = 1 << n;
    pow_2[0] = 1ll;
    for (int i = 1; i <= 20; i++) {
        pow_2[i] = pow_2[i - 1] * 2 % MOD;
    }
    for (int i = 0; i < m; i++) cin >> A[i];
    for (int i = 0; i < m; i++) cin >> B[i];
    for (int i = 0; i < m; i++) cin >> C[i];
    for (int i = 0; i <= 20; i++) {
        for (int j = 0; j < 1 << 20; j++) {
            if (j >> i & 1) {
                A[j] = (A[j] + A[j - (1 << i)]) % MOD;
                B[j] = (B[j] + B[j - (1 << i)]) % MOD;
                C[j] = (C[j] + C[j - (1 << i)]) % MOD;
            }
        }
    }
    for (int i = 0; i < 1 << 20; i++) {
        F[i] = A[i] * B[i] % MOD * C[i] % MOD;
    }

    for (int i = 20; i >= 0; i--) {
        for (int j = 0; j < 1 << 20; j++) {
            if (j >> i & 1) {
                F[j] = (F[j] - F[j - (1 << i)] + MOD) % MOD;
            }
        }
    }
    res = 0;
    for (int i = 0; i < m; i++) {
        res = (res + F[i] * pow_2[count_of_one(i)]) % MOD;
    }
    cout << res << endl;

    return 0;
}
