#include<bits/stdc++.h>
using namespace std;
using ll=long long;

struct state{
        int len,link=-1;
        int first_pos;
	bool cloned=0;
        map<char,int>next;
}st[1000005];
int sz=1,last,idx;

void ext(const char&c){
        int cur=sz++;
        st[cur].len=st[last].len+1;
        st[cur].first_pos=idx++;
        int p=last;
        while(~p and !st[p].next.count(c)){
                st[p].next[c]=cur;
                p=st[p].link;
        }
        if(!~p)st[cur].link=0;
        else{
                int q=st[p].next[c];
                if(st[p].len+1==st[q].len)
                        st[cur].link=q;
                else{
                        int clone=sz++;
                        st[clone]=st[q];
                        st[clone].len=st[p].len+1;
			st[clone].cloned=1;
                        while(~p and st[p].next[c]==q){
                                st[p].next[c]=clone;
                                p=st[p].link;
                        }
                        st[q].link=st[cur].link=clone;
                }
        }
        last=cur;
}

string s;
vector<int>sa;
vector<int>inv[1000005];

void dfs(int v){
	if(v and !st[v].cloned)
		sa.push_back(-st[v].first_pos-1);
	for(const int&i:inv[v])
		dfs(i);
}

int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        cin>>s;
	reverse(s.begin(),s.end());
	for(const char&c:s)ext(c);
	for(int i=1;i<sz;++i)
		inv[st[i].link].push_back(i);
	for(int i=0;i<sz;++i)
		sort(inv[i].begin(),inv[i].end(),[&](const int&a, const int&b){
			return s[st[a].first_pos-st[i].len]<s[st[b].first_pos-st[i].len];
		});
	dfs(0);
	for(const int&i:sa)
		cout<<s.size()+i<<' ';
	cout<<'\n';
}
