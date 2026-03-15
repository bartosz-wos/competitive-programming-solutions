#include<bits/stdc++.h>
using namespace std;
using ll=long long;

constexpr int mod=998244353;

ll exp(ll a, ll w){
        ll ret=1;
        a%=mod;
        while(w){
                if(w&1)ret=ret*a%mod;
                a=a*a%mod;
                w>>=1;
        }
        return ret;
}

void fwht(vector<int>&a, bool f){
        int n=a.size();
        for(int len=1;len<n;len<<=1)
                for(int i=0;i<n;i+=(len<<1))
                        for(int j=0;j<len;++j){
                                int u=a[i+j];
                                int v=a[i+j+len];
				if(!f){
                                	a[i+j]=u+v;
                                	if(a[i+j]>=mod)a[i+j]-=mod;
				}else{
                                	a[i+j]=u-v;
                                	if(a[i+j]<0)a[i+j]+=mod;
				}
                        }
}

int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        int n;
        cin>>n;
        int sz=1<<n;
        vector<int>a(sz),b(sz);
        for(int&i:a)cin>>i;
        for(int&i:b)cin>>i;
        fwht(a,0);
        fwht(b,0);
        for(int i=0;i<sz;++i)
                a[i]=1ll*a[i]*b[i]%mod;
        fwht(a,1);
        for(int i=0;i<sz;++i)cout<<a[i]<<' ';
}
