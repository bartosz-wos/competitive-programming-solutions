#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
constexpr int MAXN=1<<21;
int freq[MAXN];
int dp1[MAXN+5][21],dp2[MAXN+5][21];
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin>>n;
    vector<int>a(n);
    for(int i=0;i<n;++i){
        cin>>a[i];
        ++freq[a[i]];
    }
    for(int i=1;i<MAXN>>1;++i){
        dp1[i][0]=freq[i];
        if(i&1)
            dp1[i][0]+=freq[i^1];
        for(int k=1;k<21;++k){
            dp1[i][k]=dp1[i][k-1];
            if(i>>k&1)
                dp1[i][k]+=dp1[i^1<<k][k-1];
        }    
    }
    for(int i=MAXN>>1;i>0;--i){
        dp2[i][0]=freq[i];
        if(i&1^1)
            dp2[i][0]+=freq[i^1];
        for(int k=1;k<21;++k){
            dp2[i][k]=dp2[i][k-1];
            if(i>>k&1^1)
                dp2[i][k]+=dp2[i^1<<k][k-1];
        }
    }
    for(int i=0;i<n;++i){
        cout<<dp1[a[i]][20]<<' '<<dp2[a[i]][20]<<' '<<n-dp1[a[i]^((MAXN>>1)-1)][20]<<'\n';
    }
}
