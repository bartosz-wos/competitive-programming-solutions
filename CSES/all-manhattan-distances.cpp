#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define fi first
#define se second
#define pb push_back
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	if(!(cin>>n))return 0;
	vector<ll> xs(n),ys(n);
	for(int i=0;i<n;i++)cin>>xs[i]>>ys[i];
	sort(xs.begin(),xs.end());
	sort(ys.begin(),ys.end());
	__int128 ans=0;
	__int128 pref=0;
	for(int i=0;i<n;i++){
		ans+=(__int128)xs[i]*(__int128)i - pref;
		pref+=xs[i];
	}
	pref=0;
	for(int i=0;i<n;i++){
		ans+=(__int128)ys[i]*(__int128)i - pref;
		pref+=ys[i];
	}
	if(ans==0){
		cout<<0<<"\n";
		return 0;
	}
	__int128 v=ans;
	string s;
	while(v>0){
		int dig=(int)(v%10);
		s.push_back('0'+dig);
		v/=10;
	}
	reverse(s.begin(),s.end());
	cout<<s<<"\n";
	return 0;
}
