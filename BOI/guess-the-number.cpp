#include <bits/stdc++.h>

using namespace std;

int main(){
	int n;
	cin >> n;
	int l = 1 , r = n;
	int resp = -1;
	while(l < r+1){
		int mid = l + ( r - l)/2;
		if (resp != 0){
			cout << "? " << mid << endl;
			cout.flush();
		}
		cerr << l << " " << r << endl;
		
		cin >> resp;
		if(resp == 0){
			cout << "= " << mid << endl;
			cout.flush();
			break;
		}
		else if(resp == 1){
			r = mid - 1;
		}
		else{
			l = mid + 1;
		}
	}
	
}
