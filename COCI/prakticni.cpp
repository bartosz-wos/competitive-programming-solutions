#include "bits/stdc++.h"
using namespace std;
#define all(x) begin(x),end(x)
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { string sep; for (const T &x : v) os << sep << x, sep = " "; return os; }
#define debug(a) cerr << "(" << #a << ": " << a << ")\n";
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pi;
const int mxN = 1e5+1, oo = 1e9;
vi adj[mxN];

vi base;
int pref[mxN];
bitset<mxN> vis,mark;
vector<array<int,3>> es;
vector<pi> bad;
void dfs(int at, int from) {
    vis[at]=true;
    mark[at]=true;
    for(auto ei : adj[at]) {
        auto& e = es[ei];
        int to = e[0]^e[1]^at, w= e[2];
        if(to==from) continue;
        if(!vis[to]) {
            pref[to]=pref[at]^w;
            dfs(to,at);
        } else if(mark[to])  {
            // back edge
            int cyc = pref[at]^pref[to]^w;
            bad.push_back({ei,cyc});
            for(auto i : base) cyc = min(cyc,i^cyc);
            if(cyc!=0) base.push_back(cyc);
        }
    }
    mark[at]=false;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m; cin >> n >> m;
    es.resize(m);
    for(int i=0;i<m;++i) {
        auto& [a,b,w] = es[i];
        cin >> a >> b >> w;
        adj[a].push_back(i);
        adj[b].push_back(i);

    }
    dfs(1,0);
    vvi res(base.size());
    sort(all(bad));
    for(auto [i,cyc] : bad) {
        for(int j=0;j<(int)base.size();++j) {
            if((cyc^base[j]) < cyc) {
                cyc ^=base[j];
                res[j].push_back(i+1);
            }
        }
    }
    cout << base.size() << '\n';
    auto it = base.begin();
    for(auto& i : res) {
        cout << *(it++) << ' ';
        cout << i.size() << ' ';
        cout << i << '\n';
    }
}
