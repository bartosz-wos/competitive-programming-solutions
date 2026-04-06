#include <iostream>
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    char p;
    int n, q, x1, y1, x2, y2;
    cin >> n >> q;
    int grid[n+1][n+1];
 
    for(int i = 1; i <= n; ++i)
    for(int j = 1; j <= n; ++j) {
    cin >> p;
    if(p == '*')
        grid[i][j] = 1;
    else
        grid[i][j] = 0;
    }
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            grid[i][j] = grid[i-1][j] + grid[i][j-1] - grid[i-1][j-1] + grid[i][j];
 
    while( q-- ) {
        cin >> x1 >> y1 >> x2 >> y2;
        cout << grid[x2][y2] - grid[x1 - 1][y2] - grid[x2][y1 - 1] + grid[x1 - 1][y1-1] << '\n';
    }
 
}
