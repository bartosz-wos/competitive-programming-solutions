#include <bits/stdc++.h>
using namespace std;

const int MAXN=100000;

int vmin, vmax;
bool used[2*MAXN]={false};

void updatevmin()
{
    while (used[vmin])
        vmin=vmin+1;

    return;
}

void updatevmax()
{
    while (used[vmax])
        vmax=vmax-1;

    return;
}

int main()
{
    int n, i;
    cin >> n;
    int a[2*n-1], b[n];
    for (i=0; i<n; i++)
        cin >> b[i];
    vmin=1;
    vmax=2*n-1;
    a[0]=b[0];
    used[b[0]]=true;
    for (i=1; i<n; i++)
    {
        if (b[i]==b[i-1])
        {
            updatevmin();
            a[2*i-1]=vmin;
            used[vmin]=true;
            updatevmax();
            a[2*i]=vmax;
            used[vmax]=true;
        }
        if (b[i]>b[i-1])
        {
            if (used[b[i]])
            {
                updatevmax();
                a[2*i-1]=vmax;
                used[vmax]=true;
                updatevmax();
                a[2*i]=vmax;
                used[vmax]=true;
            }
            else
            {
                a[2*i-1]=b[i];
                used[b[i]]=true;
                updatevmax();
                a[2*i]=vmax;
                used[vmax]=true;
            }
        }
        if (b[i]<b[i-1])
        {
            if (used[b[i]])
            {
                updatevmin();
                a[2*i-1]=vmin;
                used[vmin]=true;
                updatevmin();
                a[2*i]=vmin;
                used[vmin]=true;
            }
            else
            {
                a[2*i-1]=b[i];
                used[b[i]]=true;
                updatevmin();
                a[2*i]=vmin;
                used[vmin]=true;
            }
        }
    }
    for (i=0; i<2*n-1; i++)
        cout << a[i] << " ";

    return 0;
}
