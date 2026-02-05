#include <bits/stdc++.h>
using namespace std;

#define dbg(x) cerr << #x << ": " << x << endl;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int m;
    cin >> m;
    int n = 1 << m;
    int max_mask = n - 1;
    vector<int> s(n);
    vector<uint64_t> xor_hash(n);
    mt19937_64 rng(1233);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        if (x & (1 << (m - 1))) x ^= max_mask;
        s[i] = x;
        xor_hash[i] = rng();
    }
    long long ans = 1LL * n * (n + 1) / 2 - (m == 1);
    vector<unordered_map<uint64_t, int>> pos(4);
    ++pos[3][0];
    uint64_t pref = 0;
    for (int i = 0; i < n; ++i) {
        pref ^= xor_hash[s[i]];
        ans -= pos[i % 4][pref];
        ++pos[i % 4][pref];
    }
    cout << ans << '\n';
    return 0;
}
