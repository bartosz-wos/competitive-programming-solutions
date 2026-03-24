#include <bits/stdc++.h>
using namespace std;
bool ok[8][8];
int ans, vals[8];
bitset<16> blocked;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    for (int i = 0; i < 8; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < 8; j++)
            ok[i][j] = (s[j] == '.');
        vals[i] = i;
    }
 
    do {
        bool works = true;
        for(int i = 0; i < 8; i++)
            if(!ok[i][vals[i]])
                works = false;
        blocked.reset();
        for(int i = 0; i < 8; i++){
            if(blocked[i + vals[i]])
                works = false;
            blocked[i + vals[i]] = true;
        }
        blocked.reset();
        for(int i = 0; i < 8; i++){
            if(blocked[i + 7 - vals[i]])
                works = false;
            blocked[i + 7 - vals[i]] = true;
        }
        if(works) ++ans;
    } while(next_permutation(vals, vals + 8));
 
    cout << ans << '\n';

