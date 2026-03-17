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
        vector<int>a(n);
        for(int&i:a)cin>>i;
        int cur=a[0];
        sort(a.begin(),a.end());
        int pos=-1;
        for(int i=0;i<n;++i)
                if(a[i]==cur)
                        pos=i;
        if(pos==0){
                int x=a[pos+1]-a[pos];
                x/=2;
                x=a[pos]+x;
                cout<<x<<'\n';
        }else if(pos==n-1){
                int x=a[pos]-a[pos-1];
                x/=2;
                x=a[pos]-x;
                cout<<(int)1e6-x+1<<'\n';
        }else{
                int l=a[pos]-a[pos-1];
                l/=2;
                l=a[pos]-l;
                int r=a[pos+1]-a[pos];
                r/=2;
                r=a[pos]+r;
                cout<<r-l+1<<'\n';
        }
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

