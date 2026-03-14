#include<iostream>
using namespace std;

int n;

int query(int x)
{
    cout<<"? "<<x<<endl;
    cout.flush();
    cin>>x;
    return x;
}

void answer(int x)
{
    cout<<"! "<<x<<endl;
    cout.flush();
}

void solve()
{
    for(int i=0;i<100;i++) if(query(i)) {answer(i); return;}
    answer(100);
}

int main()
{
    int T=1;
    scanf("%d",&T);
    while(T--) solve();
}
