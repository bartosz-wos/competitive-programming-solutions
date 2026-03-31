#include<iostream>
using namespace std;
#define ios ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
 
int get_max(int n) {
	if (!n)
		return 0;
	return max(n % 10, get_max(n / 10));
}
 
int n, ans;
int main() {
	ios;
	cin >> n;
	while (n) {
		n -= get_max(n);
		++ans;
	}
	cout << ans;
}
