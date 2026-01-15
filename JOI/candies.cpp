#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+10,inf=1e18;
int pre[N],nxt[N],st[N],c[N],n,ans;
void del(int u){
    pre[nxt[u]]=pre[u];
    nxt[pre[u]]=nxt[u];
    st[u]=1;
}
priority_queue<pair<int,int> > q;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
	    cin>>c[i];
	    pre[i]=i-1,nxt[i]=i+1;
	    q.push({c[i],i});
	}
	c[0]=c[++n]=-inf;
	for(int i=1;i<=n/2;i++){
	    while(st[q.top().second]) q.pop();
	    auto [w,p]=q.top();q.pop();
	    ans+=w;cout<<ans<<"\n";
	    c[p]=c[pre[p]]+c[nxt[p]]-c[p];
	    q.push({c[p],p});
	    del(pre[p]);del(nxt[p]);
	}
	return 0;
}
