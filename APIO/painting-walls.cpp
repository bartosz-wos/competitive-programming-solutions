#include "paint.h"
#include <bits/stdc++.h>
using namespace std;

const int N = 100'000;
const int M = 17;
const int INF = 1'000'000'000;

int n, m, k, c[N + 10], good[N + 10];
int dp[2][N + 10], ans[N + 10], rmq[N + 10][M + 3];
vector<int> pack[N + 10];

void readInput(int N, int M, int K, vector<int> C, vector<int> A, vector<vector<int>> B) {
    n = N;
    m = M;
    k = K;
    for (int i = 0; i < n; i++)
        c[i] = C[i];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < A[i]; j++)
            pack[B[i][j]].push_back(i);
    //cout << "size Pack " << pack[0].size() << ' ' << pack[1].size() << ' ' << pack[2].size() << endl;
}

void delDP(int idx) {
    if (idx > n)
        return;
    for (auto x: pack[c[idx]])
        dp[idx % 2][x] = 0;
}

void calcGood() {
    for (int i = n - 1; i >= 0; i--) {
        int t = i % 2;
        delDP(i + 2);
        for (auto x: pack[c[i]]) {
            dp[t][x] = dp[t ^ 1][(x + 1) % m] + 1;
            good[i] |= (dp[t][x] >= m);
            //cout << i << ' ' << c[i] << ", " << x << " -> " << dp[t][x] << endl;
        }
        //cout << i << ": " << good[i] << endl;
    }
}

void updateRMQ(int i) {
    rmq[i][0] = ans[i];
    for (int j = 1; j <= M; j++)
        if (i + (1 << j) <= n)
            rmq[i][j] = min(rmq[i][j - 1], rmq[i + (1 << (j - 1))][j - 1]);
}

int get(int l, int r) {
    int lg = 31 - __builtin_clz(r - l + 1);
    return min(rmq[l][lg], rmq[r - (1 << lg) + 1][lg]);
}

void calcAns() {
    for (int i = n - 1; i > n - m; i--) {
        ans[i] = INF;
        updateRMQ(i);
    }
    for (int i = n - m; i >= 0; i--) {
        if (good[i])
            ans[i] = min(INF, get(i + 1, i + m) + 1);
        else
            ans[i] = INF;
        updateRMQ(i);
    }
}

int minimumInstructions(int N, int M, int K, vector<int> C, vector<int> A, vector<vector<int>> B) {
    readInput(N, M, K, C, A, B);
    calcGood();
    calcAns();
    return (ans[0] == INF? -1: ans[0]);
}
