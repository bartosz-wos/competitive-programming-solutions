#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define MASK(i) (1LL << (i))
#define GETBIT(mask, i) (((mask) >> (i)) & 1)
#define ALL(v) (v).begin(), (v).end()

ll max(ll a, ll b){return (a > b) ? a : b;}
ll min(ll a, ll b){return (a < b) ? a : b;}

ll gcd(ll a, ll b){return __gcd(a, b);}
ll LASTBIT(ll mask){return (mask) & (-mask);}
int pop_cnt(ll mask){return __builtin_popcountll(mask);}
int ctz(ll mask){return __builtin_ctzll(mask);}
int logOf(ll mask){return __lg(mask);}

mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
ll rngesus(ll l, ll r){return l + (ull) rng() % (r - l + 1);}

template <class T1, class T2>
    bool maximize(T1 &a, T2 b){
        if (a < b) {a = b; return true;}
        return false;
    }

template <class T1, class T2>
    bool minimize(T1 &a, T2 b){
        if (a > b) {a = b; return true;}
        return false;
    }

template <class T>
    void printArr(T& container, string separator = " ", string finish = "\n"){
        for(auto item: container) cout << item << separator;
        cout << finish;
    }


template <class T>
    void remove_dup(vector<T> &a){
        sort(ALL(a));
        a.resize(unique(ALL(a)) - a.begin());
    }

const int INF = 1e9 + 69;

struct SegmentTree{
    int n;
    vector<int> a;

    SegmentTree(int _n = 0){
        n = _n;
        a.resize(n * 4 + 4, INF);
    }

    void update(int i, int v){
        int id = 1;
        int l = 1, r = n;
        while(l < r){
            int mid = (l + r) >> 1;
            minimize(a[id], v);
            if (i <= mid) {
                r = mid;
                id = id * 2;
            }
            else{
                l = mid + 1;
                id = id * 2 + 1;
            }
        }
        minimize(a[id], v);
    }

    int find_next(int i, int v, int l, int r, int id){
        if (a[id] > v) return -1;
        if (r < i) return -1;
        if (l == r) return l;
        int mid = (l + r) >> 1;
        int left = find_next(i, v, l, mid, id * 2);
        if (left != -1) return left;
        return find_next(i, v, mid + 1, r, id * 2 + 1);
    }

    int find_next(int i, int v){
        return find_next(i, v, 1, n, 1);
    }
};

void solve(){
    int n, q; cin >> n >> q;
    SegmentTree st(n);
    for(int i = 0; i< q; ++i){
        char type; cin >> type;
        if (type == 'M'){
            int x, a; cin >> x >> a;
            st.update(a, x);
        }
        else{
            int y, b; cin >> y >> b;
            cout << st.find_next(b, y) << "\n";
        }
    }
}

int main(void){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    clock_t start = clock();

    solve();

    cerr << "Time elapsed: " << clock() - start << "ms!\n";
    return 0;
}

