#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1e9+10;

struct segnode {
    int sum = 0;
    int upd = 0;
    segnode *segleft, *segright;
    segnode() : sum(0), upd(0), segleft(nullptr), segright(nullptr) {}
};

segnode* root;

void pushdown(segnode* node, int s, int e)
{
    if (node->upd != 1) return;

    const int mid = (s + e) / 2;

    if (!node->segleft && s < e)
        node->segleft = new segnode();
    if (s < e)
        node->segleft->upd = 1;

    if (!node->segright && s < e)
        node->segright = new segnode();
    if (s < e)
        node->segright->upd = 1;
    node->upd = 2;
    node->sum = (e - s + 1);
}

void lazy_update(segnode* node, int l, int r, int s=1, int e=N) {
    pushdown(node, s, e);
    if (e < l || s > r) return;
    if (l <= s && e <= r) {
        node->upd = max(node->upd, 1);
        pushdown(node, s, e);
        return;
    }
    const int mid = (s + e) / 2;

    if (!node->segleft && s < e)
        node->segleft = new segnode();
    if (!node->segright && s < e)
        node->segright = new segnode();

    int cur = 0;
    if (node->segleft) {
        lazy_update(node->segleft, l, r, s, mid);
        cur += node->segleft->sum;
    }
    if (node->segright) {
        lazy_update(node->segright, l, r, mid+1, e);
        cur += node->segright->sum;
    }
    node->sum = cur;
}

int query(segnode* node, int l, int r, int s=1, int e=N) {
    pushdown(node, s, e);
    if (e < l || s > r) return 0;
    if (l <= s && e <= r)
        return node->sum;
    const int mid = (s + e) / 2;
    int sum = 0;
    if (node->segleft)
        sum += query(node->segleft, l, r, s, mid);
    if (node->segright)
        sum += query(node->segright, l, r, mid+1, e);
    return sum;
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int q, cmd, x, y;
    cin >> q;
    root = new segnode();
    int c = 0;
    while (q--) {
        cin >> cmd >> x >> y;
        if (cmd == 1) {
            c = query(root, x+c, y+c);
            cout << c << '\n';
        }
        else if (cmd == 2) {
            lazy_update(root, x+c, y+c);
        }
    }
}
