#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
struct state{
	int len,link=-1;
	ll dp=0;
	map<char,int>next;
};
state st[500000];
int sz=1,last;
ll k;
 
void ext(const char&c){
	int cur=sz++;
	st[cur].len=st[last].len+1;
	int p=last;
	while(p!=-1 and !st[p].next.count(c)){
		st[p].next[c]=cur;
		p=st[p].link;
	}
	if(p==-1)
		st[cur].link=0;
	else{
		int q=st[p].next[c];
		if(st[p].len+1==st[q].len)
			st[cur].link=q;
		else{
			int clone=sz++;
			st[clone]=st[q];
			st[clone].len=st[p].len+1;
			while(p!=-1 and st[p].next[c]==q){
				st[p].next[c]=clone;
				p=st[p].link;
			}
			st[q].link=st[cur].link=clone;
		}
	}
	last=cur;
}
 
void DP(int v){
	st[v].dp=1;
	for(const auto&[f,i]:st[v].next){
		if(!st[i].dp)DP(i);
		st[v].dp+=st[i].dp;
	}
}
 
void solve(int v){
	if(k<=0)return;
	for(const auto&[f,i]:st[v].next){
		if(st[i].dp<k)k-=st[i].dp;
		else{
			cout<<f;
			--k;
			solve(i);
			break;
		}
	}
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	string s;
	cin>>s>>k;
	for(const char&c:s)ext(c);
	DP(0);
	solve(0);
}
