#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int constexpr DS = 32768;
vector<ll> vals[DS];
int B;

int ds(ll n) {
    int s = 0;
    while (n) s += n%B, n /= B;
    return s;
}

int main() {
    int C, D, M;
    cin >> C >> D >> B >> M;

    int mx_cnt = 0, mxi = -1;
    for (ll n = 1; mx_cnt < M; n += B-1) {
        int s = ds(C*n+D);
        vals[s].push_back(n);
        if (vals[s].size() > mx_cnt) {
            mx_cnt = vals[s].size();
            mxi = s;
        }
    }

    for (ll const n : vals[mxi]) {
        cout << n << ' ';
    }
    cout << '\n';
}
