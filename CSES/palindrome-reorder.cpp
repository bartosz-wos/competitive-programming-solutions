#include <iostream>
using namespace std;
 
int zlicz[26], p;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string a;
    cin >> a;
 
    for (int i = 0; i < a.length(); ++i)
        ++zlicz[a[i] - 65];
 
    for (int i = 0; i < 26; ++i)
        if (zlicz[i] & 1)
            ++p;
 
    if (p > 1)
        cout << "NO SOLUTION";
    else {
 
        for (int i = 0; i < 26; ++i)
            if( !(zlicz[i] & 1) )
                for (int j = 1; (j << 1) <= zlicz[i]; ++j)
                    cout << (char)(i + 65);
 
        for (int i = 0; i < 26; ++i) 
            if (zlicz[i] & 1) {
                for (int j = 1; j <= zlicz[i]; ++j)
                    cout << (char)(i + 65);
            }
 
        for (int i = 25; i >= 0; --i)
            if( !(zlicz[i] & 1) )
                for (int j = 1; (j << 1) <= zlicz[i]; ++j)
                    cout << (char)(i + 65);
 
    }
} 

