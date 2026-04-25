#include "bits/stdc++.h"
 
using namespace std;
 
#define forR(i, x) for(int i = 0; i < x; ++i)
#define REP(i, a, b) for(int i = (a); i < (b); ++i)
#define all(i) i.begin(), i.end()
#define boost() cin.sync_with_stdio(0); cin.tie()
typedef long long ll;
struct pii{int a, b;};
const int MN = 1e5 + 10;
typedef vector<vector<int>> vvi;
typedef vector<int> vi;
typedef vector<bool> vb;
 
void tarjan(int c, vvi& adj, vi& dfn, vi& mi, int& cdfn, vi& stk, vb& ist, vb& vis, vvi& scc, vi& gi) {
    assert(!vis[c]);
    vis[c] = true;
    stk.push_back(c); ist[c] = true;
    mi[c] = dfn[c] = cdfn++;
    for(int i : adj[c]) {
        if(!vis[i]) {
            tarjan(i, adj, dfn, mi, cdfn, stk, ist, vis, scc, gi);
            mi[c] = min(mi[c], mi[i]);
        } else if(ist[i]) {
            mi[c] = min(mi[c], dfn[i]);
        }
    }
    if(mi[c] == dfn[c]) {
        scc.emplace_back();
        int cur;
        do{
            cur = stk.back();
            stk.pop_back(); ist[cur] = false;
            scc.back().push_back(cur);
            gi[cur] = (int) scc.size() - 1;
        } while(cur != c);
    }
}
 
vvi tarjan(int n, vvi& adj, vi& gi) {
    vi dfn(n, 0), mi(n, 0), stk;
    vb ist(n, false), vis(n, false);
    vvi scc;
    int cdfn=1;
    forR(i, n) if(!vis[i]) {
        assert(stk.empty());
        tarjan(i, adj, dfn, mi, cdfn, stk, ist, vis, scc, gi);
        assert(stk.empty());
    }
    return scc;
}
 
int INF = 1e8;
 
vector<pii> toSCC(int n, vvi adj) {
    vi idg(n), odg(n);
    forR(i, n) for(int j : adj[i]) {
        ++odg[i], ++idg[j];
    }
    if(n == 1) return {};
 
    int ni0=0, no0=0;
    forR(i, n) {
        ni0 += idg[i] == 0;
        no0 += odg[i] == 0;
    }
 
    vector<pii> ans;
 
    vi mx(n, INF), my(n, INF);
    forR(i, n){
        if(idg[i] == 0) mx[i] = i;
        for(int j : adj[i]) mx[j] = min(mx[j], mx[i]);
    }
    for(int i =  n-1; i >= 0; --i) {
        if(odg[i] == 0) my[i] = i;
        else {
            for(int j : adj[i]) my[i] = min(my[i], my[j]);
        }
    }
 
    vector<pii> pos;
    forR(i, n) {
        if(idg[i] == 0) pos.push_back({i, my[i]});
        if(odg[i] == 0) pos.push_back({mx[i], i});
    }
    
    vector<pii> tbl;
    vb icy(n, false);
    for(auto [a, b] : pos) if(!icy[a] && !icy[b]) {
        tbl.push_back({a, b});
        icy[a] = icy[b] = true;
    }
 
    forR(i, (int) tbl.size() - 1) ans.push_back({tbl[i].b, tbl[i+1].a});
    ans.push_back({tbl.back().b, tbl.front().a});
 
    vi tp, bt;
    vb tPath(n, false);
    forR(i, n){
        if(idg[i] == 0 && !icy[i]) tp.push_back(i);
        if(odg[i] == 0 && !icy[i]) bt.push_back(i);
        assert(icy[i] || idg[i] > 0 || odg[i] > 0);
    }
 
    forR(i, min(tp.size(), bt.size())) ans.push_back({bt[i], tp[i]});
    REP(i, bt.size(), tp.size()) ans.push_back({tbl[0].b, tp[i]});
    REP(i, tp.size(), bt.size()) ans.push_back({bt[i], tbl[0].a});
 
    assert(ans.size() == max(ni0, no0));
    return ans;
}
 
signed main(){
    int n, m; cin >> n >> m;
    vvi adj(n);
    forR(g, m) {
        int a, b; cin >> a >> b;
        adj[a-1].push_back(b-1);
    }
    vi gi(n);
    vvi scc = tarjan(n, adj, gi);
    reverse(all(scc));
    forR(i, n) gi[i] = (int) scc.size() - 1 - gi[i];
 
    vvi sccAdj(scc.size());
    forR(i, n) for(int j : adj[i]) if(gi[i] != gi[j]) {
        sccAdj[gi[i]].push_back(gi[j]);
    }
 
    vector<pii> sccAdd = toSCC(scc.size(), sccAdj);
    for(auto [a, b] : sccAdd) sccAdj[a].push_back(b);
    
    vi lastGI(scc.size());
    assert(tarjan(scc.size(), sccAdj, lastGI).size() == 1);
 
    cout << sccAdd.size() << '\n';
    for(auto [a, b] : sccAdd) cout << scc[a][0] + 1 << ' ' << scc[b][0] + 1 << '\n';
}
