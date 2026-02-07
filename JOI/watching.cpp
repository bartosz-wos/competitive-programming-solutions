#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int n,p,q;
int a[2005];
int dp[2005][2005];

bool check(int mid){
    memset(dp,0,sizeof dp);
    for(int i=0;i<=p;++i)
        for(int j=0;j<=q;++j){
            int x,y;
            x=y=n;
            if(i){
                x=dp[i-1][j];
                dp[i][j]=max(dp[i][j],x);
            }
            if(j){
                y=dp[i][j-1];
                dp[i][j]=max(dp[i][j],y);
            }
            if(i and x<n){
                int X=a[x+1]+mid-1;
                int x1=upper_bound(a+1,a+n+1,X)-a-1;
                dp[i][j]=max(dp[i][j],x1);
            }
            if(j and y<n){
                int X=a[y+1]+2*mid-1;
                int x1=upper_bound(a+1,a+n+1,X)-a-1;
                dp[i][j]=max(dp[i][j],x1);
            }
            if(dp[i][j]==n)return 1;
        }
    return 0;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>p>>q;
    p=min(p,n);
    q=min(q,n);
    for(int i=1;i<=n;++i)cin>>a[i];
    sort(a+1,a+n+1);
    int l=1,r=5e8,mid,ans;
    while(l<=r){
        mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }else l=mid+1;
    }
    cout<<ans<<'\n';
}
