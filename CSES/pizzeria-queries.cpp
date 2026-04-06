#include<bits/stdc++.h>
using namespace std;
constexpr int mod = 1e9 + 7;
 
int n,q;
vector<int> tree1;
vector<int> tree2;
void build()
{
    for(int i=0;i<n;i++)
    {
        int a;
        cin>>a;
        tree1[i+n]=a+i;
        tree2[i+n]=a-i;
    }
    for(int i=n-1;i>0;i--)
    {
        tree1[i]=min(tree1[2*i],tree1[2*i+1]);
        tree2[i]=min(tree2[2*i],tree2[2*i+1]);
    }
}
void update(int k,int u)
{
    tree1[k+n]=u+k;
    tree2[k+n]=u-k;
    k+=n;
    for(int i=k/2;i>0;i/=2)
    {
        tree1[i]=min(tree1[2*i],tree1[2*i+1]);
        tree2[i]=min(tree2[2*i],tree2[2*i+1]);
    }
}
long long query1(int a,int b)
{
    a+=n;
    b+=n;
    int ans=INT_MAX;
    while(a<=b)
    {
        if(a%2==1)
            ans=min(ans,tree1[a++]);
        if(b%2==0)
            ans=min(ans,tree1[b--]);
        a/=2;
        b/=2;
    }
    return ans;
}
 
long long query2(int a,int b)
{
    a+=n;
    b+=n;
    int ans=INT_MAX;
    while(a<=b)
    {
        if(a%2==1)
            ans=min(ans,tree2[a++]);
        if(b%2==0)
            ans=min(ans,tree2[b--]);
        a/=2;
        b/=2;
    }
    return ans;
}
 
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cin>>n>>q;
    tree1.assign(2*n,0);
    tree2.assign(2*n,0);
    build();
 
    for(int i=0;i<q;i++)
    {
        int type;
        cin>>type;
        if(type==1)
        {
            int k,x;
            cin>>k>>x;
            k--;
            update(k,x);
        }
        else
        {
            int k;
            cin>>k;
            k--;
            cout<<min(query1(k,n-1)-k,query2(0,k)+k)<<"\n";
        }
    }
}
