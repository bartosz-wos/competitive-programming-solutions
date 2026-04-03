#include<bits/stdc++.h>
using namespace std;
constexpr int MAXN = 2e5 + 7;
int anc[MAXN][31], n, q, p, a, b;
 
int query(int& a, int& k) {
    int j = 0;
    while(k) {
        if(k & 1)
            a = anc[a][j];
        ++j;
        k >>= 1;
    }
    return a;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> q;
    for(int i = 1; i <= n; ++i)
        cin >> p, anc[i][0] = p;
 
    for(int i = 1; i <= 30; ++i)
        for(int j = 1; j <= n; ++j)
            anc[j][i] = anc[anc[j][i-1]][i-1];
 
    while(q--) {
        cin >> a >> b;
        cout << query(a, b) << '\n';
    }
}
