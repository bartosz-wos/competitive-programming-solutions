#include <iostream>
 
long long comb(int n, int k) {
	if (k > n - k) { k = n - k; }
	long long ret = 1;
	for (int i = 0; i < k; i++) {
		ret = ret * (n - i) / (i + 1);
	}
	return ret;
}
 
int main() {
	int test_num;
	std::cin >> test_num;
	for (int t = 0; t < test_num; t++) {
		int marble_num;
		int color_num;
		std::cin >> marble_num >> color_num;
		std::cout << comb(marble_num - 1, color_num - 1) << '\n';
	}
} 
