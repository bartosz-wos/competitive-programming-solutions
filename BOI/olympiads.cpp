#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
template <class T, class... U> void bug_h(const T& t, const U&... u) { cerr << t; ((cerr << " | " << u), ...); cerr << endl; }
#define bug(...) cerr << "L" << __LINE__ << " [" << #__VA_ARGS__ << "]: ", bug_h(__VA_ARGS__)
#else
#define cerr if (0) cerr
#define bug(...)
#endif

#define ar array
#define all(v) std::begin(v), std::end(v)
#define sz(v) int(std::size(v))
typedef long long i64;
typedef vector<int> vi;
typedef pair<int, int> pi;

using vb = vector<bool>;

int N, K, C;

struct event {
    int who, type, score;
    bool operator<(const event e) const {
        return score > e.score;
    }
};

vector<event> ev;

struct node {
    vb ban; vi use;
    int fix, score;
    node(vb ban, int fix) : ban(ban), fix(fix) {
        vb cover(K); int covered = 0;
        exchange(use, {}), score = 0;
        for (int i = 0; i < sz(ev) && covered < K && sz(use) < K; i++) {
            if (ban[ev[i].who] || cover[ev[i].type]) continue;
            score += ev[i].score;
            cover[ev[i].type] = 1, covered++;
            if (find(all(use), ev[i].who) == end(use)) use.push_back(ev[i].who);
        }
        for (int i = 0; i < sz(ev) && sz(use) < K; i++) {
            if (ban[ev[i].who]) continue;
            if (find(all(use), ev[i].who) == end(use)) use.push_back(ev[i].who);
        }
        // for (int x : use) cout << x << ' ';
        // cout << "=> " << score << endl;
    }
    bool operator<(const node v) const {
        return score < v.score;
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> N >> K >> C;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            int v;
            cin >> v;
            ev.push_back({i, j, v});
        }
    }
    sort(all(ev));
    priority_queue<node> pq;
    pq.push(node(vb(N), 0));
    while (sz(pq)) {
        auto v = pq.top(); pq.pop();
        bug(v.score);
        if (--C == 0) {
            cout << v.score << '\n';
            return 0;
        }
        while (v.fix < K) {
            auto ban = v.ban; ban[v.use[v.fix]] = 1;
            node u(ban, v.fix);
            if (sz(u.use) == K) pq.push(u);
            v.fix++;
        }
    }
    cout << "-1\n";
}
