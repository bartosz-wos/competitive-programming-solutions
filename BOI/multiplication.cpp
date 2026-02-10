#include<bits/stdc++.h>
#define ll long long
#define ldb long double
#define db double
#define fi first
#define se second
#define sza(a) (int)a.size()
#define pir pair<int,int>
#define pirll pair<ll,ll>
using namespace std;

template <class t1,class t2> inline void maxi(t1 &x,t2 y){if (x < y) x = y;}
template <class t1,class t2> inline void mini(t1 &x,t2 y){if (x > y) x = y;}


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	
	ll n,res = 1;
	cin >> n;
	ll modu = 1e9 + 7;
	while (n--){
		ll x;
		cin >> x;
		x %= modu;
		res = res * x % modu;
	}
	
	cout << res;

	return 0;
}

