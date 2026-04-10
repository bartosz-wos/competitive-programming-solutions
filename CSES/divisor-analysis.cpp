#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int mod = 1e9+7;
 
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
 
int n;
ll p[100007], k[100007];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n;
    for(int i = 0; i < n; ++i)
        cin >> p[i] >> k[i];
 
    ll div_cnt = 1, div_sum = 1, div_prod = 1, div_cnt2 = 1;
    for(int i = 0; i < n; ++i) {
        div_cnt = div_cnt * (k[i] + 1) % mod;
        div_sum = div_sum * ( exp(p[i], k[i] + 1) - 1) % mod * exp(p[i] - 1, mod - 2) % mod;
        div_prod = exp(div_prod, k[i] + 1) * exp( exp(p[i], k[i] * (k[i] + 1) >> 1), div_cnt2 ) % mod;
        div_cnt2 = div_cnt2 * (k[i] + 1) % (mod - 1);
    }
    cout << div_cnt << ' ' << div_sum << ' ' << div_prod;
}
