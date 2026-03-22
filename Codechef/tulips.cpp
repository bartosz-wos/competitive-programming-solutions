#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;
typedef complex<ld> P;
#define F first
#define S second
#define pb push_back
#define len(x) (int)x.length()
#define siz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define ms(x, a) memset(x, a, sizeof(x))
#define deb(...) logger(#__VA_ARGS__, __VA_ARGS__)
template<typename ...Args>
void logger(string vars, Args&&... values){
    cout << vars << " = ";
    string delim = "";
    (...,(cout << delim << values, delim = ", "));
    cout << endl;
}
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3f;
const ld pie = acos(-1.0);
const int MOD = 1e9+7;

const int MAX = 8e5+5;

pi adj[MAX];

struct Node{ int mn, cnt, lz; } st[MAX];

int p[MAX], in[MAX], sub[MAX], val[MAX] = {INF}, pp[20][MAX], day[MAX], ql[MAX], qr[MAX], res[MAX], curr, tim;

int findP(int x){ return !p[x]? x : p[x] = findP(p[x]); }

void unite(int a, int b, int w){
    a = findP(a), b = findP(b);
    if (a == b) return;
    p[a] = p[b] = ++curr;
    val[curr] = w;
    adj[curr] = {a, b};
}

int dfs(int v){
    in[v] = ++tim;
    if (adj[v].F) pp[0][adj[v].F] = pp[0][adj[v].S] = v;
    return sub[v] = 1+(adj[v].F? dfs(adj[v].F)+dfs(adj[v].S) : 0);
}

void init(int i, int l, int r){
    st[i] = {1, r-l+1, 0};
    if (l == r) return;
    int m = l+(r-l)/2;
    init(2*i, l, m); init(2*i+1, m+1, r);
}

void prop(int i, int l, int r){
    if (!st[i].lz) return;
    st[i].mn += st[i].lz;
    if (l != r) st[2*i].lz += st[i].lz, st[2*i+1].lz += st[i].lz;
    st[i].lz = 0;
}

void update(int i, int l, int r, int tl, int tr, int val){
    prop(i, l, r);
    if (l > tr || r < tl) return;
    if (tl <= l && r <= tr){
        st[i].lz += val;
        prop(i, l, r);
        return;
    }
    int m = l+(r-l)/2;
    update(2*i, l, m, tl, tr, val);
    update(2*i+1, m+1, r, tl, tr, val);
    st[i] = {min(st[2*i].mn, st[2*i+1].mn), 0, st[i].lz};
    if (st[2*i].mn == st[i].mn) st[i].cnt += st[2*i].cnt;
    if (st[2*i+1].mn == st[i].mn) st[i].cnt += st[2*i+1].cnt;
}

pi query(int i, int l, int r, int tl, int tr){
    prop(i, l, r);
    if (l > tr || r < tl) return {INF, 0};
    if (tl <= l && r <= tr) return {st[i].mn, st[i].cnt};
    int m = l+(r-l)/2;
    auto x = query(2*i, l, m, tl, tr), y = query(2*i+1, m+1, r, tl, tr);
    if (x.F < y.F) return x;
    if (x.F > y.F) return y;
    return {x.F, x.S+y.S};
}

void solve(){
    for (int i = 0; i < MAX; i++){
        adj[i] = {0, 0};
        st[i] = {0, 0, 0};
    }
    ms(p, 0); ms(in, 0); ms(sub, 0); ms(val, 0); val[0] = INF; ms(pp, 0); tim = 0;
    int n; cin >> n;
    vector<Node> e;
    for (int i = 1; i < n; i++){
        int a, b, w; cin >> a >> b >> w;
        e.pb({a, b, w});
    }
    sort(all(e), [](const Node &x, const Node &y){ return x.lz < y.lz; });
    curr = n;
    for (auto[a, b, w]: e) unite(a, b, w);
    dfs(curr);
    int lg = 0;
    for (int i = 1; 1<<i <= curr; i++){
        lg = i;
        for (int j = 1; j <= curr; j++) pp[i][j] = pp[i-1][pp[i-1][j]];
    }
    init(1, 1, curr);
    for (int i = 1; i <= n; i++) update(1, 1, curr, in[i], in[i], -1);
    int q, dis; cin >> q >> dis;
    for (int i = 1; i <= q; i++){
        cin >> day[i] >> ql[i] >> qr[i];
        for (int j = lg; j >= 0; j--){
            if (val[pp[j][ql[i]]] <= qr[i]) ql[i] = pp[j][ql[i]];
        }
        qr[i] = in[ql[i]]+sub[ql[i]]-1;
        ql[i] = in[ql[i]];
    }
    int ind = q;
    for (int i = q; i; i--){
        while (ind && day[i]-day[ind] < dis){
            update(1, 1, curr, ql[ind], qr[ind], 1);
            ind--;
        }
        update(1, 1, curr, ql[i], qr[i], -1);
        auto ret = query(1, 1, curr, ql[i], qr[i]);
        res[i] = (ret.F? 0 : ret.S);
    }
    for (int i = 1; i <= q; i++) cout << res[i] << "\n";
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t; while (t--) solve();

}
