#include <bits/stdc++.h>
using namespace std;
using ll=long long;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while(t--){
        ll n,m,k;
        cin >> n >> m >> k;
        ll n1 = n - 1, m1 = m - 1;
        ll period_r = 2*n1;
        ll period_c = 2*m1;
        ll kr = k % period_r;
        ll row = (kr <= n1 ? 1 + kr : 2*n - 1 - kr);
        ll kc = k % period_c;
        ll col = (kc <= m1 ? 1 + kc : 2*m - 1 - kc);
        ll hits_r = k / n1;
        ll hits_c = k / m1;
        ll g = std::gcd(n1, m1);
        ll l = (n1 / g) * m1;
        ll corner_hits = k / l;
        ll dir_changes = hits_r + hits_c - corner_hits;
 
        cout << row << " " << col << " " << dir_changes << "\n";
    }
}
