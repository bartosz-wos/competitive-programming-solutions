#include<bits/stdc++.h>
using namespace std;
#define int long long
#define F first
#define S second
#define all(x) x.begin(),x.end()
#define pii pair<int,int>
#define pb push_back
#define sz(x) (int)(x.size())
#define chmin(x,y) x=min(x,y)
#define chmax(x,y) x=max(x,y)
#define vi vector<int>
#define vp vector<pii>
#define vvi vector<vi>
#define ykh mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count())
#define __lg(x) 63-__builtin_clzll(x)
#define pow2(x) (1LL<<x)
void __print(int x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}
 
template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifdef local
void setio(){freopen("/Users/iantsai/Library/Mobile Documents/com~apple~CloudDocs/cpp/Empty.md","r",stdin);}
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
void setio(){}
#define debug(x...)
#endif
void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}
struct line{
	int a,b;
	int operator()(const int x)const{
		return a*x+b;
	}
};
bool check(line l1,line l2,line l3){
	return (l3.b-l2.b)*(l1.a-l2.a)<=(l2.b-l1.b)*(l2.a-l3.a);
}
const int mxn=501*501;
bitset<mxn>bs;
signed main(){
	setio();
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int n,m,k;
	cin>>n>>m>>k;
	m+=2;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(j==0 or j==m-1)continue;
			char c;
			cin>>c;
			debug(c);
			if(c=='.'){
				bs[i*m+j]=1;
			}
		}
	}
	bitset<mxn>org=bs;
	string s;
	cin>>s;
	debug(s);
	for(auto c:s){
		if(c=='?')bs=((bs>>1)|(bs<<1)|(bs>>m)|(bs<<m))&org;
		else if(c=='W')bs=(bs>>1)&org;
		else if(c=='E')bs=(bs<<1)&org;
		else if(c=='S')bs=(bs<<m)&org;
		else bs=(bs>>m)&org;
	}
	cout<<bs.count()<<'\n';
}

