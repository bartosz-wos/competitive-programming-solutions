#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);
typedef long long ll;
typedef double du;
using namespace std;
const ll N = 5e5 + 5, M = 1e7 + 10, mod = 1e9 + 7, mod1 = 1e9 + 11, LOG = 20;

ll k, ans = 1e17;

/// Trie
struct Node {
    ll ch[2]{}, mn = 1e17, sz{};

    ll &operator[](ll x) {
        return ch[x];
    }
};

struct BT {
    vector<Node> trie;

    int newNode() {
        return trie.emplace_back(), trie.size() - 1;
    }

    BT() { newNode(); }

    void insert(ll x, ll idx, ll op) {
        ll u = 0;
        for (int i = 30; ~i; --i) {
            trie[u].mn = min(trie[u].mn, idx);
            ll v = x >> i & 1;
            if (!trie[u][v])
                trie[u][v] = newNode();
            u = trie[u][v];
            trie[u].sz += op;
        }
        trie[u].mn = min(trie[u].mn, idx);
    }

    ll query(ll x) {
        ll u = 0, res{};
        for (int i = 30; ~i; --i) {
            ll b = x >> i & 1, best = trie[u][!b];
            if (trie[best].sz) {
                ll tmp = res | (1 << i);
                if(tmp >= k) {
                    ans = min(ans, trie[best].mn);
                    u = trie[u][b];
                }else
                    res = tmp, u = best;
            } else
                u = trie[u][b];
        }
        return res;
    }
} bt;


void solve(){
    ll n, curr{}, y; cin >> n >> k;
    ll idx{}, mx_len{};
    bt.insert(0, 0, 1);
    for (int i = 1; i <= n; ++i) {
        cin >> y;
        curr ^= y;
        ans = 1e17;
        bt.query(curr);
        ll len = i - ans;
        if(len > mx_len)
            mx_len = len, idx = ans + 1;
        else if(len == mx_len)
            idx = min(idx, 1ll * i);
        bt.insert(curr, i, 1);
    }
    cout << idx << ' ' << mx_len;
}


int main() {
    fast
    ll t = 1;
    // cin >> t;
    while (t--) {
        solve();
        cout << '\n';
    }
}

