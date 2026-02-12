#include<bits/stdc++.h>
using namespace std;
using ll=long long;

constexpr int N=2e5+5;

vector<int>g[N];
ll res[N],sz[N];

void dfs(int v){
    sz[v]=1;
    for(const int&i:g[v]){
        dfs(i);
        res[v]+=res[i];
        sz[v]+=sz[i];
    }
    res[v]+=sz[v];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin>>n;
    for(int i=2,x;i<=n;++i){
        cin>>x;
        g[x].push_back(i);
    }
    dfs(1);
    for(int i=1;i<=n;++i)
        cout<<res[i]<<' ';
}
