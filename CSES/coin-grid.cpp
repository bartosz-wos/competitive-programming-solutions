#include<bits/stdc++.h>
using namespace std;
using ll=long long;
constexpr int MAXN=105;
 
char S[MAXN];
bool used[MAXN],inZ[2][MAXN];
int N,cnt,mt[MAXN];
vector<int>G[MAXN];
 
bool kuhn(int u){
    if(used[u])return 0;
    used[u]=1;
    for(const int&v:G[u])
        if(!mt[v] or kuhn(mt[v])){
            mt[v]=u;
            return 1;
        }
    return 0;
}
 
void dfs(int t, int u){
    inZ[t][u]=1;
    if(t==0 and !inZ[1][mt[u]])
        dfs(1,mt[u]);
    else if(t==1)
        for(const int&v:G[u])
            if(!inZ[0][v])
                dfs(0,v);
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>N;
    for(int i=1;i<=N;++i){
        cin>>S;
        for(int j=1;j<=N;++j)
            if(S[j-1]=='o')
                G[j].push_back(i);
    }
    cnt=0;
    for(int i=1;i<=N;++i){
        kuhn(i);
        memset(used,0,sizeof used);
    }
    for(int i=1;i<=N;++i)
        if(mt[i]){
            ++cnt;
            used[mt[i]]=1;
        }
    cout<<cnt<<'\n';
    for(int i=1;i<=N;++i)
        if(!used[i])
            dfs(1,i);
    for(int i=1;i<=N;++i)
        if(inZ[0][i])
            cout<<1<<' '<<i<<'\n';
    for(int i=1;i<=N;++i)
        if(!inZ[1][i])
            cout<<2<<' '<<i<<'\n';
}
