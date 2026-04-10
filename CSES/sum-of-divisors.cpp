#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int mod = 1e9+7;
constexpr int inv = 500000004;
 
ll sum(ll st, ll en) {
        return (en - st + 1) % mod * ((st + en) % mod) % mod * inv % mod;
}
 
ll n;
int main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        cin >> n;
        ll total = 0;
        ll at = 1;
        while(at <= n) {
                ll add_amt = n / at;
                ll last_same = n / add_amt;
                total = (total + add_amt * sum(at, last_same)) % mod;
                at = last_same + 1;
        }
        cout << total;
}
