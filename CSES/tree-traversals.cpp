#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
vector<ll>pre,in;
ll a[100001];
ll n,x;
void post(int l=0, int h=n-1){
	if(l>h){
		--x;
		return;
	}
	int i=a[pre[x]];
	++x;
	post(l,i-1);
	++x;
	post(i+1,h);
	cout<<in[i]<<' ';
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n;
	for(int i=0;i<n;++i){
		int p;
		cin>>p;
		pre.push_back(p);
	}
	for(int i=0;i<n;++i){
		int p;
		cin>>p;
		in.push_back(p);
		a[p]=i;
	}
	post();
}
