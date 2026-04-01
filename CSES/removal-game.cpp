#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int n;
int tab[5007];
ll dp[5007][5007], sum;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n;
    for(int i = 0; i < n; ++i)
        cin >> tab[i], sum += tab[i];
 
    for(int l = n - 1; l >= 0; --l)
        for(int r = l; r < n; ++r) {
            if(l == r)
                dp[l][r] = tab[l];
            else
                dp[l][r] = max( tab[l] - dp[l+1][r], tab[r] - dp[l][r-1] );
            }
    cout << ((sum + dp[0][n-1]) >> 1);
}
