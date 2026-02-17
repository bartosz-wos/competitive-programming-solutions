#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int z[500005];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	string s;
	cin>>s;
	int n=s.size();
	int l=0,r=0;
	cout<<n<<' ';
	for(int i=1;i<n;++i){
		if(i<=r)z[i]=min(r-i+1,z[i-l]);
		while(i+z[i]<n and s[z[i]]==s[i+z[i]])++z[i];
		if(i+z[i]-1>r){
			l=i;
			r=i+z[i]-1;
		}
		cout<<z[i]<<' ';
	}
}
