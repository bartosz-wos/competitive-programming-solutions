#include <bits/stdc++.h>

using i64 = long long;
constexpr int Pool = 2e7;

struct Tag {
    int add = 0, madd = 0, delta = 0;
    void apply(const Tag &y) {
        if (madd == add + y.madd) {
            delta += y.delta;
        } else if (add + y.madd < madd) {
            madd = add + y.madd;
            delta = y.delta;
        }
        add += y.add;
    }
};
struct Info {
    int mn = 1e9, len = 0;
    i64 ans = 0;
    void apply(const Tag &y) {
        if (mn + y.madd == 0) {
            ans += 1ll * len * y.delta;
        }
        mn += y.add;
    }
};
Info operator+(const Info &a, const Info &b) {
    Info c{};
    c.mn = std::min(a.mn, b.mn);
    c.len = a.len * (a.mn == c.mn) + b.len * (b.mn == c.mn);
    c.ans = a.ans + b.ans;
    return c;
}

struct Node {
    Node *l, *r;
    Info s;
    Tag t;
};
Node pool[Pool], *ptr = pool;
Node *newNode(const Node &x) {
    *++ptr = x;
    return ptr;
}
void pull(Node *u) {
    u->s = u->l->s + u->r->s;
}
void apply(Node *u, const Tag &x) {
    u->s.apply(x);
    u->t.apply(x);
}
void push(Node *u) {
    u->l = newNode(*u->l);
    apply(u->l, u->t);
    u->r = newNode(*u->r);
    apply(u->r, u->t);
    u->t = Tag{};
}
template <typename F>
Node *build(int n, F &&f) {
    auto build = [&](auto self, int l, int r) -> Node * {
        Node *u = newNode(Node{nullptr, nullptr, Info{}, Tag{}});
        u->s.mn = 0;
        u->s.len = f(l, r);
        if (r - l > 1) {
            int m = (l + r) / 2;
            u->l = self(self, l, m);
            u->r = self(self, m, r);
            pull(u);
        }
        return u;
    };
    return build(build, 0, n);
}
void rangeApply(Node *u, int l, int r, int ql, int qr, const Tag &x) {
    if (r <= ql || qr <= l) {
        return;
    }
    if (ql <= l && r <= qr) {
        apply(u, x);
        return;
    }
    int m = (l + r) / 2;
    push(u);
    rangeApply(u->l, l, m, ql, qr, x);
    rangeApply(u->r, m, r, ql, qr, x);
    pull(u);
}
Info rangeQuery(Node *u, int l, int r, int ql, int qr) {
    if (r <= ql || qr <= l) {
        return Info{};
    }
    if (ql <= l && r <= qr) {
        return u->s;
    }
    int m = (l + r) / 2;
    Info res = rangeQuery(u->l, l, m, ql, qr) + rangeQuery(u->r, m, r, ql, qr);
    res.apply(u->t);
    return res;
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int _r, _c, n, q, V;
    std::cin >> _r >> _c >> n >> q >> V;

    std::vector<std::tuple<int, int, int, int>> s;
    std::vector<int> vx{0, V - 1}, vy{0, V - 1};
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        std::tie(x1, x2) = std::minmax({x1, x2});
        std::tie(y1, y2) = std::minmax({y1, y2});
        s.emplace_back(x1, y1, x2, y2);
        vx.push_back(x1);
        vy.push_back(y1);
        vx.push_back(x2);
        vy.push_back(y2);
    }

    std::sort(vx.begin(), vx.end());
    vx.erase(std::unique(vx.begin(), vx.end()), vx.end());
    std::sort(vy.begin(), vy.end());
    vy.erase(std::unique(vy.begin(), vy.end()), vy.end());

    std::vector<std::vector<std::tuple<int, int, int>>> mdf(vx.size());
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        std::tie(x1, y1, x2, y2) = s[i];
        x1 = std::lower_bound(vx.begin(), vx.end(), x1) - vx.begin();
        y1 = std::lower_bound(vy.begin(), vy.end(), y1) - vy.begin();
        x2 = std::lower_bound(vx.begin(), vx.end(), x2) - vx.begin();
        y2 = std::lower_bound(vy.begin(), vy.end(), y2) - vy.begin();
        mdf[x1].emplace_back(y1, y2, 1);
        mdf[x2].emplace_back(y1, y2, -1);
    }

    const int m = int(vy.size()) - 1;
    std::vector<Node *> root(vx.size() + 1);
    root[0] = build(m, [&](int l, int r) {
        return vy[r] - vy[l];
    });
    for (int i = 0; i < int(vx.size()); ++i) {
        root[i + 1] = newNode(*root[i]);
        for (auto p : mdf[i]) {
            int y1, y2, delta;
            std::tie(y1, y2, delta) = p;
            rangeApply(root[i + 1], 0, m, y1, y2, Tag{delta, std::min(delta, 0), 0});
        }
        if (i < int(vx.size()) - 1) {
            rangeApply(root[i + 1], 0, m, 0, m, Tag{0, 0, vx[i + 1] - vx[i]});
        }
    }

    auto query = [&](int x, int y) -> i64 {
        int px = std::upper_bound(vx.begin(), vx.end(), x) - vx.begin() - 1;
        int py = std::upper_bound(vy.begin(), vy.end(), y) - vy.begin() - 1;
        i64 ans = rangeQuery(root[px], 0, m, 0, py).ans, tmp = ans;
        i64 tx = 0, ty = 0, txy = 0;
        if (vx[px] != x) {
            tx = rangeQuery(root[px + 1], 0, m, 0, py).ans - tmp;
            ans += tx / (vx[px + 1] - vx[px]) * (x - vx[px]);
        }
        if (vy[py] != y) {
            ty = rangeQuery(root[px], 0, m, 0, py + 1).ans - tmp;
            ans += ty / (vy[py + 1] - vy[py]) * (y - vy[py]);
        }
        if (vx[px] != x && vy[py] != y) {
            txy = rangeQuery(root[px + 1], 0, m, 0, py + 1).ans - tx - ty - tmp;
            ans += txy / (vx[px + 1] - vx[px]) * (x - vx[px]) / (vy[py + 1] - vy[py]) * (y - vy[py]);
        } 
        return ans;
    };

    i64 ans = 0;
    auto get = [&](int &x, int v, int k) {
        x = (x + ans % k * v) % k;
    };
    while (q--) {
        int x1, y1, x2, y2, _v;
        std::cin >> x1 >> y1 >> x2 >> y2 >> _v;
        get(x1, _v, V);
        get(y1, _v, V);
        get(x2, _v, V);
        get(y2, _v, V);
        std::tie(x1, x2) = std::minmax({x1, x2});
        std::tie(y1, y2) = std::minmax({y1, y2});
        ans = 1ll * (x2 - x1) * (y2 - y1);
        ans -= query(x2, y2) - query(x1, y2) - query(x2, y1) + query(x1, y1);
        std::cout << ans << "\n";
    }

}
