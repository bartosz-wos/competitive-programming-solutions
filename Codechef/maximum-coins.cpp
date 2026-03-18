#include <iostream>
#include <math.h>
using namespace std;

signed main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    int i = 1;
    while (t--)
    {
        int nbParties, gagnees;
        cin >> nbParties >> gagnees;
        int total = 0;
        for (int i = 1; i <= nbParties-gagnees; i++)
        {
            total -= pow(2, i);
        }
        for (int i = nbParties-gagnees+1; i <= nbParties; i++)
        {
            total += pow(2, i);
        }
        cout << total << "\n";
        i++;
    }

    return 0;
}
