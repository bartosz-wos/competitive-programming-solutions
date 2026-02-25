#include<bits/stdc++.h>
using namespace std;
using ll=long long;

ll f(ll a, ll b, ll c, ll n){
        if(!a)return (b/c)*(n+1ll);
        if(a>=c or b>=c)return n*(n+1ll)/2*(a/c)+(n+1ll)*(b/c)+f(a%c,b%c,c,n);
        ll x=a*n+b;
        x/=c;
        return x*n-f(c,c-b-1,a,x-1);
}

void solve(){
        ll n,m,a,b;
        cin>>n>>m>>a>>b;
        cout<<f(a,b,m,n-1)<<'\n';
}

int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        int t;
        cin>>t;
        while(t--)
                solve();
}
