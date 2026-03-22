#include "bits/stdc++.h"
#include <ext/pb_ds/tree_policy.hpp>
#define fast ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(NULL);
#define int long long
#define ll long long
#define ld long double
#define x first
#define y second
using namespace __gnu_pbds;
using namespace std;

template<class T> bool ckmax(T& a, const T& b){
    return a < b ? a = b, 1 : 0;
}

void DBG() { cerr << "]" << endl; }
template <class H, class... T>
void DBG(H h, T... t){
    cerr << h;
    if (sizeof...(t))
        cerr << ", ";
    DBG(t...);
}

const int N = 1e6 + 5;
const int mod = 1000000007;
const int INF = 1e9;
const double eps = 1e-5;
const double PI = acos(-1);

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int stor[1<<20][20], id = 1;
vector<int> arr;
int n;
int p;

int add(int a, int b) {
    return (a + b) % p;
}

int mul(int a, int b) {
    return (a * b) % p;
}

int comb(int a, int b) {
    return mul(a, b);
}

void build(int l, int r, int ind) {
    if (ind < 0) return;
    int m = (l + r) / 2;
    int prod = id;
    for (int i = m - 1; i >= l; i--)
        stor[i][ind] = prod = comb(arr[i], prod);
    prod = id;
    for (int i = m; i < r; i++)
        stor[i][ind] = prod = comb(prod, arr[i]);
    build(l, m, ind - 1);
    build(m, r, ind - 1);
}

void init() {
    n = 1;
    while ((1 << n) < arr.size()) ++n;
    arr.resize(1 << n);
    build(0, (1 << n), n - 1);
}


int query(int l, int r) {
    if (l == r) return arr[l];
    int t = 31 - __builtin_clz(r ^ l);
    return comb(stor[l][t], stor[r][t]);
}

void solve(int tc){
    int n, q;
    cin >> n >> p >> q;
    arr.resize(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    init();
    vector<int> brr;
    for (int i = 0,x; i < q / 64 + 2; i++){
        cin >> x;
        brr.push_back(x);
    }

    int l=0, r=0, x = 0;
    for (int i = 0; i < q; i++) {
        if (i % 64 == 0) l = (brr[i / 64] + x) % n, r = (brr[i / 64 + 1] + x) % n;
        else l = (l + x) % n, r = (r + x) % n;
        if (l > r) swap(l, r);
        x = add(query(l, r), 1);
    }
    cout << x << '\n';
}

int32_t main(){
    fast;
    int tc = 1;
    cin >> tc;
    for (int tt = 1; tt <= tc; tt++){
        solve(tt);
    }
    return 0;
}
