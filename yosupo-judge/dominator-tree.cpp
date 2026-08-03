#include<bits/stdc++.h>
using namespace std;
using ll=long long;

constexpr int maxn=200005;

int n, m, S, p[maxn], sdom[maxn], idom[maxn], label[maxn];
int timer, st[maxn], inv[maxn], dsu[maxn];
vector<int> g[maxn], rg[maxn], bucket[maxn];
int ans[maxn];

void dfs(int v){
        st[v]=++timer;
        inv[timer]=v;
        label[timer]=sdom[timer]=dsu[timer]=timer;
        for(const int&i:g[v]){
                if(!st[i]){
                        dfs(i);
                        p[st[i]]=st[v];
                }
                rg[st[i]].push_back(st[v]);
        }
}

int find(int u, bool x=0){
        if(u==dsu[u])return x?-1:u;
        int v=find(dsu[u],1);
        if(v<0)return u;
        if(sdom[label[dsu[u]]]<sdom[label[u]])
                label[u]=label[dsu[u]];
        dsu[u]=v;
        return x?v:label[u];
}

void build(int root){
        dfs(root);

        for(int u=timer; u>=1; --u){
                for(const int&v:rg[u])
                        sdom[u]=min(sdom[u],sdom[find(v)]);
                if(u>1) bucket[sdom[u]].push_back(u);
                
                for(const int&i:bucket[u])
                        idom[i]=(sdom[find(i)]==sdom[i]?sdom[i]:find(i));
                        
                if(u>1) dsu[u]=p[u];
        }
        for(int u=2;u<=timer;++u){
                if(idom[u]!=sdom[u])
                        idom[u]=idom[idom[u]];
        }
}

int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        
        cin>>n>>m>>S;
        ++S; 

        while(m--){
                int a,b;
                cin>>a>>b;
                ++a; ++b; 
                g[a].push_back(b);
        }
        
        build(S);

        for(int i=1; i<=n; ++i) ans[i] = -1; 
        ans[S] = S; 
        
        for(int u=2; u<=timer; ++u){
                ans[inv[u]] = inv[idom[u]];
        }

        for(int i=1; i<=n; ++i){
                if (ans[i] == -1) cout << -1 << ' ';
                else cout << ans[i] - 1 << ' '; 
        }
        cout << '\n';
}
