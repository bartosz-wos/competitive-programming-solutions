#include <algorithm>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int longest_nondec_subseq(const vector<int> &seq) {
	vector<int> min_endings;
	for (int i : seq) {
		int pos = std::upper_bound(min_endings.begin(), min_endings.end(), i) -
		          min_endings.begin();
		if (pos == min_endings.size()) {
			min_endings.push_back(i);
		} else {
			min_endings[pos] = i;
		}
	}
	return min_endings.size();
}

int main() {
	int pole_num;
	int jump_height;
	std::cin >> pole_num >> jump_height;
	vector<int> poles(pole_num);
	for (int p = 0; p < pole_num; p++) { std::cin >> poles[p]; }

	vector<int> poss_unchanged;
	for (int i = 1; i <= pole_num; i++) {
		if (i * jump_height >= poles[i - 1]) {
			poss_unchanged.push_back(i * jump_height - poles[i - 1]);
		}
	}
	cout << pole_num - longest_nondec_subseq(poss_unchanged) << endl;
}
