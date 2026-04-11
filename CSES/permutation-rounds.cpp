#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define fi first
#define se second
#define pb push_back
 
const ll MOD=1000000007LL;
ll modpow(ll a,ll e){ll r=1;while(e){if(e&1)r=r*a%MOD;a=a*a%MOD;e>>=1;}return r;}
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n; if(!(cin>>n))return 0;
	vector<int> p(n+1);
	for(int i=1;i<=n;i++)cin>>p[i];
	vector<int> vis(n+1,0);
	vector<int> lens;
	for(int i=1;i<=n;i++){
		if(vis[i])continue;
		int cur=i;
		int cnt=0;
		while(!vis[cur]){
			vis[cur]=1;
			cnt++;
			cur=p[cur];
		}
		if(cnt>0)lens.pb(cnt);
	}
	int maxN=n;
	vector<int> spf(maxN+1,0);
	for(int i=2;i<=maxN;i++)if(spf[i]==0){
		for(int j=i;j<=maxN;j+=i)if(spf[j]==0)spf[j]=i;
	}
	unordered_map<int,int> mp; mp.reserve(1024);
	for(int len:lens){
		int x=len;
		while(x>1){
			int pr=spf[x];
			int e=0;
			while(x%pr==0){x/=pr;e++;}
			auto it=mp.find(pr);
			if(it==mp.end()||it->second<e)mp[pr]=e;
		}
	}
	ll ans=1;
	for(auto &kv:mp){
		ans=ans*modpow(kv.first,kv.second)%MOD;
	}
	cout<<ans<<"\n";
	return 0;
}
