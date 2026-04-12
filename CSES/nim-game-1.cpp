#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int t, n, p, ans;
#define pc putchar_unlocked
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> t;
	while(t--) {
		ans = 0;
		cin >> n;
		for(int i = 0; i < n; ++i) {
			cin >> p;
			ans ^= p;
		}
		if(ans)
			pc('f'), pc('i'), pc('r'), pc('s'), pc('t');
		else
			pc('s'), pc('e'), pc('c'), pc('o'), pc('n'), pc('d');
		pc('\n');
	}
}
