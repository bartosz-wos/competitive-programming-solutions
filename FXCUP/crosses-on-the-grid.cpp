#include <bits/stdc++.h>

using namespace std;

struct Cross {
  uint64_t inner, outer;
};

uint64_t SelectCross(int32_t K, vector<int32_t> I, vector<int32_t> O) {
  const uint32_t N = I.size();
  vector<Cross> crosses(N);
  for (uint32_t i = 0; i < N; i++) {
    crosses[i].inner = I[i];
    crosses[i].outer = O[i];
  }

  sort(crosses.begin(), crosses.end(), [](Cross a, Cross b) {
    return a.inner > b.inner;
  });

  const auto cmp = [](Cross a, Cross b) {
    return a.outer > b.outer;
  };
  priority_queue<Cross, vector<Cross>, decltype(cmp)> q(cmp);

  uint64_t best_area = 0;

  for(const auto &c : crosses) {
    q.push(c);
		if (q.size() < static_cast<uint32_t>(K)) {
			continue;
		} else if (q.size() > static_cast<uint32_t>(K)) {
      q.pop();
    }
    const auto inner_size = c.inner;
    const auto outer_size = q.top().outer;
    best_area = max(best_area, 2 * inner_size * outer_size - inner_size * inner_size);
  }

  return best_area;
}
