#include <bits/stdc++.h>

#include "boxes.h"

using namespace std;

long long delivery(int N, int K, int L, int p[]) {
    long long ans = 1e18;
    vector<long long> pref(N, 0);
    vector<long long> suf(N, 0);
    for(int i = 0; i < N; i++) {
        if(i >= K) {
            pref[i] = pref[i - K];
        }
        pref[i] += min(L, p[i] * 2);
    }
    for(int i = N - 1; i >= 0; i--) {
        if(i + K < N) {
            suf[i] = suf[i + K];
        }
        suf[i] += min(L,(L - p[i]) * 2);
    }
    ans = min(suf[0], pref[N - 1]);
    for(int i = 0; i < N - 1; i++) {
        ans = min(ans, pref[i] + suf[i + 1]);
    }
    return ans;
}
