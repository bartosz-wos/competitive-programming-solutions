#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n;
	cin>>n;
	ll basis[31]={0};
	int cnt=0;
	while(n--){
		ll x;
		cin>>x;
		for(int j=30;j>=0;--j){
			if(!(x&(1ll<<j)))continue;
			if(!basis[j]){
				basis[j]=x;
				++cnt;
				break;
			}
			x^=basis[j];
		}
	}
	cout<<(1ll<<cnt)<<'\n';
}
