#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
ll arr[15];
 
ll gcd(ll a, ll b){
    if(!b)return a;
    return gcd(b,a%b);
}
 
ll lcm(ll a, ll b){
    return a/gcd(a,b)*b;
}
 
ll solve(ll n, ll k){
    ll multi=0;
    for(int mask=0;mask<(1ll<<k);++mask){
        ll mult=1;
        bool ok=1;
        for(int i=0;i<k;++i){
            if((1ll<<i)&mask){
                mult=lcm(mult,arr[i]);
                if(mult>n){
                    ok=0;
                    break;
                }
            }
            if(!ok)continue;
            ll num=n/mult;
            if(__builtin_popcount(mask)&1)
                multi-=num;
            else
                multi+=num;
        }
    }
    return multi;
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll n,k;
    cin>>n>>k;
    for(int i=0;i<k;++i)
        cin>>arr[i];
    cout<<solve(n,k)<<'\n';
}
