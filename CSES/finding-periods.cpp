#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int mod = 1e9 + 7;
string a;
int z[1000001];
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> a;
 
    	int x = 0, y = 0;
    	for (int i = 1; i < a.length(); i++) {
        	z[i] = max(0, min(z[i-x], y-i+1));
        	while (i+z[i] < a.length() && a[z[i]] == a[i+z[i]]) {
            	x = i; 
		y = i + z[i]; 
		z[i]++;
        }
        if (z[i] + i == a.length()) cout << i << ' ';
    }
    cout << a.length();
}
