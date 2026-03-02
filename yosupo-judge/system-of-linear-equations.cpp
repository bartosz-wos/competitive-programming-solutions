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
        vector<vector<ll>>M(n,vector<ll>(m+1,0));
        for(int i=0;i<n;++i)
                for(int j=0;j<m;++j)
                        cin>>M[i][j];
	for(int i=0;i<n;++i)
		cin>>M[i][m];
        int r=0;
	vector<int>pv(m,-1);
        for(int i=0;i<m and r<n;++i){
                int p=-1;
                for(int j=r;j<n;++j)
                        if(M[j][i]){
                                p=j;
                                break;
                        }
                if(p==-1)continue;
                if(p!=r)swap(M[r],M[p]);
		pv[i]=r;
                ll inv=exp(M[r][i],mod-2);
		for(int j=i;j<=m;++j)
			M[r][j]=M[r][j]*inv%mod;
                for(int j=r+1;j<n;++j){
                        if(!M[j][i])continue;
                        ll f=M[j][i];
                        for(int k=i;k<=m;++k){
                                M[j][k]-=f*M[r][k]%mod;
				if(M[j][k]<0)M[j][k]+=mod;
			}
                }
                ++r;
        }
	for(int i=r;i<n;++i)
		if(M[i][m]){
			cout<<-1<<'\n';
			return 0;
		}
	for(int i=m-1;i>=0;--i)
		if(~pv[i])
			for(int j=0;j<pv[i];++j){
				if(!M[j][i])continue;
				ll f=M[j][i];
				for(int k=i;k<=m;++k){
					M[j][k]-=f*M[pv[i]][k]%mod;
					if(M[j][k]<0)M[j][k]+=mod;
				}
			}
	vector<ll>c(m);
	vector<vector<ll>>d;
	for(int i=0;i<m;++i){
		if(~pv[i])c[i]=M[pv[i]][m];
		else{
			vector<ll>b(m);
			b[i]=1;
			for(int j=0;j<m;++j)
				if(~pv[j])
					b[j]=mod-(M[pv[j]][i]?M[pv[j]][i]:mod);
			d.push_back(b);
		}
	}
	cout<<d.size()<<'\n';
	for(int i=0;i<m;++i)
		cout<<c[i]<<' ';
	cout<<'\n';
	for(const auto&b:d){
		for(const ll&i:b)cout<<i<<' ';
		cout<<'\n';
	}
}
