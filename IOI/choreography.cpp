#include "choreography.h"
#include <vector>
using namespace std;

int x0 = 0, x1 = 0, i0 = 0, i1 = 0, n;
bool s = false;
vector<int> p, inv;

void init(int N, vector<int> P)
{
    n = N;
    p = P;
    inv.resize(N);
    for(int i = 0; i < N; i++)
    {
        inv[P[i]] = i;
    }
}

void move_right(int K)
{
    x0 += + K;
    x1 += + K;
    if(x0 >= n) x0 -= n;
    if(x1 >= n) x1 -= n;
}

void move_left(int K)
{
    move_right(n - K);
}

void swap_places()
{
    x0 += x0&1 ? -1 : 1;
    x1 += x1&1 ? 1 : -1;
    if(x1 < 0) x1 += n;
    if(x1 >= n) x1 -= n;
}

void move_around()
{
    s = !s;
    swap(x0, i0);
    swap(x1, i1);
}

int get_position(int D)
{
    int i = (D - i0) % 2 == 0 ? D - i0 : D - i1;
    if(i < 0)
        i += n;
    int x = s ? p[i] : inv[i];
    int ans = x & 1 ? x + x1 : x + x0;
    return ans < n ? ans : ans - n;
}
