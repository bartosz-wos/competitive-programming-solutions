#include <iostream>

#include <vector>

using namespace std;



const int lim = 19, mx = (1 << lim) - 1;

int xors[lim+1];



struct node {

    int count;

    node *left, *right;

    node(int count, node *left, node *right) {

        this->count = count;

        this->left = left;

        this->right = right;

    }

    node* insert(int l, int r, int w);

};



node *null = new node(0, NULL, NULL);



node* node::insert(int l, int r, int v) {

    if (l <= v && v <= r) {

        if (l == r)

            return new node(this->count + 1, null, null);

        return new node(

            this->count + 1,

            this->left->insert(l, (l + r) >> 1, v),

            this->right->insert(((l + r) >> 1) + 1, r, v)

        );

    }

    return this;

}



int kthorder(node* a, node* b, int l, int r, int k) {

    if (l == r)

        return l;

    int count = a->left->count - b->left->count;

    if (count >= k)

        return kthorder(a->left, b->left, l, (l + r) >> 1, k);

    return kthorder(a->right, b->right, ((l + r) >> 1) + 1, r, k - count);

}



int smallerin(node* a, int l, int r, int x) {

    if (x >= r)

        return a->count;

    if (x < l)

        return 0;

    return smallerin(a->left, l, (l + r) >> 1, x) +

           smallerin(a->right, ((l + r) >> 1) + 1, r, x);

}



void mxxor(node* a, node* b, int l, int r, int d) {

    int lc = a->left->count - b->left->count;

    int rc = a->right->count - b->right->count;

    if ((lc == 0) && (rc == 0)) {

        return;

    }

    if (xors[d] == 0) {

        if (rc) {

            xors[d] = 1;

            mxxor(a->right, b->right, ((l + r) >> 1) + 1, r, d + 1);

        } else {

            mxxor(a->left, b->left, l, (l + r) >> 1, d + 1);

        }

    } else {

        if (lc) {

            mxxor(a->left, b->left, l, (l + r) >> 1, d + 1);

        } else {

            xors[d] = 0;

            mxxor(a->right, b->right, ((l + r) >> 1) + 1, r, d + 1);

        }

    }

}



node* root[mx];

int nodes[1000000];



int main() {

    ios_base::sync_with_stdio(false);

    cin.tie(nullptr);



    int n = 0, m, t, x, l, r;

    null->left = null->right = null;

    cin >> m;



    while (m--) {

        cin >> t;

        if (t == 0) {

            cin >> x;

            root[n] = (n == 0 ? null : root[n - 1])->insert(0, mx, x);

            nodes[n] = x;

            n++;

        } else if (t == 1) {

            cin >> l >> r >> x;

            int y = x;

            l--;

            r--;

            fill(begin(xors), end(xors), 0);

            int j = lim;

            while (x > 0) {

                xors[j] = x % 2;

                x /= 2;

                j--;

            }

            mxxor(root[r], (l == 0 ? null : root[l - 1]), 0, mx, 1);

            int ans = 0;

            for (int i = 0, j = lim; j >= 0; j--, i++) {

                ans += xors[j] << i;

            }

            ans ^= y;

            cout << ans << "\n";

        } else if (t == 2) {

            cin >> x;

            n -= x;

        } else if (t == 3) {

            cin >> l >> r >> x;

            l--;

            r--;

            int ans = smallerin(root[r], 0, mx, x) -

                      smallerin((l == 0 ? null : root[l - 1]), 0, mx, x);

            cout << ans << "\n";

        } else if (t == 4) {

            cin >> l >> r >> x;

            l--;

            r--;

            int ans = kthorder(root[r], (l == 0 ? null : root[l - 1]), 0, mx, x);

            cout << ans << "\n";

        }

    }

}


