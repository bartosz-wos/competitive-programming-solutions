#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pi=pair<ll,ll>;

constexpr ll mod=998244353;

pi op_down(pi a, pi b){ 
    return pi{(a.first*b.first)%mod,(b.first*a.second%mod+b.second)%mod}; 
}

pi op_up(pi a, pi b){ 
    return pi{(a.first*b.first)%mod,(a.first*b.second%mod+a.second)%mod}; 
}

pi e(){return pi{1,0};}

template <class T, T (*op)(T, T), T(*e)()>
struct segtree{
   vector<T>d;
   int n;
   T a,b;
   segtree(int n=0):segtree(vector<T>(n,e())){}
   segtree(const vector<T>&v):n((int)v.size()){ 
      d.assign(n<<1,e());
      for(int i=0;i<n;++i)d[n+i]=v[i];
      for(int i=n-1;i>=1;--i)d[i]=op(d[i<<1],d[i<<1|1]);
   }
   void set(int p, T x){ 
      d[p+=n]=x;
      for(p>>=1;p;p>>=1)d[p]=op(d[p<<1],d[p<<1|1]); 
   }
   T operator[](int p){ 
      return d[p+n]; 
   }
   T operator()(int l, int r){
      a=e(),b=e();
      for(l+=n,r+=n;l<r;l>>=1,r>>=1){ 
          if(l&1)a=op(a,d[l++]); 
          if(r&1)b=op(d[--r],b); 
      }
      return op(a,b);
   }
};

int tr=0;
vector<int>g[200005];
int par[200005];
int dep[200005];
int hd[200005];
int pos[200005];

int dfs_sz(int v, int p, int d){
    par[v]=p;
    dep[v]=d;
    int sz=1,mx=0;
    for(int&u:g[v]){
        if(u^p){
            int sub_sz=dfs_sz(u,v,d+1);
            sz+=sub_sz;
            if(sub_sz>mx) {
                mx=sub_sz;
                swap(u,g[v][0]);
            }
        }
    }
    return sz;
}

void dfs_hld(int v, int p, int h){
    hd[v]=h;
    pos[v]=tr++;
    bool ok=1;
    for(const int&u:g[v]){
        if (u^p) {
            dfs_hld(u,v,ok?h:u);
            ok=0;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,q;
    cin>>n>>q;
    vector<pi>a(n);
    for(int i=0;i<n;++i)
        cin>>a[i].first>>a[i].second;
    for(int i=1,u,v;i<n;++i) {
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs_sz(0, -1, 0);
    dfs_hld(0, -1, 0);
    vector<pi>init_a(n);
    for(int i=0;i<n;++i)
        init_a[pos[i]]=a[i];
    segtree<pi,op_down,e>seg_d(init_a);
    segtree<pi,op_up,e>seg_u(init_a);
    while(q--){
        int t;
        cin>>t;
        if(!t){
            int p;
            ll c,d;
            cin>>p>>c>>d;
            seg_d.set(pos[p],{c, d});
            seg_u.set(pos[p],{c, d});
        } 
        else{
            int u,v;
            ll x;
            cin>>u>>v>>x;
            pi res_u=e();
            pi res_v=e();
            while(hd[u]^hd[v]){
                if (dep[hd[u]]>dep[hd[v]]) {
                    pi val=seg_u(pos[hd[u]],pos[u]+1);
                    res_u=op_down(res_u,val);
                    u=par[hd[u]];
                }else{
                    pi val=seg_d(pos[hd[v]],pos[v]+1);
                    res_v=op_down(val,res_v);
                    v=par[hd[v]];
                }
            }
            if(dep[u]>dep[v]) {
                pi val=seg_u(pos[v],pos[u]+1);
                res_u=op_down(res_u,val);
            }else{
                pi val=seg_d(pos[u],pos[v]+1);
                res_v=op_down(val,res_v);
            }
            pi ret=op_down(res_u,res_v);
            cout<<(ret.first*x%mod+ret.second)%mod<<'\n';
        }
    }
}
