#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
const int MAXN=1e5;
long long bit[MAXN+1]={0};
void update(int i,int x){
    for(;i<=MAXN;i+=(i&(-i))){
        bit[i]+=x;
    }
}
long long query(int i){
    long long curr=0;
    for(;i;i-=(i&(-i))){
        curr+=bit[i];
    }
    return curr;
}
long long range(int l,int r){
    return (query(r)-query(l-1));
}
int in[MAXN+1],out[MAXN+1];
int tim=1;
vector<vector<int>> graph(MAXN+1);
int sparse[18][2*MAXN+1];
int timLCA=0;
int depth[MAXN+1];
int loga[2*MAXN+1];
int fir[MAXN+1];
int cmpLCA(int u,int v){
    if(depth[u]<depth[v]){
        return u;
    }
    return v;
}
int LCA(int u,int v){
    int l=fir[u],r=fir[v];
    if(l>r){
        swap(l,r);
    }
    return cmpLCA(sparse[loga[r-l+1]][l],sparse[loga[r-l+1]][r-(1<<loga[r-l+1])+1]);
}
void DFS(int u,int p){
    in[u]=tim;
    tim++;
    sparse[0][timLCA]=u;
    fir[u]=timLCA;
    timLCA++;
    for(int v:graph[u]){
        if(v!=p){
            depth[v]=depth[u]+1;
            DFS(v,u);
        }
    }
    out[u]=tim-1;
    if(p!=-1){
        sparse[0][timLCA]=p;
        timLCA++;
    }
}
struct inter{
    int low,high,s,t,idx;
};
bool cmp(inter &a,inter &b){
    return (((a.low+a.high)>>1)<((b.low+b.high)>>1));
}
bool bruh(pair<int,int> &a,pair<int,int> &b){
    return (a.second<b.second);
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    loga[1]=0;
    for(int i=2;i<=2*MAXN;i++){
        loga[i]=loga[i>>1]+1;
    }
    depth[1]=0;
    int n,m,q;
    cin >> n >> m >> q;
    vector<pair<int,int>> edges;
    edges.push_back({0,0});
    for(int i=0;i<n-1;i++){
        int a,b;
        cin >> a >> b;
        edges.push_back({a,b});
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    DFS(1,-1);
    for(int i=1;i<18;i++){
        for(int j=0;j+(1<<i)<=timLCA;j++){
            sparse[i][j]=cmpLCA(sparse[i-1][j],sparse[i-1][j+(1<<(i-1))]);
        }
    }
    vector<pair<int,int>> chk(m);
    for(int i=0;i<m;i++){
        cin >> chk[i].first >> chk[i].second;
    }
    sort(chk.begin(),chk.end(),bruh);
    long long gold[q],sil[q];
    vector<inter> que(q);
    for(int i=0;i<q;i++){
        cin >> que[i].s >> que[i].t >> gold[i] >> sil[i];
        que[i].idx=i;
        que[i].low=0,que[i].high=m-1;
        que[i].low--,que[i].high++;
    }
    vector<inter> temp2;
    while(!que.empty()){
        sort(que.begin(),que.end(),cmp);
        for(int i=1;i<=n;i++){
            bit[i]=0;
        }
        int ptr=-1;
        vector<inter> temp;
        for(inter &x:que){
            if(x.high-x.low<=1){
                temp2.push_back(x);
                continue;
            }
            inter nxt=x;
            int mid=((x.low+x.high)>>1);
            while(ptr<mid){
                ptr++;
                int u=edges[chk[ptr].first].first,p=edges[chk[ptr].first].second;
                if(depth[u]<depth[p]){
                    swap(u,p);
                }
                update(in[u],chk[ptr].second);
                if(out[u]+1<=MAXN){
                    update(out[u]+1,-chk[ptr].second);
                }
            }
            long long sum=query(in[x.s])+query(in[x.t])-2*query(in[LCA(x.s,x.t)]);
            if(sum<=sil[x.idx]){
                nxt.low=mid;
            }
            else{
                nxt.high=mid;
            }
            temp.push_back(nxt);
        }
        que=temp;
    }
    sort(temp2.begin(),temp2.end(),cmp);
    int ans[q];
    for(int i=1;i<=n;i++){
        bit[i]=0;
    }
    for(int ptr=0;ptr<m;ptr++){
        int u=edges[chk[ptr].first].first,p=edges[chk[ptr].first].second;
        if(depth[u]<depth[p]){
            swap(u,p);
        }
        update(in[u],1);
        if(out[u]+1<=MAXN){
            update(out[u]+1,-1);
        }
    }
    int ptr=-1;
    for(inter &x:temp2){
        while(ptr<x.low){
            ptr++;
            int u=edges[chk[ptr].first].first,p=edges[chk[ptr].first].second;
            if(depth[u]<depth[p]){
                swap(u,p);
            }
            update(in[u],-1);
            if(out[u]+1<=MAXN){
                update(out[u]+1,1);
            }
        }
        long long sum=query(in[x.s])+query(in[x.t])-2*query(in[LCA(x.s,x.t)]);
        if(sum<=gold[x.idx]){
            ans[x.idx]=gold[x.idx]-sum;
        }
        else{
            ans[x.idx]=-1;
        }
    }
    for(int i=0;i<q;i++){
        cout << ans[i] << endl;
    }
}
