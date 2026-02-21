#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pi=pair<int,int>;

#define fi first
#define se second

constexpr int N=5e5+5;

int n,m;

struct dsu{
        int par[N];
        dsu(){for(int i=0;i<N;++i)par[i]=-1;}
        int find(int x){
                if(par[x]<0)return x;
                return par[x]=find(par[x]);
        }
        bool unite(int a, int b){
                a=find(a);
                b=find(b);
                if(a==b)return 0;
                if(par[a]>par[b])swap(a,b);
                assert(par[a]<0 and par[b]<0);
                par[a]+=par[b];
                par[b]=a;
                return 1;
        }
        int sz(int x){return -par[find(x)];}
        bool same(int a, int b){return find(a)==find(b);}
};

set<int>g[N];

int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);

        cin>>n>>m;
        dsu p;
        vector<pi>edg;
        while(m--){
                int a,b;
                char c;
                cin>>a>>b>>c;
                if(c=='T')p.unite(a,b);
                else edg.push_back({a,b});
        }
        for(auto[a,b]:edg){
                if(p.same(a,b))continue;
                g[p.find(a)].insert(p.find(b));
                g[p.find(b)].insert(p.find(a));
        }
        int ret=0;
        for(int i=1;i<=n;++i){
                if(i!=p.find(i))continue;
                int c=p.sz(i);
                for(const int&j:g[i])c+=p.sz(j);
                ret+=(c==n)*p.sz(i);
        }
        cout<<ret<<'\n';
}

