#include<bits/stdc++.h>
using namespace std;
string trace(int a,int b)
{
    if(a==b)return "";
    else if(a>b)return '1'+trace(a-b,b);
    else return '0'+trace(a,b-a);
}
int trace_len(int a,int b)
{
    if(a==b)return 0;
    else if(a>b)return 1+trace_len(a-b,b);
    else return 1+trace_len(a,b-a);
}
int main()
{
    int n;cin>>n;
    int b,mn=++n;
    for(int a=1;a<=n+1;a++)
    {
        if(__gcd(a,n+1)!=1)continue;
        int len=trace_len(a,n-a+1);
        if(len<mn)mn=len,b=n-a+1;
    }
    cout<<trace(n-b+1,b)<<"\n";
}
