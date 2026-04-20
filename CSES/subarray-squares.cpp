#include<bits/stdc++.h>
using namespace std;
using ll=long long;
constexpr ll inf=1e18;
 
int n,k;
ll p[3001];
 
vector<ll>dp_cur(3001,0),dp_prev(3001,0);
 
ll C(int i, int j){return (p[j]-p[i-1])*(p[j]-p[i-1]);}
 
void solve(int l, int r, int optl, int optr){
	if(l>r)return;
	int mid=(l+r)>>1;
	array<ll,2>p={inf,-1};
	for(int i=optl;i<=min(mid,optr);++i)
		p=min(p,{dp_prev[i]+C(i+1,mid),i});
	dp_cur[mid]=p[0];
	solve(l,mid-1,optl,p[1]);
	solve(mid+1,r,p[1],optr);
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>k;
	for(int i=1;i<=n;++i){
		cin>>p[i];
		p[i]+=p[i-1];
	}
	for(int i=1;i<=n;++i)
		dp_prev[i]=C(1,i);
	for(int i=2;i<=k;++i){
		solve(1,n,1,n);
		dp_prev=dp_cur;
	}
	cout<<dp_prev[n];
}
