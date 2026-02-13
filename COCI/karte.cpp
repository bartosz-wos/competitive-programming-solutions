#include <bits/stdc++.h>
using namespace std;
#define MAXN 500005
#define ll long long
#define FOR(i, a, b) for(ll i = a; i <= b; i++)

ll n, k, c[MAXN];

int main(){
    cin >> n >> k;
    FOR(i, 1, n) cin >> c[i];
    sort(c + 1, c + 1 + n);
    
    for(ll i = k; i >= 1; i--){
        if(c[n - (k - i)] < i){
            cout << -1 << endl;
            return 0;
        }
    }
    if(n - k >= 1 && c[n - k] > k) {
        cout << -1 << endl;
        return 0;
    }

    FOR(i, k + 1, n) cout << c[n - (i - 1)] << " ";
    for(ll i = k; i >= 1; i--) cout << c[n - (k - i)] << " ";
    cout << endl;
}
