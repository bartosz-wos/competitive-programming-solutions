#include <bits/stdc++.h>
using namespace std;
#define ios ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define ll long long
#define int long long
#define ld long double
#define all(x) x.begin(),x.end()
#define mem(x, y) memset(x,y,sizeof x)

#define endl '\n'

const int dx8[8] = {0, 0, 1, -1, 1, -1, -1, 1};
const int dy8[8] = {1, -1, 0, 0, 1, -1, 1, -1};
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
char direction[4] = {'r', 'l', 'd', 'u'};


const int inf = 1e9 + 5, N = 1e5 + 5, M = 5e3 + 1, MAX_X = 2001, LG = 15, mod =
                1e9 + 7, p1 = 31, p2 = 37, SQ = 470;
const ll LLinf = 8e18;

// if minimum query must enter query in descending order
// if maximum query must enter query in increasing order
class PersistentCHT {
private:
    struct Line {
        int a, b;

        double intersectX(const Line &other) const {
            return (other.b - b) * 1.0 / (a - other.a);
        }

        int eval(const int &x) {
            return a * x + b;
        }
    };

    int top = 0, n;
    vector<Line> hull;
    stack<pair<pair<int, int>, Line> > st;

    void build() {
        hull.resize(n + 7, {0, 0});
    }

    bool isRedundant(const Line &pre, const Line &cur, const Line &nex) {
        return (cur.intersectX(pre) <= nex.intersectX(cur));
    }

    void add_line(const int &a, const int &b) {
        // for maximum
        // a*=-1;
        //b*=-1;
        int l = 1, r = top - 1, ans = top;
        Line cur = {a, b};
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (isRedundant(cur, hull[mid], hull[mid - 1])) {
                ans = mid;
                r = mid - 1;
            } else l = mid + 1;
        }
        st.push({{ans, top}, hull[ans]});
        top = ans + 1;
        hull[ans] = cur;
    }

    int get_query(const int &x) {
        int l = 0, r = top - 1;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (hull[mid].eval(x) >= hull[mid + 1].eval(x)) l = mid + 1;
            else r = mid;
        }
        // return -hull[l].eval(x); //for maximum
        return hull[l].eval(x);
    }

    void rollback() {
        assert(!st.empty());
        int pos = st.top().first.first;
        top = st.top().first.second;
        Line cur = st.top().second;
        hull[pos] = cur;
        st.pop();
    }

public:
    void build(int _n) {
        n = _n;
        build();
    }

    void add(const int &a, const int &b) {
        add_line(a, b);
    }

    int get(const int &x) {
        return get_query(x);
    }

    void roll() {
        rollback();
    }
} pcht;


vector<pair<int, ll> > adj[N], Harbingers(N);
ll dist[N], dp[N];
int root[N];

void dfs(int node, int p = 0) {
    if (node) {
        dp[node] = Harbingers[node].first + Harbingers[node].second * dist[node];
        dp[node] += pcht.get(Harbingers[node].second);
    }
    pcht.add(-dist[node], dp[node]);
    for (auto [v,w]: adj[node]) {
        if (v == p) continue;
        dist[v] = dist[node] + w;
        dfs(v, node);
    }
    pcht.roll();
}

void solve() {
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v, d;
        cin >> u >> v >> d;
        u--, v--;
        adj[u].push_back({v, d});
        adj[v].push_back({u, d});
    }
    for (int i = 1; i < n; ++i) {
        int s, v;
        cin >> s >> v;
        Harbingers[i] = {s, v};
    }
    pcht.build(n);
    dfs(0);
    for (int i = 1; i < n; ++i) cout << dp[i] << " ";
}

signed main(){
    ios
    cout << fixed << setprecision(10);
    int tc = 1;
    // cin >> tc;

    while (tc--) {
        solve();
    }
}
