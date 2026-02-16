#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int st[20][500005];

int get(int l, int r){
	int lg=31-__builtin_clz(r-l+1);
	return min(st[lg][l],st[lg][r-(1<<lg)+1]);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n,q;
	cin>>n>>q;
	for(int i=0;i<n;++i)
		cin>>st[0][i];
	for(int i=1;i<20;++i)
		for(int j=0;j+(1<<i)-1<n;++j)
			st[i][j]=min(st[i-1][j],st[i-1][j+(1<<(i-1))]);
	while(q--){
		int l,r;
		cin>>l>>r;
		--r;
		cout<<get(l,r)<<'\n';
	}
}
