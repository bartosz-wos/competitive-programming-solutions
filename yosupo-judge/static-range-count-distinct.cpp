#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pi=array<int,2>;

int n,q;
int st[500005];
int ans[500005];

void upd(int i, int x){
	for(++i;i<=n;i+=i&-i)
		st[i]+=x;
}

int get(int i){
	ll ret=0;
	for(++i;i;i-=i&-i)
		ret+=st[i];
	return ret;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>q;
	map<int,int>mp;
	int cnt=0;
	vector<int>a(n);
	for(int&i:a){
		cin>>i;
		if(!mp.count(i))mp[i]=++cnt;
		i=mp[i];
	}
	vector<vector<pi>>qr(n);
	for(int i=0,l,r;i<q;++i){
		cin>>l>>r;
		--r;
		if(l>r){
			ans[i]=0;
			continue;
		}
		qr[r].push_back({l,i});
	}
	map<int,int>lst;
	for(int i=0;i<n;++i){
		if(lst.count(a[i]))upd(lst[a[i]],-1);
		upd(i,1);
		for(const auto&[l,id]:qr[i])
			ans[id]=get(i)-get(l-1);
		lst[a[i]]=i;
	}
	for(int i=0;i<q;++i)
		cout<<ans[i]<<'\n';
}
