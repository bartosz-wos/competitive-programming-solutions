#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using ll=long long;
using ar=array<int,4>;

#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n,q;
	cin>>n>>q;
	vector<int>a(n),vals;
	for(int&i:a){
		cin>>i;
		vals.push_back(i);
	}

	vector<ar>qr(q);
	for(int i=0;i<q;++i){
		cin>>qr[i][0];
		if(!qr[i][0]){
			cin>>qr[i][1]>>qr[i][2];
			vals.push_back(qr[i][2]);
		}else
			cin>>qr[i][1]>>qr[i][2]>>qr[i][3];
	}

	sort(vals.begin(),vals.end());
	vals.erase(unique(vals.begin(),vals.end()),vals.end());

	auto get=[&](int x){
		int it=lower_bound(vals.begin(),vals.end(),x)-vals.begin();
		if(it!=vals.size() and vals[it]==x)
			return it;
		return -1;
	};

	vector<ordered_set>pos(vals.size());
	for(int i=0;i<n;++i)
		pos[get(a[i])].insert(i);
	for(int i=0;i<q;++i){
		if(!qr[i][0]){
			pos[get(a[qr[i][1]])].erase(qr[i][1]);
			a[qr[i][1]]=qr[i][2];
			pos[get(a[qr[i][1]])].insert(qr[i][1]);
		}else{
			int id=get(qr[i][3]);
			if(!~id)
				cout<<0<<'\n';
			else
				cout<<pos[id].order_of_key(qr[i][2])-pos[id].order_of_key(qr[i][1])<<'\n';
		}
	}
}
