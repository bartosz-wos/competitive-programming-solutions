#include "speedrun.h"
#include <vector>

using namespace std;

static constexpr int BITS_PER_FIELD=10;
static constexpr int HINT_LEN=20;

static void encodeInt(int node, int startbit, int value){
	for(int b=0;b<BITS_PER_FIELD;++b)
		if((value>>b)&1){
			setHint(node,startbit+b,1);
		}
}

static int decodeInt(int startbit){
	int value=0;
	for(int b=0;b<BITS_PER_FIELD;++b)
		if(getHint(startbit+b))
			value |= (1<<b);
	return value;
}

void assignHints(int subtask, int N, int A[], int B[]){
	setHintLen(HINT_LEN);

	vector<vector<int>>adj(N+1);
	for(int i=1;i<N;++i){
		adj[A[i]].push_back(B[i]);
		adj[B[i]].push_back(A[i]);
	}

	vector<int>par(N+1,0);
	vector<int>order;
	order.reserve(N);

	vector<bool>vis(N+1,0);

	auto dfs = [&](auto& self, int u, int p) -> void{
		vis[u]=1;
		par[u]=p;
		order.push_back(u);
		for(int v:adj[u])
			if(!vis[v])
				self(self,v,u);
	};

	dfs(dfs,1,0);

	vector<int>next_dfs(N+1,0);
	for(int i=0;i<N-1;++i)
		next_dfs[order[i]]=order[i+1];
	next_dfs[order.back()]=0;

	for(int i=1;i<=N;++i){
		encodeInt(i,1,par[i]);
		encodeInt(i,11,next_dfs[i]);
	}
}

void speedrun(int subtask, int N, int start){
	int curr=start;

	while(1){
		int p=decodeInt(1);
		if(!p)break;
		goTo(p);
		curr=p;
	}

	while(1){
		int nxt=decodeInt(11);
		if(!nxt)break;

		while(!goTo(nxt)){
			int p=decodeInt(1);
			goTo(p);
			curr=p;
		}

		curr=nxt;
	}
}
