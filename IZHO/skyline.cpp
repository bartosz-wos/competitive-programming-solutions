#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int a[305];
int dp[305][205][205];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin>>n;
    for(int i=1;i<=n;++i)cin>>a[i];
    memset(dp,0x3f3f3f3f,sizeof dp);
    dp[0][0][0]=0;
    for(int i=1;i<=n;++i)
        for(int j=a[i-1];j>=0;--j)
            for(int k=a[i];k>=0;--k){
                int x=a[i]-k;
                dp[i][j][k]=min({dp[i][j][k+1]+3,dp[i][j+1][k+1]+5,dp[i-1][x][j+x]+x*7,dp[i-1][0][j+x]+x*5,dp[i-1][0][j]+x*3});
            }
    cout<<dp[n][0][0]<<'\n';
}
