#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<pair<int,int>> nums(pow(2,n));
    for(int i=0;i<pow(2,n);i++){
        int val;
        cin >> val;
        nums[i] = {val,i};
    }
    sort(nums.begin(),nums.end());
    
    vector<int> ans(pow(2,n));
    
    for(int i=pow(2,n);i>=0;i--){
        if(i!=pow(2,n)-1 and nums[i+1].first==nums[i].first){
            int pos = nums[i].second;
            ans[pos] = ans[nums[i+1].second];
        }
        else{
            int pos = nums[i].second;
            ans[pos] = n - floor(log2(i+1));
        }
    }
    
    for(auto a:ans) cout << a << " ";
    cout << endl;

    return 0;
}
