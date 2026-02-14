#include <iostream>
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll maxn = 2*1e5+5, INF = 4e18+9;
void solve(){
    ll k, n;
    cin >> k >> n;
    for(int i = 1; i < n; i++){
        cout << i << "\n";
        k-=i;
    }
    cout << k;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}

