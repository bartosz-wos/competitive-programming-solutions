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
	vector<vector<ll>>M(n,vector<ll>(n,0));
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j)
			cin>>M[i][j];
        ll det=1;
        for(int i=0;i<n;++i){
                int p=-1;
                for(int j=i;j<n;++j)
                        if(M[j][i]){
                                p=j;
                                break;
                        }
                if(p==-1){
                        det=0;
                        break;
                }
                if(p!=i){
                        swap(M[i],M[p]);
                        det=mod-det;
                }
                det=det*M[i][i]%mod;
                ll inv=exp(M[i][i],mod-2);
                for(int j=i+1;j<n;++j){
                        if(!M[j][i])continue;
                        ll f=M[j][i]*inv%mod;
                        for(int k=i;k<n;++k)
                                M[j][k]=(M[j][k]-f*M[i][k]%mod+mod)%mod;
                }
        }
        cout<<det<<'\n';
}
