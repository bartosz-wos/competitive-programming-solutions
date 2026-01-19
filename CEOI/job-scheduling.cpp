#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef pair<int,int> pi;
typedef vector<pi> pii;
typedef tuple<int,int,int> tii;
typedef vector<ll> li;
typedef vector<li> lii;
 
#define REP(i,a,b) for(int i=a;i<b;i++)
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define LSOne(s) ((s)&(-s))
 
ll INF=1e18+10;
int inf=1e9+10;
ll M=1e9+7;
 
vi a;
pii arr;
int n,d,m;
 
int BS(int l,int r){
    if(l==r)return l;
    int t=(l+r)/2;
    int k=0;int p=1;
    bool flag=1;
    REP(i,0,m){
        if(arr[i].F>p){
            k=0;p=arr[i].F;
        }
        k++;
        if(arr[i].F+d<p){
            flag=0;
            break;
        }
        if(k==t&&i!=m-1){
            k=0;p++;
        }
    }
    if(p>n)flag=0;
    if(flag)return BS(l,t);
    else return BS(t+1,r);
}
 
int main() {   
    cin>>n>>d>>m;
    a.resize(m);
    REP(i,0,m)cin>>a[i];
    REP(i,0,m)arr.PB({a[i],i+1});
    sort(arr.begin(),arr.end());
    int ans=BS(1,m);
    cout<<ans<<"\n";
    int pos=0;int x=0;
    REP(i,0,n){
        while(pos<m&&x<ans){
            cout<<arr[pos].S<<" ";
            pos++;x++;
        }
        cout<<"0\n";
        x=0;
    }
}
