#include<bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAX_PILE = 1e4;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int move_num;
    cin >> move_num;
    vector<int> can_remove(move_num);
    for (int &n : can_remove) { std::cin >> n; }
    vector<int> nimbers(MAX_PILE + 1);
    for (int i = 1; i <= MAX_PILE; i++) {
        set<int> reachable;
        for (int n : can_remove) {
            if (i - n >= 0) { reachable.insert(nimbers[i - n]); }
        }

        for (int n = 0; n <= MAX_PILE; n++) {
            if (!reachable.count(n)) {
                nimbers[i] = n;
                break;
            }
        }
    }

    int game_num;
    cin >> game_num;
    vector<char> wins(game_num);
    for (int g = 0; g < game_num; g++) {
        int pile_num;
        std::cin >> pile_num;

        int xor_sum = 0;
        for (int p = 0; p < pile_num; p++) {
            int pile;
            cin >> pile;
            xor_sum ^= nimbers[pile];
        }

        wins[g] = xor_sum == 0 ? 'L' : 'W';
    }

    for (const char &w : wins) { cout << w; }
    cout << endl;
}
