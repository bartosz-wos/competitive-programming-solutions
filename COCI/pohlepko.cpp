#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pi=pair<int,int>;

#define pb push_back
#define fi first
#define se second

constexpr int dx[2]={0,1};
constexpr int dy[2]={1,0};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,m;
    cin>>n>>m;
    vector<vector<char>>a(n,vector<char>(m,1));
    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
            cin>>a[i][j];
    vector<pi>v;
    v.pb({0,0});
    while(!v.empty()){
        vector<pi>nw;
        cout<<a[v[0].fi][v[0].se];
        if(v[0]==pi(n-1,m-1))break;
        int opt=-1;
        for(const auto&[x,y]:v)
            for(int i=0;i<2;++i){
                int nx=x+dx[i];
                int ny=y+dy[i];
                if(nx>=n or ny>=m)continue;
                int c=a[nx][ny]-97;
                if(opt==-1 or c<opt){
                    opt=c;
                    nw.clear();
                    nw.pb({nx,ny});
                }else if(opt==c)nw.pb({nx,ny});
            }
        sort(nw.begin(),nw.end());
        nw.erase(unique(nw.begin(),nw.end()),nw.end());
        v.swap(nw);
    }
}
