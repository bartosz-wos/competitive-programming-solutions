/*
You are given a directed graph on n vertices and an array a.
Initially, there are m edges (u_i, v_i) with weight 1

Then you need to process queries. Each query gives four integers v, l, r, and x
and asks you to add directed edges (v, i) with weight 1 for each i such that:
    1. l <= i <= r
    2. a[i] < x

After processing all queries, 
find the shortest path distance between start node s and target node t.
*/

#include<bits/stdc++.h>
using namespace std;
using ll=long long;

constexpr ll INF=1e18;
constexpr int MAXN=1e5+5;
constexpr int MAX_NODES=4e6+5;

struct edge{
        int to, w;
};

struct node{
        int l,r;
}tree[MAX_NODES];

vector<edge>g[MAX_NODES];
ll dist[MAX_NODES];
int roots[MAXN];
int cnt;

void add_edge(int u, int v, int w){
        g[u].push_back({v,w});
}

int build(int l, int r){
        int id=++cnt;
        if(l==r){
                add_edge(id,l,0);
                return id;
        }
        int mid=(l+r)>>1;
        tree[id].l=build(l,mid);
        tree[id].r=build(mid+1,r);
        add_edge(id,tree[id].l,0);
        add_edge(id,tree[id].r,0);
        return id;
}

int upd(int id, int l, int r, int pos, int nd){
        int cur=++cnt;
        tree[cur]=tree[id];
        if(id)add_edge(cur,id,0);
        if(l==r){
                add_edge(cur,nd,0);
                return cur;
        }
        int mid=(l+r)>>1;
        if(pos<=mid)tree[cur].l=upd(tree[id].l,l,mid,pos,nd);
        else tree[cur].r=upd(tree[id].r,mid+1,r,pos,nd);
        if(tree[cur].l)add_edge(cur,tree[cur].l,0);
        if(tree[cur].r)add_edge(cur,tree[cur].r,0);
        return cur;
}

void query_add(int v, int k, int l, int r, int ql, int qr){
        if(!k or l>qr or r<ql)return;
        if(l>=ql and r<=qr){
                add_edge(v,k,1);
                return;
        }
        int mid=(l+r)>>1;
        query_add(v,tree[k].l,l,mid,ql,qr);
        query_add(v,tree[k].r,mid+1,r,ql,qr);
}

struct element{
        int id,val;
};

bool cmp(const element&a, const element&b){
        return a.val<b.val;
}

int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        int n,m;
        cin>>n>>m;
        cnt=n;
        while(m--){
                int a,b;
                cin>>a>>b;
                add_edge(a,b,1);
        }
        vector<element>v(n);
        for(int i=0;i<n;++i){
                v[i].id=i+1;
                cin>>v[i].val;
        }
        sort(v.begin(),v.end(),cmp);
        roots[0]=0;
        vector<int>v_a;
        for(int i=0;i<n;++i){
                roots[i+1]=upd(roots[i],1,n,v[i].id,v[i].id);
                v_a.push_back(v[i].val);
        }
        int qr;
        cin>>qr;
        while(qr--){
                int v,l,r,x;
                cin>>v>>l>>r>>x;
                int ver=(lower_bound(v_a.begin(),v_a.end(),x)-v_a.begin());
                query_add(v,roots[ver],1,n,l,r);
        }
        int s,t;
        cin>>s>>t;
        memset(dist,-1,sizeof dist);
        dist[s]=0;
        deque<int>q;
        q.push_back(s);
        while(!q.empty()){
                int u=q.front();
                q.pop_front();
                for(const auto&e:g[u]){
                        int v=e.to;
                        int w=e.w;
                        if(dist[v]==-1 or dist[v]>dist[u]+w){
                                dist[v]=dist[u]+w;
                                if(!w)q.push_front(v);
                                else q.push_back(v);
                        }
                }
        }
        cout<<dist[t]<<'\n';
}
