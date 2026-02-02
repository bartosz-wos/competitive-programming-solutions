#include <bits/stdc++.h>
#include "cycle.h"

void escape(int n) {
	if (n == 2){ jump(1);return;}
	
	int pos = 0;
	int l = 0;
	int r = n-1;
	while (l != r) {
		int mid = (l+r+1)/2;
		int j = mid - pos;
		j = (j+n)%n;
		if (j == 0) j =1;
		if (jump(j)) {
			l = mid;
		} else {
			r = mid-1;
		}
		pos = mid;
	}
	int j = l - pos;
	j = (j+n)%n;
	jump(j);
}

