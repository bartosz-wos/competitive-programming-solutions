#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define io ios_base::sync_with_stdio(0),cin.tie(0);
#define str string
#define db double
using namespace std;
const int maxn=1e6+2;
int t, n, a[maxn], aa[103][103],b,sum , m , x[maxn] , y[maxn];
int ioioioio() {
	map <int, int > yy, xx;
	for(int i  = 1;  i <= n ; i++) {
		for(int j = i + 1 ; j <= n; j++) {
			yy[y[j] - y[i]]++;
		}
	}
	for(int i  = 1;  i <= m ; i++) {
		for(int j = i + 1 ; j <= m ; j++) {
			xx[x[j] - x[i]]++;
		}
	}
	for(auto i : yy){
		if(xx.count(i.first)){
			sum += i.second * xx[i.first];
		}
	}	
	return sum;
}
signed main() {
	io;
	cin >> n >> m;
	for(int i = 1 ;i  <= n  ;i++){
		cin >> y[i];
	}
	for(int i = 1; i <= m ; i++){
		cin >> x[i];
	}
	cout << ioioioio();
}
