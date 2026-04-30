#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1e9+7;
 
int add(int a,int b){ a+=b; if(a>=MOD) a-=MOD; return a; }
int sub(int a,int b){ a-=b; if(a<0) a+=MOD; return a; }
int mul(ll a,ll b){ return int((a*b)%MOD); }
int modexp(int b,ll e=MOD-2){
    ll r=1, x=b;
    while(e){
        if(e&1) r=(r*x)%MOD;
        x=(x*x)%MOD;
        e>>=1;
    }
    return int(r);
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n;
    cin >> n;
    vector<int> freq(n+1,0);
    for(int i=0;i<n;i++){
        int x; 
        cin >> x;
        ++freq[x];
    }
 
    vector<int> pw2(n+1,1);
    for(int i=1;i<=n;i++)
        pw2[i] = add(pw2[i-1], pw2[i-1]);
 
    vector<int> f(n+1,0);
    for(int d=1;d<=n;d++){
        for(int m=d;m<=n;m+=d)
            f[d] += freq[m];
    }
 
    vector<int> F(n+1,0);
    for(int d=1;d<=n;d++){
        if(f[d]==0) F[d] = 0;
        else         F[d] = sub(pw2[f[d]], 1);
    }
 
    vector<int> g(n+1,0);
    for(int d=n; d>=1; d--){
        ll v = F[d];
        for(int m=2*d; m<=n; m+=d){
            v = (v - g[m] + MOD);
        }
        g[d] = int(v % MOD);
    }
 
    for(int d=1; d<=n; d++){
        cout << g[d] << (d==n?'\n':' ');
    }
    return 0;
}
