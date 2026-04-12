#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ld=long double;
constexpr int N=8;
constexpr int SZ=N*N;
 
int K;
ld res,ans[SZ],dp[101][SZ];
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>K;
    for(int i=0;i<SZ;++i)
        ans[i]=1;
    for(int start=0;start<SZ;++start){
        memset(dp,0,sizeof dp);
        dp[0][start]=1;
        for(int k=0;k<K;++k){
                for(int u=0;u<SZ;++u){
                    vector<int>v;
                    if(N<=u)v.push_back(u-N);
                    if(u<N*(N-1))v.push_back(u+N);
                    if(u%N!=0)v.push_back(u-1);
                    if(u%N!=N-1)v.push_back(u+1);
                    for(int e:v)
                    dp[k+1][e]+=(dp[k][u]/v.size());
                }
        }
        for(int i=0;i<SZ;++i)
            ans[i]*=(1-dp[K][i]);
    }
    for(int i=0;i<SZ;++i)
        res+=ans[i];
    cout<<fixed<<setprecision(6)<<res<<'\n';
}
