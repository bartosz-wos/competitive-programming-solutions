#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int n,m,ret,tr;

char g[1005][1005];
int vis[1005][1005];

bool check(int i, int j){
	return 1<=i and i<=n and 1<=j and j<=m and g[i][j] != '#' and vis[i][j] != tr;
}

int best_dist, best_vi, best_vj;

void dfs(int i, int j, int cur_dist){
	vis[i][j]=tr;
	if(cur_dist>best_dist){
		best_dist=cur_dist;
		best_vi=i;
		best_vj=j;
	}
	static int dx[4]={1,-1,0,0};
	static int dy[4]={0,0,1,-1};
	for(int k=0;k<4;++k){
		int nx=i+dx[k];
		int ny=j+dy[k];
		if(!check(nx,ny))continue;
		dfs(nx,ny,cur_dist+1);
	}
}

void solve(){
	cin>>m>>n;
	ret=tr=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			cin>>g[i][j];
			vis[i][j]=0;
		}

	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			if(g[i][j]=='#' or vis[i][j])continue;
			best_dist=0;
			best_vi=i;
			best_vj=j;

			++tr,dfs(i,j,0);
			best_dist=0;
			
			++tr,dfs(best_vi, best_vj, 0);
			ret=max(ret,best_dist);
		}

	cout<<"Maximum rope length is "<<ret<<".\n";
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int t;
	cin>>t;
	while(t--)
		solve();
}
