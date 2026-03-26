#include <iostream>
#include <set>
using namespace std;
 
set <int> sus;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
 
    int* n = new int, *p = new int;
    cin >> *n;
 
    for(int* i = new int{0}; *i < *n; ++(*i)) {
        cin >> *p;
        sus.insert(*p);
    }
 
    cout << sus.size();
}
