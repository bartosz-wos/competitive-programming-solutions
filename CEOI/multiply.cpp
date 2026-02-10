#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 12000;
const int INF = 1e9;

int n, m, a[N], b[N], res[N];

void toArray(string &str, int a[]){
    reverse(str.begin(), str.end());
    int base = 1, cur = 0;
    for(char ch : str){
        a[cur] += (ch - '0') * base;
        base *= 10;
        if (base == 1e9){
            cur++;
            base = 1;
        }
    }
}

void readInput(){
    string sA, sB;
    cin >> m >> n;
    cin >> sA >> sB;
    toArray(sA, a);
    toArray(sB, b);
}

void solve(){
    m = (m + 8) / 9;
    n = (n + 8) / 9;
    int base = 1e9;

    for(int i = 0; i < m; i++){
        int carry = 0;
        for(int j = 0; j < n; j++){
            ll sum = carry + res[i + j] + (ll) a[i] * b[j];
            res[i + j] = sum % base;
            carry = sum / base;
        }
        res[i + n] = carry;
    }

    int sz = m + n;
    while (res[sz] == 0 && sz > 0)
        sz--;

    cout << res[sz];
    for(int i = sz - 1; i >= 0; i--)
        cout << setw(9) << setfill('0') << res[i];
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    readInput();
    solve();
    return 0;
}
