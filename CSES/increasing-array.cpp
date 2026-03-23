#include <iostream>
#include <vector>
using namespace std;
 
unsigned long long n, p, ans;
int main() {
    cin >> n;
    vector<int> tab(n);
 
    for(int& i : tab)
        cin >> i;
 
    p = tab[0];
 
    for(int i = 1; i < n; ++i) {
        if( tab[i] < tab[i-1] ) {
            ans += tab[i-1] - tab[i];
            tab[i] = tab[i-1];
        }
    }
 
    cout << ans;

