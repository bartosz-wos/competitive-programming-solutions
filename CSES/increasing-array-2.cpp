#include<bits/stdc++.h>
using namespace std;
int n;
priority_queue<int> Q;
long long ans = 0;
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n;
	for(int i = 0; i < n; ++i) {
		int t;
		cin >> t;
		Q.push(t);
		ans += Q.top() - t;
		Q.pop();
		Q.push(t);
	}
	cout << ans;
}
