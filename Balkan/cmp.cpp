#include "cmp.h"

int delta[6]{1, 4097, 5121, 5377, 5441, 5457};

void remember(int n) {
	for (int i = 0; i < 6; i++) bit_set((n >> i * 2) + delta[i]);
}

int compare(int b) {
	int l = 0, r = 6;
	while (l != r) {
		int mid = (l + r) / 2;
		if (bit_get((b >> mid * 2) + delta[mid])) r = mid;
		else l = mid + 1;
	}

	if (!l) return 0;
	int last_digit = (b >> l * 2 - 2) & 3;
	if (last_digit > 1) {
		if (bit_get((((b >> l * 2) << 2) + 3) + delta[l - 1])) return -1;
		return 1;
	} else {
		if (bit_get(((b >> l * 2) << 2) + delta[l - 1])) return 1;
		return -1;
	}
}
