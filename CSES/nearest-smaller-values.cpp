#include<bits/stdc++.h>
using namespace std;
using ar = array<int, 2>;
int n, p;
stack<ar> S;
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n;
	for(int i = 1; i <= n; ++i) {
		cin >> p;
		while(!S.empty() && S.top()[0] >= p)
			S.pop();
		if(S.empty())
			cout << 0 << ' ';
		else
			cout << S.top()[1] << ' ';
		S.push({p, i});
	}
}
