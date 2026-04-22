#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define fi first
#define se second
#define pb push_back
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	if(!(cin>>n))return 0;
	vector<ll> invpref(n+1,0);
	ll x,y;
	for(int k=1;k<=n;k++){
		cout<<1<<" "<<k<<endl;
		cout.flush();
		cin>>x;
		cout<<1<<" "<<k<<endl;
		cout.flush();
		cin>>y;
		ll pairs=1LL*k*(k-1)/2;
		ll delta=x-y;
		ll invp=(pairs-delta)/2;
		invpref[k]=invp;
	}
	vector<int> g(n+1,0);
	for(int k=1;k<=n;k++){
		if(k==1)g[k]=0;
		else g[k]=invpref[k]-invpref[k-1];
	}
	vector<int> rk(n+1,0);
	for(int k=1;k<=n;k++)rk[k]=k-g[k];
	vector<int> rem;
	rem.reserve(n);
	for(int v=1;v<=n;v++)rem.pb(v);
	vector<int> a(n+1,0);
	for(int k=n;k>=1;k--){
		int idx=rk[k]-1;
		int val=rem[idx];
		a[k]=val;
		rem.erase(rem.begin()+idx);
	}
	for(int i=1;i<=n;i++){
		if(a[i]==i)continue;
		int pos=i;
		for(int j=i+1;j<=n;j++)if(a[j]==i){pos=j;break;}
		cout<<i<<" "<<pos<<endl;
		cout.flush();
		ll inv;
		cin>>inv;
		reverse(a.begin()+i,a.begin()+pos+1);
		if(inv==0)break;
	}
	return 0;
}
