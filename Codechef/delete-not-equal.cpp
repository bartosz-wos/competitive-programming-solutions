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
        string s;
        cin>>s;
        for(int i=1;i<n;++i)
                if(s[i]!=s[i-1]){
                        cout<<1<<'\n';
                        return;
                }
        cout<<n<<'\n';
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

