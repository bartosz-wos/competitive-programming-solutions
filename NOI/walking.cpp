#include<bits/stdc++.h>
using namespace std;
using ll=long long;

struct node{
	ll t,v,num,den;
};

bool chk(const node&a, const node&b){
	return a.num*b.den>b.num*a.den;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	ll l,n;
	cin>>l>>n;

	vector<node>v(n);
	for(int i=0;i<n;++i){
		cin>>v[i].t>>v[i].v;
		v[i].num=v[i].t*v[i].v+l;
		v[i].den=v[i].v;
	}

	std::sort(v.begin(), v.end(), [](const node&a, const node& b){
		return a.t<b.t;
	});

	vector<int>dp(n,1);
	int ret=1;

	for(int i=0;i<n;++i)
		for(int j=0;j<i;++j)
			if(chk(v[j],v[i]))
				dp[i]=max(dp[i],dp[j]+1);

	cout<<*max_element(dp.data(),dp.data()+n)<<'\n';
}
