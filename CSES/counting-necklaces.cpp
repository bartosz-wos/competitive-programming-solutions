#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int mod = 1e9+7;
 
ll gcd(ll a, ll b) {
    return !b ? a : gcd(b, a % b);
}
 
ll exp(ll a, ll w) {
    ll res = 1;
    while(w) {
        if(w & 1)
            res = res * a % mod;
        a = a * a % mod;
        w >>= 1;
    }
    return res;
}
 
ll n, m, ans;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    for(int i = 0; i < n; ++i)
        ans = (ans + exp(m, gcd(i, n))) % mod;
    
    ans = ans * exp(n, mod - 2) % mod;
    cout << ans;
}
