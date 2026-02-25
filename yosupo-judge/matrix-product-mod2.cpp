#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n,m,k;
	cin>>n>>m>>k;
	vector<string>a(n);
	for(string&s:a)cin>>s;
	vector<bitset<(1<<12)>>b(m);
	for(int i=0;i<m;++i){
		string s;
		cin>>s;
		for(int j=0;j<k;++j)
			if(s[j]-48)b[i].set(j);
	}
	for(int i=0;i<n;++i){
		bitset<(1<<12)>c;
		for(int j=0;j<m;++j)
			if(a[i][j]-48)
				c^=b[j];
		for(int j=0;j<k;++j)
			cout<<c[j];
		cout<<'\n';
	}
}
