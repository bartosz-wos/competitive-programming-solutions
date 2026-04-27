#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
const int x[]={0,1,2,3,4,5,0,3,6,1,4,7};
const int y[]={3,4,5,6,7,8,1,4,7,2,5,8};
 
string per="123456789";
unordered_map<string,int>dist;
 
void bfs(const string&s){
	if(s==per){
		cout<<0<<'\n';
		exit(0);
	}
	dist[per]=1;
	queue<string>Q;
	Q.push(per);
	while(!Q.empty()){
		per=Q.front();
		Q.pop();
		int w=dist[per];
		for(int i=0;i<12;++i){
			swap(per[x[i]],per[y[i]]);
			if(!dist[per]){
				dist[per]=w+1;
				Q.push(per);
				if(per==s){
					cout<<w<<'\n';
					exit(0);
				}
			}
			swap(per[x[i]],per[y[i]]);
		}
	}
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	string s;
	s.resize(9);
	for(int i=0,x;i<9;++i){
		cin>>x;
		s[i]=(char)(x+48);
	}
	bfs(s);
}
