#include <bits/stdc++.h>

#define mp make_pair
#define X first
#define Y second
#define taskname "Maja"

using namespace std;

typedef long long ll;
typedef pair <int, int> ii;

const int N = 101;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
int m, n, k, a, b, c[N][N];
ll dp[2][N][N];

void readInput(){
    scanf("%d %d %d %d %d", &m, &n, &a, &b, &k);
    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= n; j++)
            scanf("%d", &c[i][j]);
}

int inside(int x, int y){
    return (1 <= x && x <= m && 1 <= y && y <= n);
}

void maximize(ll &x, const ll &y){
    if (x < y)
        x = y;
}

void solve(){
    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= n; j++)
            dp[0][i][j] = dp[1][i][j] = -1;

    k /= 2;
    int lim = min(m * n, k);
    dp[0][a][b] = 0;
    for(int i = 0; i < lim; i++){
        int id = i & 1;
        for(int x = 1; x <= m; x++)
            for(int y = 1; y <= n; y++)
                dp[id ^ 1][x][y] = -1;
        for(int x = 1; x <= m; x++)
            for(int y = 1; y <= n; y++){
                if (dp[id][x][y] == -1)
                    continue;
                for(int dir = 0; dir < 4; dir++)
                if (inside(x + dx[dir], y + dy[dir])){
                    int nxtX = x + dx[dir];
                    int nxtY = y + dy[dir];
                    maximize(dp[id ^ 1][nxtX][nxtY], dp[id][x][y] + c[nxtX][nxtY]);
                }
            }
    }

    k -= lim;
    ll ans = 0;
    for(int x = 1; x <= m; x++)
        for(int y = 1; y <= n; y++)
            for(int dir = 0; dir < 4; dir++){
                if (!inside(x + dx[dir], y + dy[dir]))
                    continue;
                ll val = c[x][y] + c[x + dx[dir]][y + dy[dir]];
                maximize(ans, dp[lim & 1][x][y] * 2 + (ll) val * k - c[x][y]);
            }

    cout << ans;
}

int main(){
    //freopen(taskname".inp", "r", stdin);
    //freopen(taskname".out", "w", stdout);
    readInput();
    solve();
    return 0;
}
