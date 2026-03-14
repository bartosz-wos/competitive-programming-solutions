#include<bits/stdc++.h>
const int N=1e6+10;
std::vector<int> to[N];
int low[N],dfn[N],dfn_cnt;
int sta[N],top;bool in_sta[N];
int from[N];
std::vector<int> scc[N];int scc_cnt;
void tarjan(int u){
	low[u]=dfn[u]=++dfn_cnt;
	in_sta[sta[++top]=u]=1;
	for(int v:to[u]){
		if(!dfn[v]){
			tarjan(v);
			low[u]=std::min(low[u],low[v]);
		}
		else if(in_sta[v]){
			low[u]=std::min(low[u],dfn[v]);
		}
	}
	if(dfn[u]==low[u]){
		++scc_cnt;
		do{
			from[sta[top]]=scc_cnt;
			scc[scc_cnt].push_back(sta[top]);
			in_sta[sta[top]]=0;
		}while(sta[top--]!=u);
	}
}
int ind[N],siz[N];
int q[N];
int main(){
	int n,m,u,v;scanf("%d%d",&n,&m);
	while(m--) scanf("%d%d",&u,&v),to[u].push_back(v);
	for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
	for(int u=1;u<=n;u++){
		for(int v:to[u]){
			if(from[u]!=from[v]){
				++ind[from[v]];
			}
		}
	}
	int p=0;
	for(int i=1;i<=scc_cnt;i++)
		if(!ind[i]) ++p;
	if(p==1){
		printf("%llu\n",scc[scc_cnt].size());
		std::sort(scc[scc_cnt].begin(),scc[scc_cnt].end());
		for(int i:scc[scc_cnt]){
			printf("%d ",i);
		}
	}
	else putchar('0');
}
