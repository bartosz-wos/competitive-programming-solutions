#include<bits/stdc++.h>
using namespace std;
using ll=long long;

constexpr int mod=998244353;

int a[1000005];
int b[1000005];
ll a2[1000005];
ll b2[1000005];
ll c[1000005];

int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        int n;
        cin>>n;
        for(int i=1;i<=n;++i)cin>>a[i];
        for(int i=1;i<=n;++i)cin>>b[i];
        for(int i=1;i<=n;++i)
                for(int j=i;j<=n;j+=i){
                        a2[j]+=a[i];
                        if(a2[j]>=mod)a2[j]-=mod;
                        b2[j]+=b[i];
                        if(b2[j]>=mod)b2[j]-=mod;
                }
        for(int i=1;i<=n;++i)
                c[i]=a2[i]*b2[i]%mod;
        for(int i=1;i<=n;++i)
                for(int j=i<<1;j<=n;j+=i){
                        c[j]-=c[i];
                        if(c[j]<0)c[j]+=mod;
                }
        for(int i=1;i<=n;++i)
                cout<<c[i]<<' ';
        cout<<'\n';
}
