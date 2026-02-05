#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10;
const int MAXM = 100000+5;

#define fst first
#define snd second
#define pb push_back
#define SZ(x) (int)x.size()
#define ALL(x) x.begin(),x.end()
#define forn(i,a,b) for(int i = a; i < b; i++)
#define mset(a,v) memset(a,v,sizeof(a))

typedef int ll;

//vector<pair<ll,ll>> adj[MAXN][MAXM];
bool visited[MAXN][MAXM];
pair<ll,ll> parent[MAXN][MAXM];
string table[MAXN];
ll n=10, m; 

void dfs(ll y, ll x, ll py, ll px){
    if(visited[y][x]) return;
    visited[y][x]=true;
    parent[y][x]={py,px};
    if(y==n-1 && x+1<m && table[y][x+1]=='.') dfs(y,x+1,y,x);
    if(y+1<10 && x+1<m && table[y+1][x+1]=='.') dfs(y+1,x+1,y,x);
    if(y-1>=0 && x+1<m && table[y-1][x+1]=='.') dfs(y-1,x+1,y,x);
    if(y==0 && x+1<m && table[y][x+1]=='.') dfs(y,x+1,y,x);
}

int main(){
    mset(visited,false);
    cin>>m;

    for(int i = n-1; i >= 0; i--){
            cin>>table[i];
    }

    /*forn(i,0,n){
        forn(j,0,m){
            if(i==n-1 && j+1<m && table[i][j+1]=='.') adj[i][j].pb({i,j+1});
            if(i+1<10 && j+1<m && table[i+1][j+1]=='.') adj[i][j].pb({i+1,j+1});
            if(i-1>=0 && j+1<m && table[i-1][j+1]=='.') adj[i][j].pb({i-1,j+1});
            if(i==0 && j+1<m && table[i][j+1]=='.') adj[i][j].pb({i,j+1});
        }
    }*/

    //cout<<"paso\n";

    dfs(0,0,0,0);

    ll fila;
    forn(i,0,n){
        if(visited[i][m-1]){
            fila=i;
        }
    }


    vector<pair<ll,ll>> res;
    bool sube = false;
    ll aux = 0;
    pair<ll,ll> ndAct = {fila,m-1};
    while(ndAct.snd!=0){
        //cout<<ndAct.fst<<" "<<ndAct.snd<<'\n';
        if((parent[ndAct.fst][ndAct.snd].fst<ndAct.fst)||(parent[ndAct.fst][ndAct.snd].fst==ndAct.fst && ndAct.fst==n-1)){
            sube=true;
            aux++;
        }else if(sube){
            res.pb({ndAct.snd,aux});
            sube=false;
            aux=0;
        }
        ndAct=parent[ndAct.fst][ndAct.snd];
    }
    //cout<<ndAct.fst<<" "<<ndAct.snd<<'\n';
    if(sube) res.pb({0,aux});

    reverse(ALL(res));
    cout<<SZ(res)<<'\n';
    for(auto i:res){
        cout<<i.fst<<" "<<i.snd<<'\n';
    }

    return 0;
}
