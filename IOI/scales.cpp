#include "scales.h"
#include <bits/stdc++.h>
using namespace std;

#define popcount(n) (__builtin_popcountll((n)))
#define clz(n) (__builtin_clzll((n)))
#define ctz(n) (__builtin_ctzll((n)))
#define lg(n) (63 - __builtin_clzll((n)))
#define BIT(n, i) (((n) >> (i)) & 1ll)
#define MASK(i) (1ll << (i))
#define FLIP(n, i) ((n) ^ (1ll << (i)))
#define ON(n, i) ((n) | MASK(i))
#define OFF(n, i) ((n) & ~MASK(i))

#define Int __int128
#define fi first
#define se second

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;
typedef pair<long long, int> pli;
typedef pair<int, long long> pil;
typedef vector<pair<int, int>> vii;
typedef vector<pair<long long, long long>> vll;
typedef vector<pair<long long, int>> vli;
typedef vector<pair<int, long long>> vil;

template <class T1, class T2>
bool maximize(T1 &x, T2 y) {
    if (x < y) {
        x = y;
        return true;
    }
    return false;
}
template <class T1, class T2>
bool minimize(T1 &x, T2 y) {
    if (x > y) {
        x = y;
        return true;
    }
    return false;
}

template <class T>
void remove_duplicate(vector<T> &ve) {
    sort (ve.begin(), ve.end());
    ve.resize(unique(ve.begin(), ve.end()) - ve.begin());
}

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
template <class T> T random(T l, T r) {
    return uniform_int_distribution<T>(l, r)(rng);
}
template <class T> T random(T r) {
    return rng() % r;
}

const int N = 10000 + 5;
const int MOD = 1e9 + 7;
const int inf = 1e9;
const ll INF = 1e18;

int pw[] = {1, 3, 9, 27, 81, 243, 729};
int W[6];

#ifdef hwe
void answer(int W[]) {
    for (int i = 0; i < 6; ++i) cerr << W[i] << ' ';
    cerr << '\n';
}
int getLightest(int a, int b, int c) {
    cerr << "Lightest: " << a << ' ' << b << ' ' << c << '\n';
    int ret; cin >> ret; return ret;
}
int getMedian(int a, int b, int c) {
    cerr << "Median: " << a << ' ' << b << ' ' << c << '\n';
    int ret; cin >> ret; return ret;
}
int getHeaviest(int a, int b, int c) {
    cerr << "Heaviest: " << a << ' ' << b << ' ' << c << '\n';
    int ret; cin >> ret; return ret;
}
int getNextLightest(int a, int b, int c, int d) {
    cerr << "Next Lightest: " << a << ' ' << b << ' ' << c << ' ' << d << '\n';
    int ret; cin >> ret; return ret;
}
#endif

int numNode;
bool done = false;
pii ope[N], child[N][3];
vector<int> candidates[N];

vector<int> to_vec(int num) {
    vector<int> ret;
    while (num > 0) ret.emplace_back(num % 10), num /= 10;
    reverse(ret.begin(), ret.end());
    return ret;
}

int to_num(vector<int> ve) {
    int num = 0;
    for (auto x : ve) num = num * 10 + x;
    return num;
}

