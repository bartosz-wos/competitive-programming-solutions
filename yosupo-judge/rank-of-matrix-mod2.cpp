#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        int n,m;
        cin>>n>>m;
	if(!n or !m){
		cout<<0<<'\n';
		return 0;
	}
	int sz=(m+63)/64;
        vector<vector<uint64_t>>M(n,vector<uint64_t>(sz,0));
	for(int i=0;i<n;++i){
		string s;
		cin>>s;
		for(int j=0;j<m;++j)
			if(s[j]-48)
				M[i][j>>6]|=(1ULL<<(j&63));
	}
        int r=0;
        for(int i=0;i<m and r<n;++i){
                int p=-1;
		int sz2=i>>6;
		uint64_t b=1ULL<<(i&63);
                for(int j=r;j<n;++j)
                        if(M[j][sz2]&b){
                                p=j;
                                break;
                        }
                if(p==-1)continue;
                if(p!=r)swap(M[r],M[p]);
                for(int j=r+1;j<n;++j)
                        if(M[j][sz2]&b){
				for(int k=sz2;k<sz;++k)
					M[j][k]^=M[r][k];
			}
                ++r;
        }
        cout<<r<<'\n';
}
