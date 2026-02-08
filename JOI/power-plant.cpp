#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll n,dp[200005],ans=0;
vector<ll> adj[200005];
string s;

void dfs(ll cur,ll p){
    ll maxi=0,sum=0;
    for(auto i:adj[cur]){
        if(i==p) continue;
        dfs(i,cur);
        maxi=max(maxi,dp[i]);
        sum+=dp[i];
    }
    if(s[cur-1]=='0'){
        ans=max(ans,sum);
        dp[cur]=sum;
    }
    else{
        ans=max(ans,maxi+1);
        ans=max(ans,sum-1);
        dp[cur]=max(1LL,sum-1);
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cin>>s;
    dfs(1,0);
    cout<<ans;
}
