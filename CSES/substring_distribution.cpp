#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
struct state{
	int len=0,link=-1;
	map<char,int>nex;
};
state st[300000];
int sz=1,last=0;
ll res[100001];
 
void extend(const char&c){
	int cur=sz++;
	st[cur].len=st[last].len+1;
	int p=last;
	while(p!=-1 and !st[p].nex.count(c)){
		st[p].nex[c]=cur;
		p=st[p].link;
	}
	if(p==-1)
		st[cur].link=0;
	else{
		int q=st[p].nex[c];
		if(st[p].len+1==st[q].len)
			st[cur].link=q;
		else{
			int clone=sz++;
			st[clone]=st[q];
			st[clone].len=st[p].len+1;
			while(p!=-1 and st[p].nex[c]==q){
				st[p].nex[c]=clone;
				p=st[p].link;
			}
			st[q].link=st[cur].link=clone;
		}
	}
	last=cur;
}
 
void bfs(){
	vector<int>d(sz,-1);
	queue<int>Q;
	Q.push(0);
	d[0]=0;
	while(!Q.empty()){
		int u=Q.front();
		Q.pop();
		++res[d[u]];
		--res[st[u].len+1];
		for(const auto&[f,i]:st[u].nex)
			if(d[i]==-1){
				d[i]=d[u]+1;
				Q.push(i);
			}
	}
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	string s;
	cin>>s;
	for(const char&c:s)extend(c);
	bfs();
	for(int i=1;i<=s.size();++i){
		res[i]+=res[i-1];
		cout<<res[i]<<' ';
	}
}
