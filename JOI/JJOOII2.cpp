#include <bits/stdc++.h>

using namespace std;

vector<int> pos[256];

int main() {
    int n, k;
    string s;

    cin >> n >> k;
    cin >> s;

    for ( int i = 0; i < n; i++ )
        pos[s[i]].push_back( i );

    int minChanges = n + 1;
    int o = 0, i = 0;
    for ( int j = 0; j < pos['J'].size() - k + 1; j++ ) {
        while ( o < pos['O'].size() && pos['O'][o] < pos['J'][j + k - 1] )
            o++;

        if ( o + k - 1 >= pos['O'].size() )
            break;

        while ( i < pos['I'].size() && pos['I'][i] < pos['O'][o + k - 1] )
            i++;

        if ( i + k - 1 >= pos['I'].size() )
            break;

        int changes = pos['I'][i + k - 1] - pos['J'][j] + 1 - 3 * k;
        minChanges = min( minChanges, changes );
    }

    cout << (minChanges == n + 1 ? -1 : minChanges);

    return 0;
}
