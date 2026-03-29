#include<iostream>
#include<set>
using namespace std;
using pi = pair<int, int>;
 
int n, p, ans = 1, ind[200007];
int main() {
	cin >> n;
	for(int i = 1; i <= n; ++i) {
		cin >> p;
		ind[p] = i;
	}
 
	int poz = 1;
	for(int i = 1; i <= n; ++i) {
		if(poz > ind[i])
			++ans;
		poz = ind[i];
	}
	cout << ans;
}
