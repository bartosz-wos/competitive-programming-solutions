#include<bits/stdc++.h>
using namespace std;
using ll=long long;

constexpr int N=500;

int n;
int dp[2][N][N],cnt[2][N][N],nxt[N][N];
int pos=0;
basic_string<int>g[N];

int start(int _N, bool _A[N][N]){
    n=_N;
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
            if(_A[i][j])
                g[i].push_back(j);
    vector<array<int,3>>tmp;
    for(int i=0;i<n;++i){
        dp[1][i][i]=1;
        dp[0][i][i]=1;
        nxt[i][i]=i;
        tmp.push_back({1,i,i});
        tmp.push_back({0,i,i});
    }
    for(int it=0;it<tmp.size();++it){
        auto[t,x,y]=tmp[it];
        if(t==0){
            auto var=g[y];
            for(auto y2:var){
                if(dp[t^1][x][y2])continue;
                ++cnt[t^1][x][y2];
                if(cnt[t^1][x][y2]==(int)g[y2].size()){
                    dp[t^1][x][y2]=1;
                    tmp.push_back({t^1,x,y2});
                }
            }
        }else{
            auto var=g[x];
            var.push_back(x);
            for(auto x2:var){
                if(dp[t^1][x2][y])continue;
                nxt[x2][y]=x;
                dp[t^1][x2][y]=1;
                tmp.push_back({t^1,x2,y});
            }
        }
    }
    for(int i=0;i<n;++i){
        int win=0;
        for(int j=0;j<n;++j)
            if(dp[0][i][j]==1)++win;
        if(win==n)return pos=i;
    }
    return -1;
}

int nextMove(int pos2){
    return pos=nxt[pos][pos2];
}
