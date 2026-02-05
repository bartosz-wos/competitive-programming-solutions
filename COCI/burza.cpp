#include <functional>
#include <iostream>
#include <map>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int main() {
	int node_num;
	int max_turns;
	std::cin >> node_num >> max_turns;
	vector<vector<int>> neighbors(node_num);
	for (int e = 0; e < node_num - 1; e++) {
		int n1, n2;
		std::cin >> n1 >> n2;
		neighbors[--n1].push_back(--n2);
		neighbors[n2].push_back(n1);
	}

	if (max_turns * max_turns >= node_num) {
		cout << "DA" << endl;
		return 0;
	}

	std::map<int, int> lost;
	vector<vector<int>> cutoff_cover(node_num);
	vector<vector<int>> depth_nodes(max_turns + 1);

	std::function<void(int, int, int)> process_nodes;
	process_nodes = [&](int at, int prev, int depth) {
		depth_nodes[depth].push_back(at);
		if (depth == max_turns) {
			lost[at] = lost.size();
			cutoff_cover[at] = {at};
			return;  // we don't care about anything past this depth
		}
		for (int n : neighbors[at]) {
			if (n != prev) {
				process_nodes(n, at, depth + 1);
				cutoff_cover[at].insert(cutoff_cover[at].end(), cutoff_cover[n].begin(),
				                        cutoff_cover[n].end());
			}
		}
	};
	process_nodes(0, 0, 0);

	// intervals[n] the interval of leaves we can cover if we cut off node n
	vector<std::pair<int, int>> intervals;
	for (const vector<int> &cc : cutoff_cover) {
		if (cc.empty()) {
			intervals.push_back({-1, -1});
		} else {
			intervals.push_back({lost[cc.front()] + 1, lost[cc.back()] + 1});
		}
	}

	/*
	 * max_cover[ss] contains the max # of leaves we can cover all
	 * the way from the start given that
	 * we only cut off nodes of depths specified in the subsets ss
	 */
	vector<int> max_cover(1 << max_turns);
	max_cover[0] = 0;
	for (int ss = 1; ss < (1 << max_turns); ss++) {
		int &curr = max_cover[ss];
		// go through each possible previous depth
		for (int to_add = 0; to_add < max_turns; to_add++) {
			if ((ss & (1 << to_add)) != 0) {
				int prev = max_cover[ss & ~(1 << to_add)];
				// and all the nodes of said depth
				for (int n : depth_nodes[to_add + 1]) {
					// see if we can cover more nodes than before
					if (intervals[n].first <= prev + 1) {
						curr = std::max(curr, intervals[n].second);
					}
				}
			}
		}

		if (max_cover[ss] == lost.size()) {
			cout << "DA" << endl;
			return 0;
		}
	}

	cout << "NE" << endl;
}
