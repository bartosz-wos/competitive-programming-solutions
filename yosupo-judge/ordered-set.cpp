#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using ll=long long;
#define ordered_set tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>

int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        int n,q;
        cin>>n>>q;
        ordered_set s;
        for(int i=0,x;i<n;++i){
                cin>>x;
		s.insert(x);
	}
        while(q--){
                int t,k;
                cin>>t>>k;
                if(!t)s.insert(k);
                else if(t==1) s.erase(k);
                else if(t==2) cout<<(s.size()<k?-1:*s.find_by_order(k-1))<<'\n';
		else if(t==3) cout<<s.order_of_key(k+1)<<'\n';
                else if(t==5){
                        auto it=s.lower_bound(k);
                        cout<<(it==s.end()?-1:*it)<<'\n';
		}else{
                        auto it=s.upper_bound(k);
                        cout<<(it==s.begin()?-1:*prev(it))<<'\n';
                }
        }
}
