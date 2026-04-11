#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int mod = 1e9+7;
ll fact[2000007];
int n;
 
ll exp(ll a, ll w) {
    ll ans = 1;
    while(w) {
        if(w & 1)
            ans = ans * a % mod;
        a = a * a % mod;
        w >>= 1;
    }
    return ans;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    fact[0] = 1;
    cin >> n;
    if(n & 1) {
        cout << 0;
        exit(0);
    }
    n >>= 1;
    for(int i = 1; i <= n << 1; ++i)
        fact[i] = fact[i-1] * i % mod;
 
    cout << fact[n << 1] * exp(fact[n], mod - 2) % mod * exp(fact[n], mod - 2) % mod * exp(n + 1, mod - 2) % mod;
}