bool gen_tree(int node, int depth) {
    // cerr << node << ' ' << depth << ' ' << candidates[node].size() << '\n';
    if (candidates[node].size() > pw[depth]) return false;
    if (depth == 0) return true;

    vector<tuple<int, int, int>> triples;
    for (int i = 1; i <= 4; ++i) for (int j = i + 1; j <= 5; ++j) for (int k = j + 1; k <= 6; ++k)
        triples.emplace_back(i, j, k);
    // shuffle(triples.begin(), triples.end(), rng);
    for (auto it : triples) {
        int x = get<0>(it), y = get<1>(it), z = get<2>(it);
        // cerr << "x, y, z: " << x << ' ' << y << ' ' << z << '\n';
        for (int operation : {0, 1, 2}) {
            // if (done) break;

            int cnt[3]; cnt[0] = cnt[1] = cnt[2] = 0;
            for (auto candidate : candidates[node]) {
                vector<int> ve = to_vec(candidate); pii p[3];
                for (int i = 0; i < 6; ++i) {
                    if (ve[i] == x) p[0] = make_pair(i, 0);
                    if (ve[i] == y) p[1] = make_pair(i, 1);
                    if (ve[i] == z) p[2] = make_pair(i, 2);
                }

                sort (p, p + 3);
                ++cnt[p[operation].se];
            }

            // if (depth == 4) {
            //     int ma = max({cnt[0], cnt[1], cnt[2]});
            //     cerr << "Max: " << ma << '\n';
            //     if (ma == 28) cerr << cnt[0] << ' ' << cnt[1] << ' ' << cnt[2] << '\n';
            // }
            if (max({cnt[0], cnt[1], cnt[2]}) > pw[depth - 1]) continue;
            
            child[node][0] = make_pair(++numNode, x);
            child[node][1] = make_pair(++numNode, y);
            child[node][2] = make_pair(++numNode, z);

            for (auto candidate : candidates[node]) {
                vector<int> ve = to_vec(candidate); pii p[3];
                for (int i = 0; i < 6; ++i) {
                    if (ve[i] == x) p[0] = make_pair(i, 0);
                    if (ve[i] == y) p[1] = make_pair(i, 1);
                    if (ve[i] == z) p[2] = make_pair(i, 2);
                }

                sort (p, p + 3);
                candidates[child[node][p[operation].se].fi].emplace_back(candidate);
            }

            bool flag = true;
            for (int i = 0; i < 3; ++i) flag &= gen_tree(child[node][i].fi, depth - 1);

            if (flag) {
                ope[node] = make_pair(operation, -1);
                return true;
            }
        }
    }

    for (auto it : triples) {
        int x = get<0>(it), y = get<1>(it), z = get<2>(it);
        // cerr << "x, y, z: " << x << ' ' << y << ' ' << z << '\n';
        vector<bool> mark(7, false); mark[x] = mark[y] = mark[z] = true;
        vector<int> remains;
        for (int i = 1; i <= 6; ++i) if (!mark[i]) remains.emplace_back(i);
        for (auto d : remains) {
            int cnt[3]; cnt[0] = cnt[1] = cnt[2] = 0;
            // cerr << "d: " << d << '\n';
            for (auto candidate : candidates[node]) {
                vector<int> ve = to_vec(candidate); pii p[4];
                for (int i = 0; i < 6; ++i) {
                    if (ve[i] == x) p[0] = make_pair(i, 0);
                    if (ve[i] == y) p[1] = make_pair(i, 1);
                    if (ve[i] == z) p[2] = make_pair(i, 2);
                    if (ve[i] == d) p[3] = make_pair(i, 3);
                }

                // cerr << '\n';
                // for (int i = 0; i < 4; ++i) cerr << p[i].fi << ' ' << p[i].se << ' ';
                // cerr << '\n';
                sort (p, p + 4);

                if (p[3].se == 3) ++cnt[p[0].se];
                else for (int i = 1; i < 4; ++i) if (p[i - 1].se == 3) ++cnt[p[i].se];
            }

            // int ma = max({cnt[0], cnt[1], cnt[2]});
            // cerr << "MAX: " << ma << '\n';
            if (max({cnt[0], cnt[1], cnt[2]}) > pw[depth - 1]) continue;

            child[node][0] = make_pair(++numNode, x);
            child[node][1] = make_pair(++numNode, y);
            child[node][2] = make_pair(++numNode, z);

            for (auto candidate : candidates[node]) {
                vector<int> ve = to_vec(candidate); pii p[4];
                for (int i = 0; i < 6; ++i) {
                    if (ve[i] == x) p[0] = make_pair(i, 0);
                    if (ve[i] == y) p[1] = make_pair(i, 1);
                    if (ve[i] == z) p[2] = make_pair(i, 2);
                    if (ve[i] == d) p[3] = make_pair(i, 3);
                }

                sort (p, p + 4);

                if (p[3].se == 3) candidates[child[node][p[0].se].fi].emplace_back(candidate);
                else for (int i = 1; i < 4; ++i) 
                    if (p[i - 1].se == 3) candidates[child[node][p[i].se].fi].emplace_back(candidate);
            }

            bool flag = true;
            for (int i = 0; i < 3; ++i) flag &= gen_tree(child[node][i].fi, depth - 1);

            if (flag) {
                ope[node] = make_pair(3, d);
                return true;
            }
        }
    }

    // cerr << "Dac: " << node << ' ' << depth << '\n';
    return false;
}

void init(int t) {
    vector<int> p = {1, 2, 3, 4, 5, 6};
    done = false, numNode = 0;

    do {
        candidates[0].emplace_back(to_num(p));
    } while (next_permutation(p.begin(), p.end()));

    gen_tree(0, 6);
}

void orderCoins() {
    int current_node = 0;

    auto play = [&]() {
        int tmp, x = child[current_node][0].se, y = child[current_node][1].se, z = child[current_node][2].se;
        int flag = ope[current_node].fi;
        if (flag == 0) tmp = getLightest(x, y, z);
        else if (flag == 1) tmp = getMedian(x, y, z);
        else if (flag == 2) tmp = getHeaviest(x, y, z);
        else tmp = getNextLightest(x, y, z, ope[current_node].se);

        if (tmp == x) return 0;
        if (tmp == y) return 1;
        return 2;
    };

    while (true) {
        if (candidates[current_node].size() == 1) {
            vector<int> ve = to_vec(candidates[current_node][0]);
            for (int i = 0; i < 6; ++i) W[i] = ve[i];
            answer(W);
            return;
        }

        // if (child[current_node][0].fi == 0) {
        //     cerr << "All candidates:\n";
        //     for (auto candidate : candidates[current_node]) {
        //         vector<int> ve = to_vec(candidate);
        //         for (auto &x : ve) cerr << x << ' ';
        //         cerr << '\n';
        //     }
        // }

        int tmp = play(); current_node = child[current_node][tmp].fi;
    }
}

signed main() {
    init(0);

    orderCoins();

    cerr << '\n'; return 0;
}
