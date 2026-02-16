#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int n,m,cur;
int col[1000005];
vector<int>g[1000005],rg[1000005];
vector<int>ord,comp;

void dfs(int v){
        col[v]=1;
        for(const int&i:g[v])
                if(!col[i])
                        dfs(i);
        ord.push_back(v);
}

void dfs2(int v){
        col[v]=cur;
        comp.push_back(v);
        for(const int&i:rg[v])
                if(!col[i])
                        dfs2(i);
}

int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        string xd;
        cin>>xd;
        cin>>xd;
        cin>>n>>m;
        while(m--){
                int a,b,c;
                cin>>a>>b>>c;
                if(a<0)a=(-a)<<1|1;
                else a<<=1;
                if(b<0)b=(-b)<<1|1;
                else b<<=1;
                g[a^1].push_back(b);
                g[b^1].push_back(a);
                rg[b].push_back(a^1);
                rg[a].push_back(b^1);
        }
        for(int i=1;i<=2*n;++i)
                if(!col[i])
                        dfs(i);
        reverse(ord.begin(),ord.end());
        memset(col,0,sizeof col);
        for(const int&i:ord)
                if(!col[i]){
                        ++cur;
                        dfs2(i);
                }
        for(int i=1;i<=n;++i)
                if(col[i<<1]==col[i<<1|1]){
			cout<<"s UNSATISFIABLE\n";
			return 0;
		}
	cout<<"s SATISFIABLE\nv ";
	for(int i=1;i<=n;++i)
		cout<<(col[i<<1]>col[i<<1|1]?i:-i)<<' ';
	cout<<0<<'\n';
}
