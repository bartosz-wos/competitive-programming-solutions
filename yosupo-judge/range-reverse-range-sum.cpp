#include<bits/stdc++.h>
#define int long long
#define pb push_back
#define fast ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
#define MOD 1000000007
#define inf 1e18
#define fi first
#define se second
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define FORD(i,a,b) for(int i=a;i>=b;i--)
#define sz(a) ((int)(a).size())
#define endl '\n'
#define pi 3.14159265359
#define TASKNAME "rrrsum"
using namespace std;
template<typename T> bool maximize(T &res, const T &val) { if (res < val){ res = val; return true; }; return false; }
template<typename T> bool minimize(T &res, const T &val) { if (res > val){ res = val; return true; }; return false; }
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef vector<int> vi;
const int MAXN = 5e5 + 9;
int a[MAXN], n, q;

int RAND(){
    int res = 0;
    FOR(i, 1, 30){
        res += (1LL << (rand() % 30));
    }
    return res;
}

struct TreapNode{
    TreapNode *leftChild, *rightChild;
    int val = 0, sum = 0, weight;
    int lazy = 0, sz = 0;

    TreapNode(int _val = 0){
        val = _val;
        sum = val;
        weight = RAND();
        lazy = 0;
        sz = 1;
        leftChild = rightChild = nullptr;
    }
};

typedef TreapNode* Treap;

int getSum(Treap root){
    if (root == nullptr) return 0;
    return root->sum;
}

int getSize(Treap root){
    if (root == NULL) return 0;
    return root->sz;
}

void update(Treap &root){
    if (root == NULL) return;
    root->sum = root->val + getSum(root->leftChild) + getSum(root->rightChild);
    root->sz = 1 + getSize(root->leftChild) + getSize(root->rightChild);
}

void fix(Treap root){
    if (root == NULL) return;

    if (root->lazy){
        swap(root->leftChild, root->rightChild);
        if (root->leftChild != NULL) root->leftChild->lazy ^= 1;
        if (root->rightChild != NULL) root->rightChild->lazy ^= 1;
    }
    root->lazy = 0;
}
void split(Treap rt, Treap &l, Treap &r, int key, int add){

    if (rt == NULL) {
        l = r = NULL;
        return;
    }
    fix(rt);

    int imkey = add + getSize(rt->leftChild);
    if (imkey <= key){
        l = rt;
        split(rt->rightChild, l->rightChild, r, key, imkey + 1);
        update(rt);
    }
    else{
        r = rt;
        split(rt->leftChild, l, r->leftChild, key, add);
        update(rt);
    }
}

void merge(Treap &rt, Treap l, Treap r){
    fix(l);
    fix(r);
    if (!l or !r){
        rt = ((!l) ? r : l);
        return;
    }

    if (l->weight < r->weight){
        rt = r;
        merge(rt->leftChild, l, r->leftChild);
        update(rt);
    }
    else{
        rt =l;
        merge(rt->rightChild, l->rightChild, r);
        update(rt);
    }
}

void go(Treap rt){
    if (rt == NULL) return;

    go(rt->leftChild);
    cout << rt->val << ' ';

    go(rt->rightChild);

}
Treap rt;
main()
{
    fast;
//    srand(time(NULL));
    if (fopen(TASKNAME".inp","r")){
        freopen(TASKNAME".inp","r",stdin);
        freopen(TASKNAME".out","w",stdout);
    }
    cin >> n >> q;


    FOR(i, 0, n - 1){
        cin >> a[i];
        merge(rt, rt, new TreapNode(a[i]));
    }

    FOR(i, 0, q - 1){
        int type, l, r;
        cin >> type >> l >> r;
        if (l >= r) {
            if (type == 1) cout << 0 << endl;
        }
        else{
            if (type == 0){
                Treap a, b, c, d;
                split(rt, a, b, l - 1, 0);
                split(b, c, d, r - l - 1, 0);
                c->lazy = true;
                merge(rt, a, c);
                merge(rt, rt, d);
            }
            else{
                Treap a, b, c, d;
                split(rt, a, b, l - 1, 0);
                split(b, c, d, r - l - 1, 0);
                cout << c->sum << endl;
                merge(rt, a, c);
                merge(rt, rt, d);
//
            }

        }
    }

}
