#include<bits/stdc++.h>
using namespace std;
using ll=long long;
constexpr int mod=1e9+7;
 
ll dp[501][124753];
ll p[124753];
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int N,K;
    cin>>N>>K;
 
    for(int i=0;i<=N;++i)
        dp[i][0]=dp[i][i*(i-1)/2]=1;
    for(int i=1;i<=N;++i){
        p[0]=1;
        for(int k=1;k<=K;++k){
            p[k]=p[k-1]+dp[i-1][k];
            if(p[k]>=mod)p[k]-=mod;
        }
        for(int k=1;k<=K;++k){
            int low=i-1;
            if(k-low<0)low=k;
            if(k-low==0)dp[i][k]=p[k];
            else dp[i][k]=p[k]-p[k-low-1];
            if(dp[i][k]<0)dp[i][k]+=mod;
        }
    }
 
    cout<<dp[N][K]<<'\n';
}
