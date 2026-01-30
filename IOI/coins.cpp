#include "coins.h"
#include <bits/stdc++.h>
using namespace std;

vector<int> coin_flips(vector<int> b,int c) {
    int xr = 0;
    for (int i = 0;i<64;i++) if (b[i])xr^=i;
    vector<int> a;a.push_back(xr^c);
    return a;
}

int find_coin(vector<int> b) {
    int xr = 0;
    for (int i = 0;i<64;i++) if (b[i]) xr^=i;
    return xr;
}

