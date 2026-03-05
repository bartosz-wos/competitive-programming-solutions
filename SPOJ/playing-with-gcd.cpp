#include<bits/stdc++.h>
using namespace std;
#define m 100009
long long  result[m],i,j,d,k,v,r,n;
void phi()
{
    result[0]=0;
    for(k=1;k<=m;k++)
    {
       v=k;
       r=v;
       for(i=2;i*i<=v;i++)
       {
           if(v%i==0)
            r-=r/i;
           while(v%i==0)
            v/=i;
       }
       if(v>1)
       r-=r/v;
       d=k-r;
       result[k]=result[k-1]+d;
    }
     
}
int main()
{
    int t,n,i;
    phi();
    cin>>t;
    for(i=1;i<=t;i++)
    {
        cin>>n;
        printf("Case %d: %d\n",i,result[n]);
    }
} 
