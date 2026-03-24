#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pi=pair<int,int>;
 
#define fi first
#define se second
 
int dx[]={1,1,-1,-1,2,2,-2,-2};
int dy[]={2,-2,2,-2,1,-1,1,-1};
 
int n;
 
int d[1005][1005];
 
bool check(int i, int j){
    return i>=0 and i<n and j>=0 and j<n;
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    memset(d,-1,sizeof d);
    cin>>n;
    d[0][0]=0;
    queue<pi>q;
    q.push({0,0});
    while(!q.empty()){
        int x=q.front().fi;
        int y=q.front().se;
        q.pop();
        for(int k=0;k<8;++k){
            int i=x+dx[k];
            int j=y+dy[k];
            if(!check(i,j))continue;
            if(d[i][j]!=-1)continue;
            d[i][j]=d[x][y]+1;
            q.push({i,j});
        }
    }
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j)
            cout<<d[i][j]<<' ';
        cout<<'\n';
    }
}
