#include<bits/stdc++.h>
using namespace std;

const int mn=3e5+11;

vector<int>adj[mn];
bool r[mn];
int sz[mn];

int get_tree_size(int u,int par=-1){
    sz[u]=1;
    for(int v:adj[u])if(v!=par && !r[v])
        sz[u]+=get_tree_size(v,u);
    return sz[u];
}
int get_centroid(int u,int tree_size,int par=-1){
    for(int v:adj[u])if(v!=par && !r[v])
        if(sz[v]*2>tree_size)
            return get_centroid(v,tree_size,u);
    return u;
}

inline int get(char x){
    return x==')' ? -1 : 1;
}

string a;

struct holder{
    int cnt[2*mn];
    int elements[3*mn],cc=0;

    inline void emplace(int x){
        elements[++cc]=x;
        cnt[x+mn]++;
    }
    inline void erase(int x){
        if(cnt[x+mn])cnt[x+mn]--;
    }
    inline int get(int x){
        return cnt[x+mn];
    }
    inline void clear(){
        while(cc)erase(elements[cc--]);
    }
}st;

void traverse(int u,int par,int cur,int dip,bool dir){
    if(dip>=0){
        if(dir)st.emplace(cur);
        else st.erase(cur);
    }
    for(int v:adj[u])if(v!=par && !r[v]){
        int nxt=cur+get(a[v]);
        traverse(v,u,nxt,min(dip+get(a[v]),get(a[v])),dir);
    }
}

long long res=0;
void dfs(int u,int par,int cur,int dip){
    if(-cur+dip>=0)res+=st.get(-cur);
    
    for(int v:adj[u])if(v!=par && !r[v]){
        int nxt=cur+get(a[v]);
        dfs(v,u,nxt,min(dip,nxt));
    }
}

void centroid_decompose(int root=1){
    root=get_centroid(root,get_tree_size(root));

    st.clear();
    traverse(root,-1,get(a[root]),get(a[root]),1);

    for(int other:adj[root])if(!r[other]){
        int cur=get(a[root])+get(a[other]);
        int dip=min(get(a[other]),cur);

        traverse(other,root,cur,dip,0);
        dfs(other,root,get(a[other]),get(a[other]));
        traverse(other,root,cur,dip,1);
    }
    res+=st.get(0);

    r[root]=true;
    for(int other:adj[root])if(!r[other])
        centroid_decompose(other);
}

int32_t main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n;cin>>n;
    cin>>a;
    a='0'+a;

    for(int i=2,u,v;i<=n;i++){
        cin>>u>>v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    centroid_decompose();
    return cout<<res,0;
}
