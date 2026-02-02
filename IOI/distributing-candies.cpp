#include "candies.h"
#include <vector>
#include<bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<ll, ll>;

const int MxN = 2e5 + 5;
int n, q;
ll lz[MxN * 4];

struct node {
    ll val;
    pii mx, mn;
    node() : val(0), mx({0, -1}), mn({0, -1}) {}
    node(ll val, ll idx) : val(val), mx({val, idx}), mn({val, idx}) {}
    node(ll mx, ll mn, ll idx) : val(0), mx({mx, idx}), mn({mn, idx}) {}
    friend node operator + (const node &l, const node &r) {
        node res = node();
        res.val = l.val + r.val;
        res.mx = max(l.mx, r.mx);
        res.mn = min(l.mn, r.mn);
        return res;
    }
} segm[MxN * 4];

using pni = pair<node, ll>;

pni operator + (pni c, node o) {
    c.first = c.first + o;
    return c;
}

void push (ll l, ll r, ll idx) {
    segm[idx].val += lz[idx];
    segm[idx].mx.first += lz[idx];
    segm[idx].mn.first += lz[idx];
    if (l < r) {
        lz[idx * 2 + 1] += lz[idx];
        lz[idx * 2 + 2] += lz[idx];
    }
    lz[idx] = 0;
}

void build (ll l, ll r, ll idx) {
    if (l == r) return void(segm[idx] = node(0, l));
    ll mid = (l + r) >> 1LL;
    build(l, mid, idx * 2 + 1);
    build(mid + 1, r, idx * 2 + 2);
    segm[idx] = segm[idx * 2 + 1] + segm[idx * 2 + 2];
}

void upd (ll l, ll r, ll idx, ll tl, ll tr, ll val) {
    push(l, r, idx);
    if (l > tr || r < tl) return;
    if (l >= tl && r <= tr) {
        lz[idx] += val;
        push(l, r, idx);
        return;
    }
    ll mid = (l + r) >> 1LL;
    push(l, mid, idx * 2 + 1);
    push(mid + 1, r, idx * 2 + 2);
    upd(l, mid, idx * 2 + 1, tl, tr, val);
    upd(mid + 1, r, idx * 2 + 2, tl, tr, val);
    segm[idx] = segm[idx * 2 + 1] + segm[idx * 2 + 2];
}

// pni qr (int l, int r, int idx, ll k) {
//     push(l, r, idx);
//     if (l == r) return {segm[idx], l};
//     int mid = (l + r) >> 1;
//     push(l, mid, idx * 2 + 1);
//     push(mid + 1, r, idx * 2 + 2);
//     node qrr = segm[idx * 2 + 2];
//     if (qrr.mx.first - qrr.mn.first > k) return qr(mid + 1, r, idx * 2 + 2, k);
//     else return qr(l, mid, idx * 2 + 1, k) + segm[idx * 2 + 2];
// }

pni qr (ll l, ll r, ll idx, ll k, node cur) {
    push(l, r, idx);
    if (l == r) return {segm[idx] + cur, l};
    ll mid = (l + r) >> 1LL;
    push(l, mid, idx * 2 + 1);
    push(mid + 1, r, idx * 2 + 2);
    node qrr = segm[idx * 2 + 2] + cur;
    // cerr << "F " << l << ' ' << r << ' ' << idx << ' ' << qrr.mx.first << ' ' << qrr.mn.first << ' ' << k << '\n';
    // cerr << "S " << segm[idx * 2 + 2].mx.first << ' ' << segm[idx * 2 + 2].mn.first << ' ' << cur.mx.first << ' ' << cur.mn.first << '\n';
    if (qrr.mx.first - qrr.mn.first > k) return qr(mid + 1, r, idx * 2 + 2, k, cur);
    else return qr(l, mid, idx * 2 + 1, k, qrr);
    // ll omx = max(cmx, qrr.mx.first), omn = min(cmn, qrr.mn.first);
    // if (omx - omn > k) return qr(mid + 1, r, idx * 2 + 2, k, cmx, cmn);
    // else return qr(l, mid, idx * 2 + 1, k, omx, omn) + segm[idx * 2 + 2];
    // if (qrr.mx.first - qrr.mn.first > k) return qr(mid + 1, r, idx * 2 + 2, k, max(cmx, qrr.mx.first), min(cmn, qrr.mn.first));
    // else return qr(l, mid, idx * 2 + 1, k) + segm[idx * 2 + 2];
}

node oo (ll l, ll r, ll idx, ll pos) {
    push(l, r, idx);
    if (l == r) return segm[idx];
    ll mid = (l + r) >> 1LL;
    push(l, mid, idx * 2 + 1);
    push(mid + 1, r, idx * 2 + 2);
    if (pos <= mid) return oo(l, mid, idx * 2 + 1, pos);
    else return oo(mid + 1, r, idx * 2 + 2, pos);
}

std::vector<int> distribute_candies(std::vector<int> c, std::vector<int> l, std::vector<int> r, std::vector<int> v) {
    n = c.size(); q = l.size();
    std::vector<int> s(n);
    vector<vector<pii>> cq(n, vector<pii>());
    for (int i = 0; i < q; i++) {
        cq[l[i]].emplace_back(v[i], i);
        if (r[i] + 1 < n) cq[r[i] + 1].emplace_back(-v[i], i);
    }
    build(0, q - 1 + 2, 0);
    ll cur = 0;
    upd(0, q - 1 + 2, 0, 0, q - 1 + 2, 1e18);
    upd(0, q - 1 + 2, 0, 1, q - 1 + 2, -1e18);
    for (int i = 0; i < n; i++) {
        for (auto &[x, y]: cq[i]) upd(0, q - 1 + 2, 0, y + 2, q - 1 + 2, x), cur += x;
        auto cqr = qr(0, q - 1 + 2, 0, c[i], node(-1e18, 1e18, 0));
        auto z = cqr.first;
        if (z.mx.second < z.mn.second) s[i] = cur - z.mn.first;
        else s[i] = cur - (z.mx.first - c[i]);
    }
    return s;
}

