#include<bits/stdc++.h>
using namespace std;
using ll=long long;

struct state{
        int len,link=-1;
	int first_pos;
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
                        while(~p and st[p].next[c]==q){
                                st[p].next[c]=clone;
                                p=st[p].link;
                        }
                        st[q].link=st[cur].link=clone;
                }
        }
        last=cur;
}

int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        string s,t;
        cin>>s>>t;
        for(const char&c:s)ext(c);
	int v=0,l=0,res=0,pos=0,pos2=0;
	for(int i=0;i<t.size();++i){
		while(v and !st[v].next.count(t[i])){
			v=st[v].link;
			l=st[v].len;
		}
		if(st[v].next.count(t[i])){
			v=st[v].next[t[i]];
			++l;
		}
		if(l>res){
			res=l;
			pos=i;
			pos2=st[v].first_pos;
		}
	}
	if(!res){
		cout<<"0 0 0 0\n";
		return 0;
	}
	cout<<pos2-res+1<<' '<<pos2+1<<' '<<pos-res+1<<' '<<pos+1<<'\n';
}
