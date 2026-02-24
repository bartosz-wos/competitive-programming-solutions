#include<bits/stdc++.h>
using namespace std;
using ll=long long;

vector<int>g[100005];
ll a[100005];
int ptr[18][100005];
int dep[100005];

void dfs_lca(int v, int e){
        for(int i=1;i<18;++i)
                ptr[i][v]=ptr[i-1][ptr[i-1][v]];
        for(const int&i:g[v]){
                if(i==e)continue;
                dep[i]=dep[ptr[0][i]=v]+1;
                dfs_lca(i,v);
        }
}

int kth(int v, int k){
        int j=0;
        while(k){
                if(k&1)v=ptr[j][v];
                ++j;
                k>>=1;
        }
        return v;
}

int lca(int u, int v){
        if(dep[u]<dep[v])swap(u,v);
        u=kth(u,dep[u]-dep[v]);
        if(u==v)return u;
        for(int i=17;i>=0;--i)
                if(ptr[i][u]!=ptr[i][v])
                        u=ptr[i][u],v=ptr[i][v];
        return ptr[0][u];
}

int dist(int u, int v){
        return dep[u]+dep[v]-2*dep[lca(u,v)];
}

int sz[100005];
bool del[100005];
int par[100005];
int md1[100005];
int md2[100005];
vector<ll>st1[100005];
vector<ll>st2[100005];

void get_sz(int v, int e){
        sz[v]=1;
        for(const int&i:g[v]){
                if(del[i] or i==e)continue;
                get_sz(i,v);
                sz[v]+=sz[i];
        }
}

int get_c(int v, int e, int tot){
        for(const int&i:g[v]){
                if(del[i] or i==e)continue;
                if((sz[i]<<1)>tot)return get_c(i,v,tot);
        }
        return v;
}

void dfs(int v, int e, int c, int ec){
        md1[c]=max(md1[c],dist(c,v));
        if(~ec)md2[c]=max(md2[c],dist(ec,v));
        for(const int&i:g[v]){
                if(del[i] or i==e)continue;
                dfs(i,v,c,ec);
        }
}

void build_tree(int v, int e){
        get_sz(v,-1);
        int c=get_c(v,-1,sz[v]);
        del[c]=1;
        par[c]=e;
        md1[c]=md2[c]=0;
        dfs(c,-1,c,e);
        st1[c].resize(md1[c]+5);
        if(~e)st2[c].resize(md2[c]+5);
        for(const int&i:g[c]){
                if(del[i])continue;
                build_tree(i,c);
        }
}

void upd(int i, ll x, vector<ll>&st){
        for(++i;i<(int)st.size();i+=i&-i)
                st[i]+=x;
}

void upd_range(int l, int r, ll x, vector<ll>&st){
	l=max(0,l);
	if(l>=r or l>=st.size())return;
	upd(l,x,st);
	if(r<st.size())upd(r,-x,st);
}

ll get(int i, const vector<ll>&st){
        if(i<0)return 0;
        ll ret=0;
        for(i=min(i+1,(int)st.size()-1);i;i-=i&-i)
                ret+=st[i];
        return ret;
}

void upd_tree(int v, int l, int r, ll x){
        int cur=v;
        while(~cur){
		int d=dist(cur,v);
                upd_range(l-d,r-d,x,st1[cur]);
                if(~par[cur]){
			d=dist(par[cur],v);
			upd_range(l-d,r-d,x,st2[cur]);
		}
                cur=par[cur];
        }
}

ll get_tree(int v){
        ll ret=a[v];
        int cur=v;
        while(~cur){
                ret+=get(dist(cur,v),st1[cur]);
                if(~par[cur])ret-=get(dist(par[cur],v),st2[cur]);
                cur=par[cur];
        }
        return ret;
}

int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        int n,q;
        cin>>n>>q;
        for(int i=0;i<n;++i)
                cin>>a[i];
        for(int i=1,u,v;i<n;++i){
                cin>>u>>v;
                g[u].push_back(v);
                g[v].push_back(u);
        }
        dfs_lca(0,-1);
        build_tree(0,-1);
        while(q--){
                int t,p,l,r,x;
                cin>>t>>p;
                if(!t){
			cin>>l>>r>>x;
			upd_tree(p,l,r,x);
		}else cout<<get_tree(p)<<'\n';
        }
}
