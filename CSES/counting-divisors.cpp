#include<bits/stdc++.h>
using namespace std;
 
int n, p, ans;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n;
    while(n--) {
        ans = 0;
        cin >> p;
        for(int i = 1; i * i <= p; ++i)
            if(!(p % i))
                ans += 2;
        if(sqrt(p) == (int)sqrt(p))
            --ans;
        cout << ans << '\n';
    }
}
