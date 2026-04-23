#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
int t,n,k;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>t;
	while(t--){
		cin>>n>>k;
		if(k*k<n){
			cout<<"IMPOSSIBLE\n";
			continue;
		}
		int l=1,r=k;
		while(1){
			for(int i=r;i>=l;--i)
				cout<<i<<' ';
			if(r==n)
				break;
			l=r+1;
			r=min(r+k,n);
		}
		cout<<'\n';
	}
}
