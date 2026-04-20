#include <bits/stdc++.h>
using namespace std;
 
struct Node {
	char val;
	int weight, size;
	Node *left, *right;
	Node(char c) : val(c), weight(rand()), size(1), left(NULL), right(NULL) {}
} *root;
 
inline int size(Node *treap) {
	return treap ? treap->size : 0;
}
 
void split(Node *treap, Node *&left, Node *&right, int val) {
	if (!treap) {
		left = right = NULL;
		return;
	}
 
	if (size(treap->left) < val) {
		split(treap->right, treap->right, right, val - size(treap->left) - 1);
		left = treap;
	} else {
		split(treap->left, left, treap->left, val);
		right = treap;
	}
	treap->size = 1 + size(treap->left) + size(treap->right);
}
 
void merge(Node *&treap, Node *left, Node *right) {
	if (left == NULL) {
		treap = right;
		return;
	}
	if (right == NULL) {
		treap = left;
		return;
	}
 
	if (left->weight < right->weight) {
		merge(left->right, left->right, right);
		treap = left;
	} else {
		merge(right->left, left, right->left);
		treap = right;
	}
	treap->size = 1 + size(treap->left) + size(treap->right);
}
 
ostream& operator<<(ostream &os, Node *n) {
	if (!n) return os;
	os << n->left;
	os << n->val;
	os << n->right;
	return os;
}
 
int main() {
	int N, Q;
	string S;
 
	cin >> N >> Q >> S;
	for (char c : S) {
		merge(root, root, new Node(c));
	}
	while (Q--) {
		int l, r;
		cin >> l >> r;
		Node *a, *b, *c, *d;
		split(root, a, b, l - 1);
		split(b, c, d, r - l + 1);
		merge(root, a, d);
		merge(root, root, c);
	}
	cout << root << '\n';
}
