#include <bits/stdc++.h>
using namespace std;
using ll=long long;

void solve(){
    ll n, k; cin >> n >> k;
    vector<ll>a(n), h(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    for (ll i = 0; i < n; i++) cin >> h[i];
    ll t = 0, br = LLONG_MAX;
    for (ll i = 0; i < n; i++){
        ll tt = t + h[i];
        if (tt > a[i]){
            br = i; break;
        }
        t = tt;
    }
    if (br == LLONG_MAX) {
        cout << "YES\n"; return;
    }
    ll s = 0, i = 0, x = 2*k+1;
    for (; i < n; i++){
        if (a[i] <= x) s += h[i];
        else break;
    }
    ll l = 0;
    ll maxs = s, maxsl = 1;
    for (; i < n  && l <= i; i++){
        s += h[i];
        while(a[l] < a[i] - (2*k) ){
            s -= h[l];
            l++;
        }
        if (l > br) break;
        if (s > maxs){
            maxs = s;
            maxsl = a[i] - (2*k);
        }
    }
    ll tn = 0;    
    for (ll i = 0; i < n; i++){
        if(a[i] >= maxsl && a[i] <= maxsl+2*k) continue;
        ll tt = tn + h[i];
        if (tt > a[i]){
            cout << "NO\n"; return;
        }
        tn = tt;
    }
    cout << "YES\n";
}

int main(){
	int t;
	cin >>t;
	while(t--)
	    solve();
}
