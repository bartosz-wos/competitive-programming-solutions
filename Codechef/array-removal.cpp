#include <bits/stdc++.h>
using namespace std;
using ll=long long;

void solve(){
    int n;
    cin>>n;
    vector<ll>a(n);
    ll mx=0;
    for(ll&i:a){
        cin>>i;
        mx=max(mx,i);
    }
    ll ret=1e18;
    for(ll need=0;need<=5ll*mx;++need,need<<=1,--need){
        ll cur=0;
        ll s=0;
        for(const ll&i:a){
            bool ok=0;
            for(int b=0;b<=30;++b)
                if(i>need){
                    ++cur;
                    ok=1;
                    break;
                }
            if(!ok)s|=i;
        }
        if(s==need)ret=min(ret,cur);
    }
    cout<<ret<<'\n';
}

int main() {
    int t=1;
    cin>>t;
    while(t--)solve();
}

