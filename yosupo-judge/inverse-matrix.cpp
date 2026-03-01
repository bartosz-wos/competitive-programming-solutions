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
        int n;
        cin>>n;
        vector<vector<ll>>M(n,vector<ll>(n<<1,0));
        for(int i=0;i<n;++i){
                for(int j=0;j<n;++j)
                        cin>>M[i][j];
		M[i][i+n]=1;
	}
        for(int i=0;i<n;++i){
                int p=-1;
                for(int j=i;j<n;++j)
                        if(M[j][i]){
                                p=j;
                                break;
                        }
                if(p==-1){
			cout<<-1<<'\n';
			return 0;
                }
                if(p!=i)swap(M[i],M[p]);
                ll inv=exp(M[i][i],mod-2);
		for(int j=i;j<(n<<1);++j)
			M[i][j]=M[i][j]*inv%mod;
                for(int j=0;j<n;++j){
                        if(j==i or !M[j][i])continue;
                        ll f=M[j][i];
                        for(int k=i;k<(n<<1);++k){
                                M[j][k]=(M[j][k]-f*M[i][k])%mod;
				if(M[j][k]<0)M[j][k]+=mod;
			}
                }
        }
	for(int i=0;i<n;++i){
		for(int j=n;j<(n<<1);++j)
			cout<<M[i][j]<<' ';
		cout<<'\n';
	}
}
