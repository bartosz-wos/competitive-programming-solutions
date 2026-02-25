#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        int n,mod;
        cin>>n>>mod;
        vector<vector<ll>>M(n,vector<ll>(n,0));
        for(int i=0;i<n;++i)
                for(int j=0;j<n;++j){
                        cin>>M[i][j];
			M[i][j]%=mod;
		}
        ll det=1%mod;
        for(int i=0;i<n;++i){
		for(int j=i+1;j<n;++j){
			while(M[j][i]){
				ll q=M[i][i]/M[j][i];
				for(int k=i;k<n;++k)
					M[i][k]=(M[i][k]-q*M[j][k]%mod+mod)%mod;
				swap(M[i],M[j]);
				det=(mod-det);
			}
		}
		det=det*M[i][i]%mod;
        }
        cout<<det<<'\n';
}
