// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <iostream>
#include <cassert>
#include <functional>
#include <bitset>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>
#include <unordered_set>
#include <set>
#include <map>
#include <utility>
#include <sstream>
#include <string>
#include <chrono>

using namespace std;

inline int exchg(int &a, int &b)  { int c = a; a = b; b = c; }
inline int log2(int N){ return log10(N) / log10(2); }
inline float min(float a, float b) { return a < b ? a : b; }


struct TreeNode {
	TreeNode(int a, int b, int max) :start(a), end(b), max(max), left(nullptr), right(nullptr) {}
	TreeNode(int a, int b) :start(a), end(b), left(nullptr), right(nullptr) {}

	int start;
	int end;
	int max;
	TreeNode *left;
	TreeNode *right;
};


class SegmentTree {
public:
	TreeNode * root; 
	SegmentTree(vector<int>& A){
		root = build(A); 
	}

	TreeNode* build(vector<int>& A){
		return helper(A, 0, A.size() - 1); 
	}
	TreeNode* helper(vector<int>& A, int start, int end){
		if (start > end)
			return nullptr; 
		if (start == end)
			return new TreeNode(start, end, A[start]); 

		TreeNode* root = new TreeNode(start, end); 
		int mid = start + (end - start) / 2; 
		root->left = helper(A, start, mid);
		root->right = helper(A, mid + 1, end); 
		root->max = max(root->left->max, root->right->max); 
		return root; 
	}

	void modify(int idx, int newval){
		mod(root, idx, newval); 
	}
	void mod(TreeNode* node, int idx, int newval){
		if (idx<node->start || idx > node->end)
			return; 
		if (node->start == idx && node->end == idx){
			node->max = newval; 
			return; 
		}
		
		int mid = node->start + (node->end - node->start) / 2; 
		if (idx <= mid)
			mod(node->left, idx, newval);
		else
			mod(node->right, idx, newval); 
		node->max = max(node->left->max, node->right->max); 
	}

	int queryMax(int ll, int rr){
		return query(root, ll, rr); 
	}
	int query(TreeNode* node, int ll, int rr){
		if (ll == node->start && rr == node->end)
			return node->max; 
		int mid = node->start + (node->end - node->start) / 2; 
		if ((rr <= mid))
			return query(node->left, ll, rr);
		else if (ll > mid)
			return query(node->right, ll, rr);
		else
			return max(query(node->left, ll, mid), query(node->right, mid + 1, rr)); 
	}
};



int main(){

	vector<int> b = { 4, 1, -9, 0, 8 }; 

	SegmentTree a(b); 

	cout << a.queryMax(0, b.size()-1); 
	a.modify(2, 9); 
	cout << a.queryMax(0, b.size()-1); 

	for (int i = 10; i < 100; ++i){
		int r = rand() % (b.size()); 
		a.modify(r, i); 
		assert(a.queryMax(0, b.size() - 1) == i); 
	}

	///////////////////////////
	auto start = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout << endl << microseconds << " microseconds elapsed..." << endl;
}

