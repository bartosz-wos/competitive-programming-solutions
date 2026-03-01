#include<bits/stdc++.h>
using namespace std;
using ll=long long;

constexpr int mod=998244353;

ll exp(ll a, ll w){
        a%=mod;
        ll ret=1;
        while(w){
                if(w&1)ret=ret*a%mod;
                a=a*a%mod;
                w>>=1;
        }
        return ret;
}

int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        int n,m;
        cin>>n>>m;
        vector<vector<ll>>M(n,vector<ll>(m,0));
        for(int i=0;i<n;++i)
                for(int j=0;j<m;++j)
                        cin>>M[i][j];
        int r=0;
        for(int i=0;i<m and r<n;++i){
                int p=-1;
                for(int j=r;j<n;++j)
                        if(M[j][i]){
                                p=j;
                                break;
                        }
                if(p==-1)continue;
                if(p!=r)swap(M[r],M[p]);
                ll inv=exp(M[r]	[i],mod-2);
                for(int j=r+1;j<n;++j){
                        if(!M[j][i])continue;
                        ll f=M[j][i]*inv%mod;
                        for(int k=i;k<m;++k)
                                M[j][k]=(M[j][k]-f*M[r][k]%mod+mod)%mod;
                }
		++r;
        }
        cout<<r<<'\n';
}
