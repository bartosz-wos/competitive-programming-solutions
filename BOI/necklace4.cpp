#include <bits/stdc++.h>

using namespace std;

const int N = 6'000 + 10;
string a, b;

int pi[N], match1[N], match2[N];
void initKMP(const string& s1, const string& s2, int* match) { 
  fill(match + 1, match + N, 0);
  string s = s1 + '#' + s2; 
  for (int i = 1; i < (int)s.size(); i++) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) j = pi[j - 1];
    j += (s[i] == s[j]);
    pi[i] = j;
    if (i > (int)s1.size()) match[i - s1.size()] = pi[i];
  }
}

int pos[N];

int32_t main() { 
  cin.tie(0)->sync_with_stdio(0);

  cin >> a >> b;
  int n = a.size(), m = b.size(); 

  int answer = 0, stA = 0, stB = 0;
  for (int turn = 0; turn < 2; ++turn) { 
    for (int i = 0; i <= n; ++i) { 
      string s1 = a.substr(0, i), s2 = a.substr(i, n - i);
      
      initKMP(string(s1.rbegin(), s1.rend()), b, match1);
      initKMP(s2, string(b.rbegin(), b.rend()), match2);
    
      for (int j = 1; j <= m; ++j) { 
        int length = match1[j] + match2[m - j];
        if (length > answer) { 
          answer = length;
          stA = i - match1[j], stB = (!turn ? j - match1[j] : m - (j + match2[m - j]));
        }
      }
    }
    reverse(b.begin(), b.end());
  }

  cout << answer << "\n";
  cout << stA << " " << stB << "\n";
}
