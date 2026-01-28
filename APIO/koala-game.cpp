#include <bits/stdc++.h>
#include "koala.h"
using namespace std;

int B[1000];
int R[1000];

int minValue(int N, int W) {
	fill(B, B + N, 0);
	B[0] = 1;
	playRound(B, R);
	if (R[0] < 2) return 0;
	else
		for (int i = 1; i < N; i++)
			if (!R[i]) return i;
}

int maxValue(int N, int W) {
	vector<int> v;
	for (int i = 0; i < N; i++) v.push_back(i);
	while (v.size() != 1) {
		int k = W / v.size();
		fill(B, B + N, 0);
		for (int i : v) B[i] = k;
		playRound(B, R);
		v.clear();
		for (int i = 0; i < N; i++)
			if (R[i] > k) v.push_back(i);
	}
	return v[0];
}

int greaterValue(int N, int W) {
	int l = 1, r = 9;
	while (l != r) {
		int mid = (l + r) / 2;
		B[0] = B[1] = mid;
		playRound(B, R);

		if (R[0] > mid && R[1] > mid) l = mid + 1;
		else if (R[0] <= mid && R[1] <= mid) r = mid - 1;
		else return (R[0] < R[1]);
	}
	B[0] = B[1] = l;
	playRound(B, R);
	return (R[0] < R[1]);
}

inline bool compare(int a, int b, int N, int W) {
	fill(B, B + N, 0);
	B[a] = B[b] = W;
	playRound(B, R);
	return (R[b] > W);
}
vector<int> mergesort(vector<int> v, int N, int W) {
	if (v.size() == 1) return v;

	vector<int> a, b;
	a.insert(a.begin(), v.begin(), v.begin() + (v.size() + 1) / 2);
	b.insert(b.begin(), v.begin() + (v.size() + 1) / 2, v.end());
	a = mergesort(a, N, W), b = mergesort(b, N, W);

	vector<int> sorted;
	int aptr = 0, bptr = 0;
	while (aptr < a.size() && bptr < b.size()) {
		if (compare(a[aptr], b[bptr], N, W)) sorted.push_back(a[aptr++]);
		else sorted.push_back(b[bptr++]);
	}
	sorted.insert(sorted.end(), a.begin() + aptr, a.end());
	sorted.insert(sorted.end(), b.begin() + bptr, b.end());

	return sorted;
}

void split(vector<int> v, int N, int W, int *P, int l = 1, int r = 100) {

	if (l == r) P[v[0]] = l;

	else {

		int x = min((int)sqrt(3*l/2), W / (r - l + 1));


		fill(B, B + N, 0);

		for (int i : v) B[i] = x;


		playRound(B, R);

		vector<int> less, greater;

		for (int i : v)

			if (R[i] > x) greater.push_back(i);

			else less.push_back(i);


		split(less, N, W, P, l, l + less.size() - 1);

		split(greater, N, W, P, r - greater.size() + 1, r);

	}

}

void allValues(int N, int W, int *P) {
  if (W == N) {

		vector<int> v;

		for (int i = 0; i < N; i++) v.push_back(i);

		split(v, N, W, P);

	}
	if (W == 2 * N) {
		vector<int> v;
		for (int i = 0; i < N; i++) v.push_back(i);
		vector<int> sorted = mergesort(v, N, W / 2);
		for (int i = 0; i < N; i++) P[sorted[i]] = i + 1;
	}
}
