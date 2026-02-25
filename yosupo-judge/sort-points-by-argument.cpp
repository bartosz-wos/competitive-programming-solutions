#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ar=array<ll,2>;

bool cmp(const ar&a, const ar&b){
	return atan2l(a[1],a[0])<atan2l(b[1],b[0]);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n;
	cin>>n;
	vector<ar>v(n);
	for(int i=0;i<n;++i)
		cin>>v[i][0]>>v[i][1];
	sort(v.begin(),v.end(),cmp);
	for(const auto&[x,y]:v)
		cout<<x<<' '<<y<<'\n';
}
