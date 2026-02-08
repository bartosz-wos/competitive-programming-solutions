#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define pb push_back
#define ff first
#define ss second
#define all(s) s.begin(),s.end()
#define rall(s) s.rbegin(),s.rend()

const ll N=5e5+5;

ll n,c[N],b[N],l[N],r[N],last[N],p[N],q[N];
vector<ll>key[N];

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin>>n;
    for(ll i=1;i<n;i++){
        cin>>c[i];
    }
    for(ll i=1;i<=n;i++){
        cin>>b[i];
        key[i].resize(b[i]);
        for(auto &k:key[i]){
            cin>>k;
        }
    }
    fill(last,last+n+1,0);
    //left closest position
    for(ll i=1;i<n;i++){
        for(ll k:key[i]){
            last[k]=i;
        }
        p[i]=last[c[i]];
    }
    fill(last,last+n+1,n+1);
    //right closest position
    for(ll i=n;i>=2;i--){
        for(ll k:key[i]){
            last[k]=i;
        }
        q[i]=last[c[i-1]];
    }
    for(ll i=1;i<=n;i++){
        l[i]=i;
        r[i]=i;
        while(true){
            if(l[i]>1&&q[l[i]]<=r[i]){//can move to left
                l[i]--;
                if(r[l[i]]>=i){
                    r[i]=r[l[i]];
                    l[i]=l[l[i]];
                    break;
                }
            }
            else if(r[i]<n&&p[r[i]]>=l[i]){
                r[i]++;
            }
            else{
                break;
            }
        }
    }
    ll q;
    cin>>q;
    while(q--){
        ll x,y;
        cin>>x>>y;
        if(l[x]<=y&&y<=r[x]){
            cout<<"YES\n";
        }
        else{
            cout<<"NO\n";
        }
    }
}
