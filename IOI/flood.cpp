#include <bits/stdc++.h>
#define ll long long
#define all(x) x.begin(), x.end()
#define Neco "flood"
#define resp(x) sort(all(x)), x.resize(unique(all(x)) - x.begin())
#define getbit(x,i) ((x >> i)&1)
#define _left id * 2, l, mid
#define _right id * 2 + 1, mid + 1, r
#define cntbit(x) __builtin_popcountll(x)
#define fi(i, a, b) for(int i = a; i <= b; i++)
#define fid(i, a, b) for(int i = a; i >= b; i--)
#define maxn (int) 2e5 + 7

using namespace std;

const ll mod = 1e9 + 7; //972663749
const ll base = 911382323;
const vector<int> prio = {1, 0, 3, 2};


int n, m;
int d[maxn], del[maxn];
struct dl {
    pair<int, int> coord;
    int id;
} point[maxn];
int ID[maxn];
vector<pair<int, int>> edges[maxn];

void create_edge(int i, int j, int id) {
    int x, y, u, v;
    tie(x, y) = point[i].coord, tie(u, v) = point[j].coord;
    pair<int, int> val = {j, id};

    if(x == u) {
        if(v > y) edges[i][0] = val;
        else edges[i][2] = val;
    }

    if(y == v) {
        if(u > x) edges[i][3] = val;
        else edges[i][1] = val;
    }
}

bool check(int u) {
    for(auto [v, id] : edges[u]) if(!del[id]) return 1;
    return 0;
}

void dfs(int u)
{
    int rt = u, dir = 0;
    vector<int> visited_edges;

    do {
        pair<int, int> v;
        for(int t : prio) {
            v = edges[u][(dir + t) % 4];
            if(!del[v.second]) {
                dir = (dir + t) % 4;
                break;
            }
        }

//        cout << u << " " << v.first << " " << dir << '\n';

        visited_edges.push_back(v.second);
        u = v.first;

    } while(u != rt);

    for(int x : visited_edges) d[x] ++, del[x] = 1;
}

void solve()
{
    cin >> n;
    fi(i, 1, n) {
        cin >> point[i].coord.first >> point[i].coord.second;
        point[i].id = i;
        edges[i].resize(4);
    }

    sort(point + 1, point + 1 + n, [](dl x, dl y) {
            return x.coord < y.coord;
        });

    fi(i, 1, n) ID[point[i].id] = i;

    cin >> m;
    fi(i, 1, m) {
        int x, y; cin >> x >> y;

        x = ID[x], y = ID[y];
        create_edge(x, y, i);
        create_edge(y, x, i);
    }

    del[0] = 1;
    fi(i, 1, n) {
        while(check(i)) dfs(i);
    }

    vector<int> ans;
    fi(i, 1, m) if(d[i] == 2) ans.push_back(i);

    cout << ans.size() << '\n';
    for(int x : ans) cout << x << '\n';

}


int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    if(fopen(Neco".inp", "r")) {
        freopen(Neco".inp", "r", stdin);
        freopen(Neco".out", "w", stdout);
    }


    int nTest = 1;
//    cin >> nTest;


    while(nTest--)
    {
        solve();
    }


    return 0;
}

