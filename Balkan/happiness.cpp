#include "happiness.h"

struct Node {
    long long l, r, val;
    Node *lc, *rc;

    Node(long long L, long long R): l(L), r(R), val(0), lc(nullptr), rc(nullptr) {}

    void update(long long p, long long v) {
        val += v;
        if (l != r) {
            long long mid = (l + r) / 2;
            if (p > mid) {
                if (!rc) rc = new Node(mid + 1, r);
                rc->update(p, v);
            } else {
                if (!lc) lc = new Node(l, mid);
                lc->update(p, v);    
            }
        }
    }

    long long query(long long a, long long b) {
        if (r < a || l > b) return 0;
        if (r <= b && l >= a) return val;
        long long ret = 0;
        if (lc) ret += lc->query(a, b);
        if (rc) ret += rc->query(a, b);
        return ret;
    }
};

Node *root;

bool check() {
    long long curr = 1, sm = root->val;
    while (curr < sm) {
        long long t = root->query(1, curr);
        if (t < curr) return false;
        curr = t + 1;
    }
    return true;
}

bool init(int coinsCount, long long maxCoinSize, long long coins[]) {
    root = new Node(1, maxCoinSize);
    for (int i = 0; i < coinsCount; i++) root->update(coins[i], coins[i]);
    return check();
}

bool is_happy(int event, int coinsCount, long long coins[]) {
    for (int i = 0; i < coinsCount; i++) root->update(coins[i], event * coins[i]);
    return check();
}
