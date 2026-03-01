#include<bits/stdc++.h>
using namespace std;
using ll=long long;

struct node{
	int nxt[26],link,len,p;
}et[1000005];

string s;
int suf,cnt;

int f(int v){
	if(v==1)return -1;
	if(v==2)return 0;
	return v-2;
}

vector<int>ans;

void ext(int pos){
	int cur=suf,curlen=0;
	int c=s[pos]-97;
	while(1){
		curlen=et[cur].len;
		if(pos-1-curlen>=0 and s[pos-1-curlen]==s[pos])break;
		cur=et[cur].link;
	}
	if(et[cur].nxt[c]){
		suf=et[cur].nxt[c];
		ans.push_back(f(suf));
		return;
	}
	suf=++cnt;
	et[cnt].len=et[cur].len+2;
	et[cur].nxt[c]=cnt;
	et[cnt].p=cur;
	if(et[cnt].len==1){
		et[cnt].link=2;
		ans.push_back(f(suf));
		return;
	}
	while(1){
		cur=et[cur].link;
		curlen=et[cur].len;
		if(pos-1-curlen>=0 and s[pos-1-curlen]==s[pos]){
			et[cnt].link=et[cur].nxt[c];
			break;
		}
	}
	ans.push_back(f(suf));
}

void init(){
	cnt=2,suf=2;
	et[1].len=-1;
	et[1].link=et[2].link=1;
	et[2].len=0;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	init();
	cin>>s;
	for(int i=0;i<s.size();++i)ext(i);
	int n=cnt-2;
	cout<<n<<'\n';
	for(int i=3;i<=cnt;++i)
		cout<<f(et[i].p)<<' '<<f(et[i].link)<<'\n';
	for(const int&i:ans)
		cout<<i<<' ';
	cout<<'\n';
}
