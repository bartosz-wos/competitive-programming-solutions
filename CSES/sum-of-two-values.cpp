#include<iostream>
#include<map>
using namespace std;
 
int n, x, p;
map<int, int> mp;
int main() {
	cin >> n >> x;
	for(int i = 0; i < n; ++i) {
		cin >> p;
		if( mp.find(x - p) != mp.end() ) {
			cout << mp[x - p] + 1 << ' ' << i + 1;
			return 0;
		}
		mp[p] = i;
	}
	cout << "IMPOSSIBLE";
}
