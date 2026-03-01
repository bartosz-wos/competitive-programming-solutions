#include<bits/stdc++.h>
using namespace std;
using ll=long long;

constexpr int mxn=30*500000+5;
int nxt[2][mxn];
int cnt[mxn];
int tr=1;

bool chk(int x){
        int c=0;
        for(int i=29,b;i>=0;--i){
                b=(x>>i)&1;
                if(!nxt[b][c])return 0;
                c=nxt[b][c];
                if(!cnt[c])return 0;
        }
        return cnt[c];
}

void ins(int x){
	if(chk(x))return;
	int c=0;
	for(int i=29,b;i>=0;--i){
		b=(x>>i)&1;
		if(!nxt[b][c])nxt[b][c]=tr++;
		c=nxt[b][c];
		++cnt[c];
	}
}

void rem(int x){
	if(!chk(x))return;
	int c=0;
	for(int i=29,b;i>=0;--i){
		b=(x>>i)&1;
		c=nxt[b][c];
		--cnt[c];
	}
}

int get(int x){
	int c=0,ret=0;
	for(int i=29,b;i>=0;--i){
		b=(x>>i)&1;
		if(nxt[b][c] and cnt[nxt[b][c]])
			c=nxt[b][c];
		else{
			c=nxt[b^1][c];
			ret|=1<<i;
		}
	}
	return ret;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int q;
	cin>>q;
	while(q--){
		int t,x;
		cin>>t>>x;
		if(!t)ins(x);
		else if(t==1)rem(x);
		else cout<<get(x)<<'\n';
	}
}
