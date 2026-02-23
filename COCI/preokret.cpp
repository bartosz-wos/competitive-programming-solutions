//#pragma GCC optimize("O3,unroll-loops,Ofast")
//#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
//using namespace __gnu_pbds;
 
#define MAX 200007
#define pb push_back
#define mp make_pair 
#define int long long
#define f first
#define s second
#define vi vector<int>
#define pii pair<int,int>
#define si set<int>
#define vpii vector<pair<int,int>> 
const int mod = 1e9+7;
const int INF = 1e18;
// myMap.begin()->first :  key
// myMap.begin()->second : value
 
int epow(int a,int b){int ans=1;while(b){if(b&1) ans*=a;a*=a;;b>>=1;}return ans;}
int gcd(int a,int b) {if(a<b)swap(a,b);while(b){int tmp=b;b=a%b;a=tmp;}return a;}
int mul(int a,int b){return ((a%mod)*(b%mod))%mod;}
int sum(int a,int b){return ((a%mod)+(b%mod))%mod;}
 
//typedef tree<pii,null_type,less<pii>,rb_tree_tag,tree_order_statistics_node_update>ordered_set;

void solve(){
	int a; cin>>a;
 	vi v1(a); for(int i=0;i<a;i++) cin>>v1[i];
 	int b; cin>>b;
 	vi v2(b); for(int i=0;i<b;i++) cin>>v2[i];

 	int sure=4*12*60,sayi=0;
 	for(int i=0;i<a;i++) if(v1[i]<=sure/2) sayi++;
 	for(int i=0;i<b;i++) if(v2[i]<=sure/2) sayi++;
 	cout<<sayi<<endl;

 	vpii arr;
 	for(int i=0;i<a;i++) arr.pb({v1[i],1});
 	for(int i=0;i<b;i++) arr.pb({v2[i],2});
 	sort(arr.begin(),arr.end());

	int last=(arr[0].s==1?2:1),bir=0,iki=0;
//	cout<<last<<endl;
	if(arr[0].s==1) bir++;
	else iki++;

	int ans=0;
	for(int i=1;i<arr.size();i++){
		if(arr[i].s==1) bir++;
		else iki++;
		if(last==1 && bir>iki){last=2;ans++;}
		else if(last==2 && iki>bir){last=1;ans++;}
//		cout<<ans<<" "<<bir<<" "<<iki<<endl;
	}

	cout<<ans<<endl;


	return;
}
 
int32_t main() {
	ios_base::sync_with_stdio(0);cin.tie(0);   
 
    int t=1;
 //   cin >> t;
    while (t--) solve();
 
    return 0;
}
