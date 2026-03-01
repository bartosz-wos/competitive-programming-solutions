#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        int n;
        cin>>n;
        vector<bitset<4096>>bs(n),inv(n);
        for(int i=0;i<n;++i){
                string s;
                cin>>s;
                for(int j=0;j<n;++j)
                        if(s[j]-48)
                                bs[i].set(j);
		inv[i].set(i);
        }
        for(int i=0;i<n;++i){
                int p=i;
                while(p<n and !bs[p][i])++p;
                if(p==n){
                        cout<<-1<<'\n';
                        return 0;
                }
                if(p!=i)swap(bs[i],bs[p]),swap(inv[i],inv[p]);
                for(int j=0;j<n;++j)
                        if(j^i and bs[j][i])
                                bs[j]^=bs[i],inv[j]^=inv[i];
        }
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j)
			cout<<inv[i][j];
		cout<<'\n';
	}
}
