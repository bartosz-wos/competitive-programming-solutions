#include "bits/stdc++.h"

using namespace std;

struct Node {
    Node* l = nullptr;
    Node* r = nullptr;
    int sz;
    char x;
    Node(char x) : l(nullptr), r(nullptr), sz(1), x(x) {}
};

mt19937 gen(22);
using pnode = Node*;

void upd(pnode t) {
    t->sz = 1;
    if (t->l) t->sz += t->l->sz;
    if (t->r) t->sz += t->r->sz;
}

pnode merge(pnode a, pnode b) {
    if (!a) return b;
    if (!b) return a;
    if (gen() % 2) {
        a->r = merge(a->r, b);
        upd(a);
        return a;
    } else {
        b->l = merge(a, b->l);
        upd(b);
        return b;
    }
}

pair<pnode, pnode> split(pnode t, int x) {
    if (!t) return {nullptr, nullptr};
    int sz = 1 + (t->l ? t->l->sz : 0);
    if (x >= sz) {
        auto [l, r] = split(t->r, x - sz);
        t->r = l;
        upd(t);
        return {t, r};
    } else {
        auto [l, r] = split(t->l, x);
        t->l = r;
        upd(t);
        return {l, t};
    }
}

char get(pnode t, int x) {
    int sz = 1 + (t->l ? t->l->sz : 0);
    if (x == sz) {
        return t->x;
    }
    if (x < sz) {
        return get(t->l, x);
    } else {
        return get(t->r, x - sz);
    }
}

void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    pnode root = nullptr;
    for (auto& c : s) {
        pnode A = new Node(c);
        root = merge(root, A);
    }
    while (q--) {
        char c;
        cin >> c;
        if (c == 'a') {
            int x, y;
            cin >> x >> y;
            auto [l, R] = split(root, x);
            auto [L, M] = split(l, x - 1);
            root = merge(L, R);
            auto [l2, r2] = split(root, y - 1);
            root = merge(l2, merge(M, r2));
        } else {
            int x;
            cin >> x;
            cout << get(root, x) << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
//    cin >> t;
    while (t--) {
        solve();
    }
}
