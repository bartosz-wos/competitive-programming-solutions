#include "Alice.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<pair<int, int>> Alice() {
	const int kN = 5000;
	ll x = setN(kN);
	vector<pair<int, int>> edg;
	for(int i = 1; i < kN; i++) {
		edg.emplace_back(x % i + 1, i + 1);
	}
	return edg;
}

