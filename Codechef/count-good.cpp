#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fast                       \
 ios_base::sync_with_stdio(0);      \
 cin.tie(0);                         \
 cout.tie(0);

int main(){
    fast;
    ll t;
    cin>>t;
    while(t--){
        ll n,k,q;
        cin>>n>>k>>q;
        ll n1=k,n2=n+k-1;
        ll xx=0;
        for(ll i=61;i>=0;i--){
            if((n2&(1LL<<i))==((n1&(1LL<<i)))){
                if((n1&(1LL<<i))>0){
                    xx+=(1LL<<i);
                    n1-=(1LL<<i);
                    n2-=(1LL<<i);
                }
            }
            else break;
        }
        vector<pair<ll,ll>> v1,v;
        v1.push_back({n1,n2});
        ll x=0,y=0;
        if(n2>0) x=1LL<<(__lg(n2));
        if(n2>x) y=1LL<<(__lg(n2-x));
        v1.push_back({x,x+2*y-1});
        v1.push_back({x+n1,2*x-1});
        sort(v1.begin(),v1.end());
        for(ll i=0;i<(ll)v1.size();i++){
            v1[i].first+=xx;
            v1[i].second+=xx;
        }
        for(ll i=0;i<(ll)v1.size();i++){
            if((ll)v.size()==0) v.push_back({v1[i].first,v1[i].second});
            else{
                if(v1[i].first<=v.back().second){
                    ll x=v.back().first,y=v.back().second;
                    v.pop_back();
                    x=min(x,v1[i].first);
                    y=max(y,v1[i].second);
                    v.push_back({x,y});
                }
                else v.push_back({v1[i].first,v1[i].second});
            }
        }
        while(q--){
            ll l,r;
            cin>>l>>r;
            ll ans=0;
            for(ll i=0;i<(ll)v.size();i++){
                ll x=v[i].first,y=v[i].second;
                if(l>=x && l<=y){
                    ans+=(min(r,y)-l+1);
                }
                else if(r>=x && r<=y){
                    ans+=(r-max(l,x)+1);
                }
                else if(l<=x && y<=r){
                    ans+=(y-x+1);
                }
            }
            cout<<ans<<"\n";
        }
    }
}
