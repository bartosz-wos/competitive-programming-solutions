#include<bits/stdc++.h>
 using namespace std;
 
 const int mx=1e4+1;
 
 typedef long long ll;
 
 ll phi[mx];
 
 void totient_sieve()
 
 {
     for(int i=1;i<mx;i++)
     {
         phi[i]=i;
     }
     for(int p=2;p<mx;p++)
     {
         if(phi[p]==p)
         {
             for(int j=p;j<mx;j+=p)
             	phi[j]-=phi[j]/p;
         }
     }
 }
 
 
 int main()
 
 {
     totient_sieve();
     phi[1]=1;
     ll dp[mx];
     ll sum=0;
     for(int i=1;i<mx;i++)
     {
         sum=sum+phi[i];
         dp[i]=sum*sum;
     }
    int t,n,m;
    ll h;
    cin>>t;
    while(t--)
    {
        cin>>n;
        cout<<dp[n]<<endl;
    }
 }
