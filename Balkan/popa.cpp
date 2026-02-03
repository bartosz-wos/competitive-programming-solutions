#include <bits/stdc++.h>
#include "popa.h"
using namespace std;

int st[1005];

int solve(int N, int* L, int* R) {
    int root = -1;

    for (int i = 0; i < N; i++)
        L[i] = R[i] = -1;
    int idx = 0;

    for (int i = 0; i < N; i++) {
        while (idx && query(st[idx], i, i, i)) {
            R[st[idx]] = L[i];
            L[i] = st[idx];
            idx--;
        }

        if (!idx) root = i;
            else R[st[idx]] = i;
        st[++idx] = i;
    }

    return root;
}
