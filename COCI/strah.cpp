#include<bits/stdc++.h>
using namespace std;
using ll=long long;

constexpr int MAXN=2e3+5;

int n,m;
string s[MAXN];
int high[MAXN][MAXN];
int l[MAXN][MAXN],r[MAXN][MAXN];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        cin>>s[i];
        s[i]='#'+s[i]+'#';
        for(int j=1;j<=m;++j)
            high[i][j]=(s[i][j]=='.'?high[i-1][j]+1:0);
    }
    ll ans=0;
    for(int i=1;i<=n;++i){
        stack<int>S;
        for(int j=1;j<=m;++j){
            while(!S.empty() and high[i][S.top()]>=high[i][j])S.pop();
            l[i][j]=S.empty()?1:S.top()+1;
            S.push(j);
        }
        S=stack<int>();
        for(int j=m;j>=1;--j){
            while(!S.empty() and high[i][S.top()]>high[i][j])S.pop();
            r[i][j]=S.empty()?m:S.top()-1;
            S.push(j);
        }
        for(int j=1;j<=m;++j){
            ll x=j-l[i][j]+1;
            ll y=r[i][j]-j+1;
            ans+=1ll*high[i][j]*(high[i][j]+1ll)*x*y*(x+y)/4;
        }
    }
    cout<<ans<<'\n';
}
