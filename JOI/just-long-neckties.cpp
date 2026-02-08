#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
pair<int,int> a[N];
int b[N],p[N],s[N],ans[N];
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n+1;i++) cin>>a[i].first,a[i].second=i;
    for(int i=1;i<=n;i++) cin>>b[i];
    sort(a+1,a+n+2);
    sort(b+1,b+n+1);
    for(int i=1;i<=n;i++){
        p[i]=max(p[i-1],max(0,a[i].first-b[i]));
    }
    for(int i=n;i>=1;i--){
        s[i]=max(s[i+1],max(0,a[i+1].first-b[i]));
    }
    for(int i=1;i<=n+1;i++){
        ans[a[i].second]=max(p[i-1],s[i]);
    }
    for(int i=1;i<=n+1;i++){
        cout<<ans[i] <<" ";
    }
}
