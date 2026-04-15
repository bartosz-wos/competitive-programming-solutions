#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
struct state{
	int len=0,link=-1,cnt=0;
	ll dp=0;
	map<char,int>nex;
};
state st[300000];
int sz=1,last=0;
ll k;
 
void extend(const char&c){
	int cur=sz++;
	st[cur].len=st[last].len+1;
	st[cur].cnt=1;
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
			st[clone].cnt=0;
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
 
void init(){
	vector<int>len[sz];
	for(int i=1;i<sz;++i)
		len[st[i].len].emplace_back(i);
	for(int i=sz-1;i>0;--i)
		for(const int&j:len[i])
			st[st[j].link].cnt+=st[j].cnt;
}
 
void DP(int v){
	st[v].dp=st[v].cnt;
	for(const auto&[f,i]:st[v].nex){
		if(!st[i].dp)DP(i);
		st[v].dp+=st[i].dp;
	}
}
 
void ask(int v){
	if(k<=0)return;
	for(const auto&[f,i]:st[v].nex){
		if(st[i].dp<k)k-=st[i].dp;
		else{
			cout<<f;
			k-=st[i].cnt;
			ask(i);
			return;
		}
	}
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	string s;
	cin>>s>>k;
	for(const char&c:s)extend(c);
	init();
	DP(0);
	ask(0);
}
