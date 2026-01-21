#include<bits/stdc++.h>
using namespace std;

#define int long long
#define i128 int128
#define ii pair<int,int>
#define ld long double
#define vi vector<int>
#define vvi vector<vi>
#define vii vector<pair<int,int>>
#define FOR(i,a,b) for (int i=a;i<=b;i++)
#define FOR1(i,a,b,c) for (int i=a;i<=b;i+=c)
#define REP(i,a,b) for (int i=a;i>=b;i--)
#define REP1(i,a,b,c) for(int i=b;i>=a;i-=c)
#define endh '\n';
#define len(a) a.length()
#define pb(c) push_back(c)
#define elif else if
#define ppb() pop_back()
#define rong std::npos
#define all(c) (c.begin(),c.end())
#define Z int
#define R double
#define lcm(a,b) ((int) (a/__gcd(a,b))*b)
#define mk(a,b) make_pair(a,b)
Z dx4[]={-1,1,0,0};
Z dy4[]={0,0,1,-1};
string co="YES",khong="NO";
const int mod=1e9+7;
const Z oo=1e16;
const Z maxn=100005;
Z tin[maxn],tout[maxn];
vii g[maxn];
Z dp[maxn],check[maxn],id=0,up[20][maxn],c,s[maxn],f1[maxn],f[maxn],n,S,q,H,fd[20][maxn];
Z h[maxn];
/*
5 2 3 5
5 1 3
5 3 2
3 4 1
3 2 2
1
4
*/
ii canh[maxn];
void predfs(Z u,Z p)
{
    tin[u]=++id;
    if (check[u]) f1[u]=s[u];
    else f1[u]=oo;
    for (ii v:g[u]){
        if (v.first==p) continue;
        s[v.first]=s[u]+v.second;
        h[v.first]=h[u]+1;
        up[0][v.first]=u;
        predfs(v.first,u);
        f1[u]=min(f1[u],f1[v.first]);
    }
    tout[u]=id;
}
bool ispar(Z par,Z u)
{
    return tin[par]<=tin[u] && tout[par]>=tout[u];
}
Z calc( Z u,Z v)
{
    Z tam=s[u];
    Z ans=f[u]+s[u];
    REP(i,19,0){
        if (h[up[i][u]]>=h[v]){
            ans=min(ans,fd[i][u]+tam);
            u=up[i][u];
        }
    }
    return ans;
}
void solve()
{
    cin>>n>>S>>q>>H;

    FOR(i,2,n){
        Z x,y,w;
        cin>>x>>y>>w;
        g[x].pb(mk(y,w));
        g[y].pb(mk(x,w));
        canh[i-1]=mk(x,y);
    }
    FOR(i,1,S){
        Z x;cin>>x;check[x]=1;
    }
    h[H]=1;
    predfs(H,0);

    FOR(i,1,n) f[i]=f1[i]-2*s[i];
    FOR(i,1,n) fd[0][i]=f[up[0][i]];
    FOR(i,1,19){
        FOR(j,1,n){
            up[i][j]=up[i-1][up[i-1][j]];
           fd[i][j]=min(fd[i-1][j],fd[i-1][up[i-1][j]]);
        }
    }
    FOR(i,1,n-1){
        if (h[canh[i].first]>h[canh[i].second]) swap(canh[i].first,canh[i].second);
    }
    while(q--){
        Z id,u;
        cin>>id>>u;
        if (!(ispar(canh[id].first,u) && ispar(canh[id].second,u))){
            cout<<"escaped\n";
            continue;
        }
        Z tam=calc(u,canh[id].second);
        if (tam>=1e14) {
            cout<<"oo\n";
        }
        else{
            cout<<tam<<'\n';
        }
    }
}
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Z t=1;
  //  cin>>t;
    while(t--) solve();
}


