#include<bits/stdc++.h>
using namespace std;

const int N=1000010;
typedef pair<int,int> pii;
typedef long long ll;
int n,x1[N],x2[N],y[N];
pii s,t;
ll crs(pii a,pii b,pii c){
	return (ll)(b.first-a.first)*(c.second-a.second)-(ll)(b.second-a.second)*(c.first-a.first);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin>>n;
	cin>>s.first>>s.second>>t.first>>t.second;
	for(int i=1;i<=n;i++)cin>>x1[i]>>x2[i]>>y[i];
	n++;
	x1[n]=x2[n]=t.first,y[n]=t.second;
	
	vector<pii>ans;
	ans.push_back(s);
	deque<pii>L,R;
	L.push_back(s),R.push_back(s);
	for(int i=1;i<=n;i++){
		pii l={x1[i],y[i]},r={x2[i],y[i]};
		while(L.size()>=2&&crs(L.back(),l,L[(int)L.size()-2])>=0)L.pop_back();
		while(R.size()>=2&&crs(R.back(),R[(int)R.size()-2],r)>=0)R.pop_back();
		L.push_back(l),R.push_back(r);
		while(L.size()>=2&&R.size()>=2&&crs(ans.back(),L[1],R[1])<0){
			if(L[1].second>R[1].second){
				ans.push_back(L[1]);
				R[0]=L[1];
				L.pop_front();
			}
			else{
				ans.push_back(R[1]);
				L[0]=R[1];
				R.pop_front();
			}
		}
	}
	ans.push_back(t);
	cout<<ans.size()<<'\n';
	for(auto pr:ans)cout<<pr.first<<' '<<pr.second<<'\n';
}
