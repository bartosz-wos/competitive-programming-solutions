#include<bits/stdc++.h>
using namespace std;
using ll=long long;

#define pb push_back

constexpr int N=505;

int n,m,sz;
vector<int>g[N];
bool M[N][N];
int deg[N];
bool ok[N];

struct dinic{
    struct Edge{
        int v,u;
        ll cap=0,flow=0;
        Edge(int v, int u, ll cap):v(v),u(u),cap(cap){}
    };
    const ll inf=1e18;
    vector<Edge>edges;
    vector<vector<int>>adj;
    int n,m=0;
    int s,t;
    vector<int>lvl,ptr;
    queue<int>q;
    
    dinic(int n, int s, int t):n(n),s(s),t(t){
        adj.resize(n+5);
        lvl.resize(n+5);
        ptr.resize(n+5);
    }
    void add_edge(int v, int u, ll cap){
        adj[v].pb(m);
        adj[u].pb(m+1);
        m+=2;
        edges.pb({v,u,cap});
        edges.pb({u,v,0});
    }
    bool bfs(){
        while(!q.empty()){
            int x=q.front();
            q.pop();
            for(const int&id:adj[x]){
                int v=edges[id].u;
                ll cap=edges[id].cap;
                if(cap-edges[id].flow<1)continue;
                if(lvl[v]!=-1)continue;
                lvl[v]=lvl[x]+1;
                q.push(v);
            }
        }
        return lvl[t]!=-1;
    }
    ll dfs(int v, ll push){
        if(!push)return 0;
        if(v==t)return push;
        for(int&cid=ptr[v];cid<adj[v].size();++cid){
            int id=adj[v][cid];
            int u=edges[id].u;
            if(lvl[u]!=lvl[v]+1)continue;
            if(edges[id].cap-edges[id].flow<1)continue;
            ll p=dfs(u,min(push,edges[id].cap-edges[id].flow));
            if(!p)continue;
            edges[id].flow+=p;
            edges[id^1].flow-=p;
            return p;
        }
        return 0;
    }
    ll flow(){
        ll f=0;
        while(1){
            fill(lvl.begin(),lvl.end(),-1);
            lvl[s]=0;
            q.push(s);
            if(!bfs())break;
            fill(ptr.begin(),ptr.end(),0);
            ll cur=inf;
            while(cur=dfs(s,inf))f+=cur;
        }
        return f;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m;
    while(m--){
        int x,y;
        cin>>x>>y;
        ++x,++y;
        M[x][y]=1;
        ++deg[y];
        g[x].pb(y);
    }
    for(int k=1;k<=n;++k)
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                M[i][j]|=M[i][k]&M[k][j];
    memset(ok,1,sizeof ok);
    {
        queue<int>q;
        for(int i=1;i<=n;++i)
            if(!deg[i])q.push(i);
        while(!q.empty()){
            int x=q.front();
            q.pop();
            for(const int&i:g[x])
                if(--deg[i]==0)q.push(i);
        }
        for(int i=1;i<=n;++i)
            if(deg[i]){
                ok[i]=0;
                ++sz;
                for(int j=1;j<=n;++j)
                    M[i][j]=M[j][i]=0;
            }
    }
    dinic D(2*n+2,0,2*n+1);
    for(int i=1;i<=n;++i){
        D.add_edge(0,i,1);
        D.add_edge(n+i,2*n+1,1);
    }
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            if(M[i][j]){
                D.add_edge(i,n+j,D.inf);
            }
    cout<<n-D.flow()-sz<<'\n';
}
