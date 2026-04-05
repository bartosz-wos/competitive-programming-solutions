#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int poz = 19;
constexpr int u = 1 << (poz - 1);
constexpr int inf = 2e9;
 
int T[u << 1];
 
void act(int index, int value) {
    index += u;
    T[index] = value;
    index >>= 1;
    while(index) {
        T[index] = min( T[index << 1], T[(index << 1) + 1] );
        index >>= 1;
    }
}
 
int query(int a, int b) {
    int ans = 2e9;
    a += u - 2;
    b += u;
    while(b - a > 1) {
        if(!(a & 1))
            ans = min(ans, T[a+1]);
        if(b & 1)
            ans = min(ans, T[b-1]);
        a >>= 1;
        b >>= 1;
    }
    return ans;
}
int n, q, p, a, b;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> q;
    for(int i = 0; i < n; ++i)
        cin >> T[u+i];
    for(int i = u - 1; i > 0; --i)
        T[i] = min(T[i << 1], T[(i << 1) + 1]);
 
    while(q--) {
        cin >> p >> a >> b;
        if(p == 1)
            act(a-1, b);
        else
            cout << query(a, b) << '\n';
    }
}
