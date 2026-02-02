#include "transfer.h"

std::vector<int> get_attachment(std::vector<int> source) {
	std::vector<int> v;
	int x = 0;
	for (int i = 0; i < source.size(); i++)
		if (source[i]) x ^= (i + 1);

	int last = 0;
	if (source.size() < 64) {
		for (int i = 0; i < 6; i++) {
			v.push_back(x & 1);
			if (x & 1) last = 1 - last;
			x >>= 1;
		}
	} else {
		for (int i = 0; i < 8; i++) {
			v.push_back(x & 1);
			if (x & 1) last = 1 - last;
			x >>= 1;
		}
	}
	v.push_back(last);
	return v;
}

std::vector<int> retrieve(std::vector<int> data) {
	int last = data.back();
	data.pop_back();
	int actual_last = 0, x = 0;
	if (data.size() < 71) {
		for (int i = 0; i < 6; i++) {
			x <<= 1;
			x += data.back();
			if (data.back()) actual_last = 1 - actual_last;
			data.pop_back();
		}
	} else {
		for (int i = 0; i < 8; i++) {
			x <<= 1;
			x += data.back();
			if (data.back()) actual_last = 1 - actual_last;
			data.pop_back();
		}
	}

	if (actual_last != last) return std::vector<int>(data.begin(), data.end());

	int actual_x = 0;
	for (int i = 0; i < data.size(); i++) {
		if (data[i]) actual_x ^= (i + 1);
	}

	int error = actual_x ^ x;
	if (error == 0) return data;

	data[error - 1] = 1 - data[error - 1];
	return data;
}
