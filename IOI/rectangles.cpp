#include<bits/stdc++.h>
#include<fstream>
using namespace std;
#define sz(a) (int)a.size()
#define ALL(v) v.begin(), v.end()
#define ALLR(v) v.rbegin(), v.rend()
#define ll long long
#define pb push_back
#define forr(i, a, b) for(int i = a; i < b; i++)
#define dorr(i, a, b) for(int i = a; i >= b; i--)
#define ld long double
#define vt vector
#include<fstream>
#define fi first
#define se second
#define pll pair<ll, ll>
#define pii pair<int, int>
#define mpp make_pair
const ld PI = 3.14159265359, prec = 1e-9;;
//using u128 = __uint128_t;
const int cox[4] = {1, 0, -1, 0};
#include <vector>

const int coy[4] = {0, -1, 0, 1};
const ll mod = 1e9 + 7, pr = 31;
const int mxn = 2e5 + 5, mxd = 250 * 250, sq = 100, mxv = 5e4 + 1;
//const int base = (1 <<18);
const ll inf = 1e18 + 5, neg = -69420, inf2 = 1e14;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
// have fun!

/*
#include <vector>
static const int buf_size = 4096;

inline int getChar() {
	static char buf[buf_size];
	static int len = 0, pos = 0;
	if (pos == len) {
		pos = 0;
		len = fread(buf, 1, buf_size, stdin);
	}
	if (pos == len)
		return -1;
	return buf[pos++];
}

inline int readChar() {
	int c = getChar();
	while (c <= 32)
		c = getChar();
	return c;
}

inline int readInt() {
	int x; cin >> x;
	return x;
}
*/
#include <vector>
const int N = 2505;
const ll base = (1 << 12);
vt<int>seg_row[N], seg_col[N];
vt<pii>range_col[N], range_row[N];
pair<int, int>row[N][N], col[N][N];
int n, m;
int get(vt<int>&seg, int ob){
    int id = lower_bound(ALL(seg), ob) - seg.begin();
    if(id == sz(seg) || seg[id] != ob)return(-1);
    return(id);
}
ll HASH(ll a, ll b, ll c, ll d){
    return((((a * base) + b) * base + c) * base + d);
}
int HASH(pii a){
    return(a.fi * base + a.se);
}
long long count_rectangles(std::vector<std::vector<int> > a){
    n = sz(a); m = sz(a[0]);
    for(int i = 0; i < n; i++){
        stack<int>st;
        for(int j = 0; j < m; j++){
            while(sz(st) && a[i][st.top()] <= a[i][j])st.pop();
            row[i][j].fi = ((sz(st) == 0) ? 0 : st.top() + 1);
            st.push(j);
        }
        while(sz(st))st.pop();
        for(int j = m - 1; j >= 0; j--){
            while(sz(st) && a[i][st.top()] <= a[i][j])st.pop();
            row[i][j].se = ((sz(st) == 0) ? m - 1 : st.top() - 1);
            st.push(j);
        }
    }
    for(int j = 0; j < m; j++){
        stack<int>st;
        for(int i = 0; i < n; i++){
            while(sz(st) && a[st.top()][j] <= a[i][j])st.pop();
            col[i][j].fi = ((sz(st) == 0) ? 0 : st.top() + 1);
            st.push(i);
        }
        while(sz(st))st.pop();
        for(int i = n - 1; i >= 0; i--){
            while(sz(st) && a[st.top()][j] <= a[i][j])st.pop();
            col[i][j].se = ((sz(st) == 0) ? n - 1 : st.top() - 1);
            st.push(i);
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            seg_row[i].pb(HASH(row[i][j])); seg_col[j].pb(HASH(col[i][j]));
        }
    }
    for(int i = 0; i < n; i++){
        sort(ALL(seg_row[i])); seg_row[i].resize(unique(ALL(seg_row[i])) - seg_row[i].begin());
        range_row[i].resize(sz(seg_row[i]));
    }
    for(int i = 0; i < m; i++){
        sort(ALL(seg_col[i])); seg_col[i].resize(unique(ALL(seg_col[i])) - seg_col[i].begin());
        range_col[i].resize(sz(seg_col[i]));
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < sz(seg_row[i]); j++){
            if(i == 0){
                range_row[i][j].fi = 0; continue;
            }
            int id = get(seg_row[i - 1], seg_row[i][j]);
            if(id == -1){
                range_row[i][j].fi = i;
            }else{
                range_row[i][j].fi = range_row[i - 1][id].fi;
            }
        }
    }
    for(int i = n - 1; i >= 0; i--){
        for(int j = 0; j < sz(seg_row[i]); j++){
            if(i == n - 1){
                range_row[i][j].se = n - 1; continue;
            }
            int id = get(seg_row[i + 1], seg_row[i][j]);
            if(id == -1){
                range_row[i][j].se = i;
            }else{
                range_row[i][j].se = range_row[i + 1][id].se;
            }
        }
    }
    for(int i = 0; i < m; i++){
        for(int j = 0; j < sz(seg_col[i]); j++){
            if(i == 0){
                range_col[i][j].fi = 0; continue;
            }
            int id = get(seg_col[i - 1], seg_col[i][j]);
            if(id == -1){
                range_col[i][j].fi = i;
            }else{
                range_col[i][j].fi = range_col[i - 1][id].fi;
            }
        }
    }
    for(int i = m - 1; i >= 0; i--){
        for(int j = 0; j < sz(seg_col[i]); j++){
            if(i == m - 1){
                range_col[i][j].se = m - 1; continue;
            }
            int id = get(seg_col[i + 1], seg_col[i][j]);
            if(id == -1){
                range_col[i][j].se = i;
            }else{
                range_col[i][j].se = range_col[i + 1][id].se;
            }
        }
    }
    vt<ll>res;
    for(int i = 1; i < n - 1; i++){
        for(int j = 1; j < m - 1; j++){
            int idr = lower_bound(ALL(seg_row[i]), HASH(row[i][j])) - seg_row[i].begin();
            int idl = lower_bound(ALL(seg_col[j]), HASH(col[i][j])) - seg_col[j].begin();
            if(row[i][j].fi != 0 && row[i][j].se != m - 1 && range_row[i][idr].fi <= col[i][j].fi && range_row[i][idr].se >= col[i][j].se){
                if(col[i][j].fi != 0 && col[i][j].se != n - 1 && range_col[j][idl].fi <= row[i][j].fi && range_col[j][idl].se >= row[i][j].se){
                    res.pb(HASH(row[i][j].fi, row[i][j].se, col[i][j].fi, col[i][j].se));
                }
            }
        }
    }
    sort(ALL(res)); res.resize(unique(ALL(res)) - res.begin());
    return(sz(res));
}

