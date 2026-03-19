#include <bits/stdc++.h>
using namespace std;
using ll=long long;

bool prime(ll x){
    if(x<=1)return 0;
    if(x==2)return 1;
    for(ll i=2;i*i<=x;++i)
        if(x%i==0)return 0;
    return 1;
}

bool sq(ll x){
    ll p=(ll)sqrt(x);
    if(p*p==x)return 1;
    return 0;
}

void solve(){
    ll x;
    cin>>x;
    ll p1,p2;
    p1=p2=-1;
    for(ll i=x;;++i){
        if(prime(i)){
            if(p1==-1)p1=i;
            else if(p2==-1)p2=i;
            else break;
        }
    }
    cout<<p1*p2<<'\n';
}

int main() {
    int t=1;
    cin>>t;
    while(t--)solve();
}

