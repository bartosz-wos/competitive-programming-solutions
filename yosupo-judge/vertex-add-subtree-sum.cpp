#include<bits/stdc++.h>
using namespace std;
using ll=long long;

vector<int>g[500005];

int dep[500005];
int ptr[20][500005];
int st[500005];
int en[500005];
int tr=1;

void dfs(int v, int e){
        st[v]=tr++;
        for(int i=1;i<20;++i)
                ptr[i][v]=ptr[i-1][ptr[i-1][v]];
        for(const int&u:g[v]){
                if(u==e)continue;
                dep[u]=dep[ptr[0][u]=v]+1;
                dfs(u,v);
        }
        en[v]=tr-1;
}

int kth(int x, int k){
        int j=0;
        while(k){
                if(k&1)x=ptr[j][x];
                ++j;
                k>>=1;
        }
        return x;
}

int lca(int u, int v){
        if(dep[u]<dep[v])swap(u,v);
        u=kth(u,dep[u]-dep[v]);
        if(u==v)return u;
        for(int i=19;i>=0;--i)
                if(ptr[i][u]!=ptr[i][v])
                        u=ptr[i][u],v=ptr[i][v];
        return ptr[0][u];
}

int dist(int u, int v){
        return dep[u]+dep[v]-(dep[lca(u,v)]<<1);
}

int n,N,q;
ll seg[1000005];
ll tab[500005];

void upd(int i, ll x){
        for(;i<=N;i+=i&-i)
                seg[i]+=x;
}

ll get(int i){
        ll res=0;
        for(;i;i-=i&-i)
                res+=seg[i];
        return res;
}

int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        cin>>n>>q;
        N=n+1;
        for(int i=0;i<n;++i)
                cin>>tab[i];
        for(int i=1,p;i<n;++i){
		cin>>p;
                g[i].push_back(p);
		g[p].push_back(i);
        }
        dfs(0,-1);
        for(int i=0;i<n;++i)
                upd(st[i],tab[i]);
        while(q--){
                int t,a,b;
                cin>>t>>a;
                if(!t){
			cin>>b;
                        upd(st[a],b);
                        tab[a]+=b;
                }else cout<<get(en[a])-get(st[a]-1)<<'\n';
        }
}
