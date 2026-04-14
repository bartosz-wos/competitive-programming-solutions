#include<bits/stdc++.h>
using namespace std;
string a;
int Zar[1000001];
int lps[1000001];
 
void computelps() {
	int M = a.length();
	int i = 1, len = 0;
	lps[0] = 0;
	while(i < M) {
		if(a[i] == a[len]) {
			lps[i] = ++len; 
			++i;
		}
		else {
			if(len != 0)
				len = lps[len - 1];
			else {
				lps[i] = 0;
				++i;
			}
		}
	}
}
 
void computeZar() {
	int left = 0, right = 0;
	for(int k = 1; k < a.length(); ++k) {
		if(k > right) {
			left = right = k;
			while(right < a.length() and a[right] == a[right-left])
				++right;
			Zar[k] = right - left;
			--right;
		}
		else {
			int k1 = k - left;
			if(Zar[k1] < right - k + 1)
				Zar[k] = Zar[k1];
			else {
				left = k;
				while(right < a.length() && a[right] == a[right - left])
					++right;
				Zar[k] = right - left;
				--right;
			}
		}
	}
}
 
int main() {
	cin >> a;
	computelps();
	computeZar();
	for(int i = 0; i < a.length(); ++i)
		cout << Zar[i] << ' ';
	cout << '\n';
	for(int i = 0; i < a.length(); ++i)
		cout << lps[i] << ' ';
}
