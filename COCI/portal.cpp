#include <bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define endl '\n'
#define MASK(i) (1LL << (i))
#define ull unsigned long long
#define ld long double
#define pb push_back
#define all(x) (x).begin() , (x).end()
#define BIT(x , i) ((x >> (i)) & 1) 
#define TASK "task"
#define sz(s) (int) (s).size()

using namespace std;
const int mxN = 507;
const int inf = 1e9 + 277;
const int mod = 1e9 + 7;
const ll infll = 1e18 + 7;
const int base = 307;
const int LOG = 20;
 
template <typename T1, typename T2> bool minimize(T1 &a, T2 b) {
	if (a > b) {a = b; return true;} return false;
}
template <typename T1, typename T2> bool maximize(T1 &a, T2 b) {
	if (a < b) {a = b; return true;} return false;
}

struct item{
	int x , y , dist;
};

struct cmp{
	bool operator()(item a , item b)
	{
		return a.dist > b.dist;
	}
};

int n , m;
char a[mxN][mxN];
int dist[mxN][mxN];
int block[mxN][mxN];
pair<int , int> sta;
pair<int , int> fin;
pair<int , int> dd[mxN][mxN][4];

int dx[4] = {0 , 1 , 0 , -1};
int dy[4] = {1 , 0 , -1 , 0};

void solve()
{
	cin >> n >> m;
	for(int i = 1 ; i <= n ; i++)
	for(int j = 1 ; j <= m ; j++) {
		cin >> a[i][j];
		if(a[i][j] == 'C') {
			sta = {i , j};
			a[i][j] = '.';
		}
		if(a[i][j] == 'F') {
			fin = {i , j};
			a[i][j] = '.';
		}
	}

	queue<pair<int , int>> q;
	memset(block , -1 , sizeof(block));
	for(int i = 1 ; i <= n ; i++)
	for(int j = 1 ; j <= m ; j++) {
		if(a[i][j] == '#') {
			block[i][j] = 0;
			q.push({i , j});
		}
	}

	while(!q.empty()) {
		int x = q.front().fi;
		int y = q.front().se;
		q.pop();

		for(int d = 0 ; d < 4 ; d++) {
			int newx = x + dx[d];
			int newy = y + dy[d];
			if(1 <= newx && newx <= n && 1 <= newy && newy <= m && block[newx][newy] == -1) {
				block[newx][newy] = block[x][y] + 1;
				q.push({newx , newy});
			}
		}
	}


	for(int i = 1 ; i <= n ; i++) {
		pair<int , int> tmp;
		for(int j = 1 ; j <= m ; j++) {
			if(a[i][j] == '#') tmp = {i , j};
			else dd[i][j][0] = {tmp.fi , tmp.se + 1};
		}
		for(int j = m ; j >= 1 ; j--) {
			if(a[i][j] == '#') tmp = {i , j};
			else dd[i][j][1] = {tmp.fi , tmp.se - 1};
		}
	}

	for(int j = 1 ; j <= m ; j++) {
		pair<int , int> tmp;
		for(int i = 1 ; i <= n ; i++) {
			if(a[i][j] == '#') tmp = {i , j};
			else dd[i][j][2] = {tmp.fi + 1 , tmp.se};
		}

		for(int i = n ; i >= 1 ; i--) {
			if(a[i][j] == '#') tmp = {i , j};
			else dd[i][j][3] = {tmp.fi - 1 , tmp.se};
		}
	}


	memset(dist , 0x3f , sizeof(dist));	
	dist[sta.fi][sta.se] = 0;
	priority_queue<item , vector<item> , cmp> pq;
	pq.push({sta.fi , sta.se , 0});
	while(!pq.empty()) {
		int x = pq.top().x;
		int y = pq.top().y;
		int d = pq.top().dist;
		pq.pop();
		if(dist[x][y] != d) continue;

		for(int k = 0 ; k < 4 ; k++) {
			int newx = x + dx[k];
			int newy = y + dy[k];
			if(1 <= newx && newx <= n && 1 <= newy && newy <= m && a[newx][newy] == '.' && minimize(dist[newx][newy] , d + 1)) {
				pq.push({newx , newy , d + 1});
			}
		}

		for(int k = 0 ; k < 4 ; k++) {
			int newx = dd[x][y][k].fi;
			int newy = dd[x][y][k].se;
			if(minimize(dist[newx][newy] , d + block[x][y])) {
				pq.push({newx , newy , d + block[x][y]});
			}
		}
	}

	if(dist[fin.fi][fin.se] == dist[0][0]) cout << "nemoguce";
	else cout << dist[fin.fi][fin.se];
}
 
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //freopen(TASK".in" , "r" , stdin);
    //freopen(TASK".out" , "w" , stdout);
    
    int tc = 1;
    //cin >> tc;
    while(tc--) {
    	solve();
    }
    return 0;
}
