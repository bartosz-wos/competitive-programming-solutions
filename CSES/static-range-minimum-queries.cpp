#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
int n,q,res=1;
int x[1000000];
int ST[1000000][22];
short lg[1000001];
 
int f(int i, int j){
	int p=lg[j-i+1];
	return min(ST[i][p],ST[j-(1<<p)+1][p]);
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>q;
	for(int i=0;i<n;++i)
		cin>>x[i];
	lg[0]=0;
	lg[1]=0;
	for(int i=2;i<=n;++i)
		lg[i]=lg[i>>1]+1;
	for(int i=0;i<n;++i)
		ST[i][0]=x[i];
	for(int l=1;l<22;++l)
		for(int i=0;i+(1<<l)-1<n;++i)
			ST[i][l]=min(ST[i][l-1],ST[i+(1<<(l-1))][l-1]);
	while(q--){
		int a,b;
		cin>>a>>b;
		cout<<f(a-1,b-1)<<'\n';
	}
}
