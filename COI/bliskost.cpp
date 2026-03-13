#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define FORI(i, n) for(ll i = 0; i < n; i++)
#define FOR(i, n) for(ll i = 1; i <= n; i++)
typedef vector < ll > vl; 
typedef set < ll > setl;
#define ff first
#define ss second    
#define all(v) v.begin(), v.end() 
#define pll pair<ll, ll> 
#define db double
#define nll cout << "\n"
#define nl "\n"
#define sync ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

const ll mod =  1e9 + 7;
const int MAX = 3e5 + 5;
const int imax = 2147483647;
ll n, m, k, q, l, r, x, y, res, nd;
ll a[MAX], b[MAX], used[MAX];
void solve(){
    cin >> n >> q;
    string s, t;
    cin >> s >> t;
    ll sum = 0;
    FORI(i, n){
        sum = (t[i] - s[i] - sum + 26) % 26;
    }
    ll ind;
    char c;
    cout << (sum ? "ne" : "da") << nl;
    while(q--){
        cin >> ind >> c;
        ind--;
        ll dif = c - s[ind];
        s[ind] = c;
        sum = (sum + 26 - (((n - ind) & 1) ? dif : -dif)) % 26;
        if(sum)cout << "ne";
        else cout << "da";
        nll;
    }
}
signed main(){      
    sync;
    ll t = 1;
    FOR(i, t){
        solve();
    }
}
