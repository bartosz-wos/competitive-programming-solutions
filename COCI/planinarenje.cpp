#include<bits/stdc++.h>
using namespace std;
using ll=long long;

constexpr int MAXN=1e4+5;
constexpr int mod=1e9+7;

int xd=-1;

int n,m;
vector<int>g[MAXN];
bool used[MAXN];
int to[MAXN];
bool nact[MAXN];

bool dfs(int x){
    if(used[x])return 0;
    used[x]=1;
    for(const int&i:g[x]){
        if(nact[i])continue;
        if(to[i]==-1 or dfs(to[i])){
            to[i]=x;
            return 1;
        }
    }
    return 0;
}

bool aug(int x){
    for(int i=n+1;i<=2*n;++i)used[i]=0;
    return dfs(x);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m;
    while(m--){
        int a,b;
        cin>>a>>b;
        b+=n;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    memset(to,-1,sizeof to);
    for(int i=n+1;i<=2*n;++i)aug(i);
    for(int i=1;i<=n;++i){
        if(to[i]==-1){
            cout<<"Mirko\n";
            continue;
        }
        int temp=to[i];
        to[i]=-1;
        nact[i]=1;
        if(aug(temp)){
            nact[i]=0;
            cout<<"Mirko\n";
        }else{
            nact[i]=0;
            aug(temp);
            cout<<"Slavko\n";
        }
    }
}
