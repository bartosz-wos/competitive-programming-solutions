#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>

using namespace std;

const int inf = 1e9;
const int maxn = 1e5 + 2;

int ans = inf;

struct RECTANGLE {
    int x1,y1,x2,y2;
    RECTANGLE() {}
    RECTANGLE(int x1, int y1, int x2, int y2) : x1(x1), x2(x2), y1(y1), y2(y2) {}
    bool operator < (RECTANGLE a) {
        return x2 < a.x2;
    }
    void print() {
        cout << "REC:: " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
    }
};

int T[maxn][2];
RECTANGLE rec[maxn];
pii trace[maxn][2];

void solve() {
    int X,Y; cin >> X >> Y;
    int n; cin >> n;
    int sz = 0;
    for (int i = 1; i <= n; i++) {
        int x1,y1,x2,y2; cin >> x1 >> y1 >> x2 >> y2;
        if (max(x1,x2) >= X) continue;

        rec[++sz] = RECTANGLE(min(x1,x2),min(y1,y2),max(x1,x2),max(y1,y2));
        T[sz][0] = T[sz][1] = inf;
    }
    sort(rec + 1, rec + sz + 1);
    set<pii> st;
    rec[sz+1] = {X,Y,X,Y};
    rec[0] = {0,0,0,0};
    st.insert({Y,sz + 1});
    for (int i = sz; i >= 1; i--) {
        set<pii>::iterator p = st.lower_bound({rec[i].y1,-inf});
//        cerr << i << " ";
//        rec[i].print();
        while (p!=st.end() && p->first <= rec[i].y2) {
            int type = (p->second > 0);
            int id = abs(p->second);

            if (T[i][0] >  rec[id].x2 - rec[i].x2 + abs(rec[i].y1 - p->first) + T[id][type]+ 1) {
                T[i][0] = rec[id].x2 - rec[i].x2 + abs(rec[i].y1 - p->first) + T[id][type] + 1;
                trace[i][0] = {id, type};
            }
            if (T[i][1] >  rec[id].x2 - rec[i].x2 + abs(rec[i].y2 - p->first) + T[id][type] + 1) {
                T[i][1] = rec[id].x2 - rec[i].x2 + abs(rec[i].y2 - p->first) + T[id][type] + 1;
                trace[i][1] = {id, type};
            }
            p++;
            st.erase(prev(p));
        }
        if (T[i][0] != inf) st.insert({rec[i].y1 - 1, -i});
        if (T[i][1] != inf) st.insert({rec[i].y2 + 1, i});
    }

    for (pii tmp : st) {
        int pos,id; tie(pos,id) = tmp;
        int type = (id > 0);
        id = abs(id);
        if (ans > T[id][type] + abs(pos) + rec[id].x2) {
            ans = T[id][type] + abs(pos) + rec[id].x2;
            trace[0][0] = {id,type};
        }
    }
    vector<pii> re,out;
    cout << ans << '\n';
    int id=0,type=0;
    while (trace[id][type].first <= sz) {
        int nid, ntype;  tie(nid,ntype) = trace[id][type];
        if (id) {
            re.push_back({0,((ntype) ? (rec[nid].y2+1) : (rec[nid].y1-1)) - ((type) ? (rec[id].y2+1) : (rec[id].y1-1))});
            re.push_back({rec[nid].x2 - rec[id].x2,0});
        }
        else {
            re.push_back({0,(ntype) ? (rec[nid].y2+1) : (rec[nid].y1-1)});
            re.push_back({rec[nid].x2 + 1,0});
        }

        id = nid;
        type = ntype;
    }
    if (id) {
        re.push_back({0,Y - ((type) ? (rec[id].y2+1) : (rec[id].y1-1))});
        re.push_back({X - rec[id].x2 - 1,0});
    }
    else {
        re.push_back({0,Y});
        re.push_back({X,0});
    }
    for (pii tmp : re) {
        if (tmp != make_pair(0,0)) out.push_back(tmp);
    }
    cout << out.size() << '\n';
    for (pii tmp : out) {
        cout << tmp.first << " " << tmp.second << '\n';
    }

}

signed main() {
    cin.tie(0) -> sync_with_stdio(0);
    solve();
    return 0;
}

