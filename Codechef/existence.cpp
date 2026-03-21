#include<bits/stdc++.h>
using namespace std;
using ll=long long;

void solve(){
    ll x,y;
    cin>>x>>y;
    if(x*x-2*y==0)
        cout<<"YES\n";
    else
        cout<<"NO\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t=1;
    cin>>t;
    while(t--)
        solve();
}
