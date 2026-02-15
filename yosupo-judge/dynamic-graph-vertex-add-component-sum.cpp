#include <bits/stdc++.h>
using namespace std;

#define int long long 

#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define sp <<' '<<
#define pb push_back

#define FOR(i,a) for(int i=0;i<(a);i++)
#define FORE(i,a,b) for(int i=(a);i<(b);i++)

#define cont(a) for(auto el:a) cout<<el<<' '; cout<<endl;
#define contp(a) for(auto el:a) cout<<el.fi<<'-'<<el.se<<' ';cout<<endl;

#define DEBUG(x) cout<<#x sp ":" sp x<<endl;

#define endl '\n'

typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<pii> vii;
typedef long long ll;
typedef pair<double,double> pdd;

#define topla(x,y,MOD) ((x%MOD)+(y%MOD))%MOD
#define carp(x,y,MOD) ((x%MOD)*(y%+MOD))%MOD

#define mid ((l+r)/2)

const int INF=1e9+7;
const int MAXN=3e5+5;

int n,q;
int val[MAXN];


vector<pair<int,pii>> t[4*MAXN];

void add(pair<int,pii> val,int ql,int qr,int nd=1,int l=1,int r=q){
    if(l>r or l>qr or r<ql) return;
    if(ql<=l and r<=qr){
        t[nd].pb(val);
        return;
    }

    add(val,ql,qr,nd*2,l,mid);
    add(val,ql,qr,nd*2+1,mid+1,r);
}


int rr[MAXN],p[MAXN],sum[MAXN];
vector<pair<int &,int>> hist;

int find(int a){
    while(a!=p[a]) a=p[a];
    return a;
}

void uni(int a,int b){
    a=find(a);
    b=find(b);

    if(a==b) return;

    hist.pb({rr[a],rr[a]});
    hist.pb({p[a],p[a]});
    hist.pb({sum[a],sum[a]});

    hist.pb({rr[b],rr[b]});
    hist.pb({p[b],p[b]});
    hist.pb({sum[b],sum[b]});

    if(rr[a]>rr[b]) swap(a,b);
    p[a]=b;
    sum[b]+=sum[a];
    if(rr[a]==rr[b]) rr[b]++;
}

void roll(int tt){
    while(hist.size()>tt){
        hist.back().fi=hist.back().se;
        hist.pop_back();
    }
}


map<int,int> cev;

void dfs(int nd=1,int l=1,int r=q){
    if(l>r) return;

    int tt=hist.size();

    for(auto el:t[nd]){
        int op=el.fi;
        if(op==1){
            uni(el.se.fi,el.se.se);
        }
    }

    for(auto el:t[nd]){
        int op=el.fi;
        if(op==2){
            val[el.se.fi]+=el.se.se;
            sum[find(el.se.fi)]+=el.se.se;
        }    
    }

    if(l==r){
        for(auto el:t[nd]){
            int op=el.fi;
            if(op==3){
                cev[el.se.se]=sum[find(el.se.fi)];
            }    
        }
    }
    else{
        dfs(nd*2,l,mid);    
        dfs(nd*2+1,mid+1,r);
    }

    for(auto el:t[nd]){
        int op=el.fi;
        if(op==2){
            val[el.se.fi]-=el.se.se;
            sum[find(el.se.fi)]-=el.se.se;
        }    
    }

    roll(tt);
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>q;
    FORE(i,1,n+1){
        cin>>val[i];
        p[i]=i;
        sum[i]=val[i];
    }

    map<pii,int> edg;

    FORE(i,1,q+1){
        int op;
        cin>>op;
        if(op==0){
            int u,v;
            cin>>u>>v;
            u++;v++;
            edg[{u,v}]=i;
            edg[{v,u}]=i;
        }
        else if(op==1){
            int u,v;
            cin>>u>>v;
            u++;v++;

            pair<int,pii> el;
            el.fi=1;
            el.se={u,v};

            add(el,edg[{u,v}],i-1);
            edg[{u,v}]=0;
            edg[{v,u}]=0;
        }
        else if(op==2){
            int v,x;
            cin>>v>>x;
            v++;
            pair<int,pii> el;
            el.fi=2;
            el.se={v,x};

            add(el,i,q);
        }
        else{
            int v;
            cin>>v;
            v++;
            pair<int,pii> el;
            el.fi=3;
            el.se={v,i};
            
            add(el,i,i);
        }
    }

    for(auto [p,deg]:edg){
        if(deg){
            pair<int,pii> el;
            el.fi=1;
            el.se=p;
            add(el,deg,q);
        }
    }

    dfs();

    for(auto el:cev) cout<<el.se<<endl;
}
