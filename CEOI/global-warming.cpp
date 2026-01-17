#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int n,x;
int a[200005];
int pref[200005];

int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        cin>>n>>x;
        for(int i=0;i<n;++i)cin>>a[i];
        vector<int>dp(n,INT_MAX);
        int longest=0;
        for(int i=0;i<n;++i){
                int j=lower_bound(dp.begin(),dp.end(),a[i])-dp.begin();
                dp[j]=a[i];
                pref[i]=j+1;
                longest=max(longest,pref[i]);
        }
        dp=vector<int>(n,INT_MAX);
        for(int i=n-1;i>=0;--i){
                int pos=lower_bound(dp.begin(),dp.end(),-a[i]+x)-dp.begin();
                longest=max(longest,pref[i]+pos);
                int ins=lower_bound(dp.begin(),dp.end(),-a[i])-dp.begin();
                dp[ins]=-a[i];
        }
        cout<<longest<<'\n';
}
