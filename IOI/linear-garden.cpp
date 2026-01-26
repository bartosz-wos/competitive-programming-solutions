#include<bits/stdc++.h>
using namespace std;
vector<pair<int,int>>v;
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int n,m;
    cin>>n>>m;
    string str;
    cin>>str;
    int A=0,B=0;
    for(auto i:str) {
        if(i=='P'){
            v.push_back({A+1,max(1,B)-1});
        } else v.push_back({3,3});
        if(i=='L')
            A++,B=max(1,B)-1;
        else B++,A=max(1,A)-1;
    }
    reverse(v.begin(),v.end());
    int dp[4][4]{},dp2[4][4]{};
    long long ans=1;
    dp[0][0]=1;
    for(auto[a,b]:v){
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                if(i+a<3&&j+b<3)
                    ans+=dp[i][j];
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                dp2[i+1][max(j-1,0)]+=dp[i][j],
                dp2[max(i-1,0)][j+1]+=dp[i][j];
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                dp[i][j]=dp2[i][j]%m,dp2[i][j]=0;
    }
    cout<<ans%m;
}
