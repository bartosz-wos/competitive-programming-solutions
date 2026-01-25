#include "bits/stdc++.h"
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;
using ll=long long;
constexpr ll INF = 1e18, mod = 1e9 + 7, N = 2e5 + 5;

void solve(){
    ll n,m;
    cin >> n;
    vector<pair<ll,ll>>v;
    v.push_back({0ll, 0ll});
    ll a,b;
    for(int i = 0; i < n; i++){
       cin >> a >> b;
       v.push_back({a,b});
    }
    sort(v.begin(),v.end());
    ll maxi = 0;
    ll cur = 0;
    for(int i = 1; i <= n; i++){
        cur += v[i].second;
        cur = max(cur, v[i].first + v[i].second);
        maxi = max(maxi, cur - v[i].first);
    }
    cout << maxi << endl;
}
int main() {
    fast;
    ll t = 1;
   // cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
