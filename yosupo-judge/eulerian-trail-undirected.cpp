#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pi=array<int,2>;

void solve(){
        int n,m;
        cin>>n>>m;
        vector<vector<pi>>g(n);
        vector<int>deg(n);
	vector<int>vis(m);
        for(int i=0,a,b;i<m;++i){
                cin>>a>>b;
                g[a].push_back({b,i});
		g[b].push_back({a,i});
                ++deg[a],++deg[b];
        }
	int sto=-1,st=0;
	int cnto=0;
	for(int i=0;i<n;++i){
		if(deg[i])st=i;
		if(deg[i]&1){
			++cnto;
			sto=i;
		}
	}
        if(cnto and cnto!=2){
                cout<<"No\n";
                return;
        }
	if(cnto==2)st=sto;
        vector<int>pv,pe;
        stack<pi>s;
        s.push({st,-1});
        while(!s.empty()){
                int v=s.top()[0];
		while(!g[v].empty() and vis[g[v].back()[1]])g[v].pop_back();
                if(!g[v].empty()){
                        auto[i,id]=g[v].back();
                        g[v].pop_back();
                        s.push({i,id});
			vis[id]=1;
                }else{
                        int id=s.top()[1];
                        s.pop();
                        pv.push_back(v);
                        if(~id)pe.push_back(id);
                }
        }
        if(pe.size()!=m){
                cout<<"No\n";
                return;
        }
        cout<<"Yes\n";
        reverse(pv.begin(),pv.end());
        reverse(pe.begin(),pe.end());
        for(const int&i:pv)cout<<i<<' ';
        cout<<'\n';
        for(const int&i:pe)cout<<i<<' ';
        cout<<'\n';
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
