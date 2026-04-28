#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
int n,last[200001];
ll k,a[400004];
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>k;
	for(int i=0;i<n;++i){
		cin>>a[i];
		a[i+n]=a[i];
	}
	int r=0;
	ll s=0;
	for(int l=0;l<n;++l){
		while(r<l+n and s+a[r]<=k){
			s+=a[r];
			++r;
		}
		last[l]=r%n;
		s-=a[l];
	}
	int p=0;
	for(int i=0;i<n;++i)
		p=last[p];
	int cnt=1;
	s=a[p];
	for(int i=p+1;i<n+p;++i){
		if(s+a[i]<=k)s+=a[i];
		else{
			s=a[i];
			++cnt;
		}
	}
	cout<<cnt<<'\n';
}
