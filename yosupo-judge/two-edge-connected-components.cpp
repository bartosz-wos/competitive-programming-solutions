#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define sz(x) (int)(x).size()
#define uniq(v) v.erase(unique(all(v)), v.end())
#define ft first
#define sd second
#define pb push_back

void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '"' << x << '"';}
void __print(const string &x) {cerr << '"' << x << '"';}
void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef vector<ll> vl;
typedef vector<pll> vll;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
typedef vector<vl> vvl;

#define dbg if(0)

const ll MOD = 1e9+7;
const ll MOD9 = 998244353;
const ll INFLL = 1e18+5;
const int INF = 1e9;

void printbit(int x, int len) {string s="\n";while(len--){s=((x%2)?'1':'0')+s;x/=2;} cout<<s;}
ll power(ll x, ll y, ll mod){x %= mod;if (x<0) x += mod;ll res = 1;
    for (ll t = x;y;t = t * t % mod, y>>=1){
        if (y&1) res = res * t  % mod;
    }
    return res;
}
ll modinv(ll x, ll mod = MOD) {return power(x, mod-2, mod);}

template<class T> bool chmin(T& a, T b){return (a>b?a=b,1:0);}
template<class T> bool chmax(T& a, T b){return (a<b?a=b,1:0);}
template<class T>
istream& operator>>(istream&in, vector<T>&v){
    for (T& x:v) in>>x;
    return in;
}
template<class T>
ostream& operator<<(ostream&out, vector<T>&v){
    for (T& x:v) out<<x<<' ';
    cout<<'\n';
    return out;
}

const int N = 200000;
const int maxK = 8001;

vi adj[N];
int low[N];
int tim[N];
vvi ans;
int timer;
stack<int> stk;

void dfs(int node, int par = -1){
	low[node] = tim[node] = ++timer;
	stk.push(node);
	bool m_edge = true;

	for (int x:adj[node]){
		if (x == par && m_edge) {
			m_edge = false;
			continue;
		}

		if (tim[x]==0) {
			dfs(x, node);
			chmin(low[node], low[x]);
		} else {
			chmin(low[node], tim[x]);
		}
	}
	if (low[node]==tim[node]){
		vi tmp;
		while(stk.top()!=node) {
			tmp.push_back(stk.top());
			stk.pop();
		}
		tmp.push_back(stk.top());
		ans.push_back(tmp);
		stk.pop();
	}
}


void solve(){
    int n, m;cin>>n>>m;

    for (int i = 0;i<m;i++){
    	int u, v;cin>>u>>v;
    	adj[u].push_back(v);
    	adj[v].push_back(u);
    }
    for (int i = 0; i < n; i++){
    	if (tim[i]==0) dfs(i);
    }
    cout<<sz(ans)<<'\n';
    for (auto &x:ans) {
    	cout<<sz(x)<<' ';
    	for (auto y:x) cout<<y<<' ';
    	cout<<'\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t=1, i = 1;
    while(t--){
        solve();
        cout<<'\n';
    }
}
