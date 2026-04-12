#include<bits/stdc++.h>
using namespace std;
int t, n, p;
bool a;
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> t;
	while(t--) {
		a = 0;
		cin >> n;
		while(n--) {
			cin >> p;
			if(p & 1) a = 1;
		}
		cout << (a ? "first\n" : "second\n");
	}
}
