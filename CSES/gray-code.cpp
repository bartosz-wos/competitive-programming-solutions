#include<iostream>
#include<vector>
using namespace std;
#define ios ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
 
bool value(int number, int pos) {
	return (number & (1 << pos));
}
 
int main() {
	ios;
	int n;
	cin >> n;
	for (int i = 0; i < (1 << n); ++i) {
		cout << value(i, n - 1);
		for (int j = n - 2; j >= 0; --j)
			cout << (value(i, j) ^ value(i, j + 1));
		cout << '\n';
	}

