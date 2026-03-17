#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pi=pair<ll,ll>;

#define sz(x) (x).size()
#define al(x) (x).begin(),(x).end()
#define fi first
#define se second

void solve(){
        int n;
        cin>>n;
        vector<ll>a(n),b(n);
        for(int i=0;i<n;++i)cin>>a[i];
        ll ret=0;
        for(int i=0;i<n-1;++i){
                ret+=abs(a[i]);
                a[i+1]+=a[i];
                a[i]=0;
        }
        cout<<ret<<'\n';
}


int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        int tc;
        cin>>tc;
        while(tc--)
                solve();
}

