#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll n;
    cin>>n;
    ll s,t;
    s=t=-1;
    for(ll i=n;i<=n+100;++i)
        if(i%100==99){
            t=i;
            break;
        }
    for(ll i=n;i>=n-100 and i>=99;--i)
        if(i%100==99){
            s=i;
            break;
        }
    if(s==-1)cout<<t<<'\n';
    else if(n-s==t-n)cout<<t<<'\n';
    else if(n-s<t-n)cout<<s<<'\n';
    else cout<<t<<'\n';
}
