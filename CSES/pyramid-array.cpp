#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ar=array<int,2>;
 
int n,f[200001];
ar a[200001];
 
void upd(int i){
	for(;i<=n;i+=i&-i)++f[i];
}
int ask(int i){
	int ret=0;
	for(;i>0;i-=i&-i)ret+=f[i];
	return ret;
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n;
	for(int i=0,x;i<n;++i){
		cin>>x;
		a[i]={x,i+1};
	}
	sort(a,a+n,[](const ar&a, const ar&b){return a[0]>b[0];});
	ll ret=0;
	for(int i=0;i<n;++i){
		int idx=a[i][1];
		int l=ask(idx);
		ret+=min(l,i-l);
		upd(idx);
	}
	cout<<ret<<'\n';
}
