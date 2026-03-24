#include<iostream>
using namespace std;
#define ios ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
 
 
void solve(int a, int b, int c, int n) {
	if (!n) return;
	solve(a, c, b, n - 1);
	cout << a << ' ' << c << '\n';
	solve(b, a, c, n - 1);
}
 
int n;
int main() {
	ios;
	cin >> n;
	cout << (1 << n) - 1 << '\n';
	solve(1, 2, 3, n);

