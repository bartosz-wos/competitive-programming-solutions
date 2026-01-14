#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ar=array<ll,2>;
ll n,k,res=1e7;
vector<ar>g[200000];
ll sz[200000];
bool used[200000];
map<ll,ll>mp;
void siz(int v, int e){
        sz[v]=1;
        for(const auto&[i,w]:g[v])
                if(i!=e and !used[i]) siz(i,v),sz[v]+=sz[i];
}
ll get(int v, int e, ll des){
        for(const auto&[i,w]:g[v])
                if(i!=e and !used[i] and sz[i]>des) return get(i,v,des);
        return v;
}
void help(int v, int e, ll km, ll d, bool fill){
        if(km>k) return;
        if(fill){
                if(!mp.count(km)) mp[km]=d;
                else mp[km]=min(mp[km],d);
        }
        else{
                if(km==k) res=min(res,d);
                else if(mp.count(k-km)) res=min(res,d+mp[k-km]);
        }
        for(const auto&[i,w]:g[v])
                if(i!=e and !used[i]) help(i,v,km+w,d+1,fill);
}
void decomp(ll v=0){
        siz(v,-1);
        int c=get(v,-1,sz[v]>>1);
        used[c]=1;
        for(const auto&[i,w]:g[c])
                if(!used[i]){
                        help(i,c,w,1,0);
                        help(i,c,w,1,1);
                }
        mp.clear();
        for(const auto&[i,w]:g[c])
                if(!used[i]) decomp(i);
}
int best_path(int N, int K, int H[][2],int L[]){
        n=N;
        k=K;
        for(ll i=0;i<n-1;++i){
                g[H[i][0]].push_back({H[i][1],L[i]});
                g[H[i][1]].push_back({H[i][0],L[i]});
        }
        decomp();
        if(res==1e7) res=-1;
        return res;
}

