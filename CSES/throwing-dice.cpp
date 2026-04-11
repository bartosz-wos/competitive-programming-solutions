#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int mod =1e9+7;
vector<vector<ll>> M(6, vector<ll>(6, 0));
 
vector<vector<ll>> mul(vector<vector<ll>>& a, vector<vector<ll>>& b) {
        vector<vector<ll>> res(6, vector<ll>(6, 0));
        for(int i = 0; i < 6; ++i)
                for(int j = 0; j < 6; ++j)
                        for(int k = 0; k < 6; ++k)
                                res[i][j] = (res[i][j] + a[i][k] * b[k][j] % mod) % mod;
        return res;
}
 
vector<vector<ll>> exp(vector<vector<ll>>& a, ll k) {
        vector<vector<ll>> res(6, vector<ll>(6, 0));
        for(int i = 0; i < 6; ++i)
                res[i][i] = 1;
        while(k) {
                if(k & 1)
                        res = mul(res, a);
                a = mul(a, a);
                k >>= 1;
        }
        return res;
}
 
ll n;
int main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        cin >> n;
        for(int i = 0; i < 5; ++i)
                M[i][i+1] = 1, M[5][i] = 1;
        M[5][5] = 1;
        cout << exp(M, n)[5][5];
}
