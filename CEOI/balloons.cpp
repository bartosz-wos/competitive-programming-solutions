#include<bits/stdc++.h>
using namespace std;
using ll=long long;

void solve(){
    ll x;
    cin>>x;
    pair<ll, ll> arr[x];
    long double ans[x];
    for(int i=0; i<x; i++)
        cin>>arr[i].first>>arr[i].second;
        stack<pair<ll, long double>>s;
        for(ll i=0; i<x; i++){
            long double r=arr[i].second;
            while(!s.empty()){
            r=min(r, (arr[i].first-s.top().first)*(arr[i].first-s.top().first)/(4LL*s.top().second));
            if(r>=s.top().second) s.pop();
            else break;
        }
        ans[i]=r;
        s.push({arr[i].first, ans[i]});
        }
    for(int i=0; i<x; i++) cout<<fixed<<setprecision(3)<<ans[i]<<'\n';
}
     
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t=1;
    while(t--) 
        solve();
}
