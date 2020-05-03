// _template.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

inline int exchg(int &a, int &b)  { int c = a; a = b; b = c; }
inline int log2(int N){ return log10(N) / log10(2); }
inline float min(float a, float b) { return a<b ? a : b; }


struct TreeNode
{
	TreeNode(int a) :val(a), left(nullptr), right(nullptr) {}
	TreeNode(int a, TreeNode* x, TreeNode* y) :val(a), left(x), right(y) {}
	TreeNode() :val(0), left(nullptr), right(nullptr) {}

	int val;
	TreeNode *left;
	TreeNode *right;

};

void print(TreeNode* root){
	queue<TreeNode*> q;
	q.push(root);

	while (q.size()){
		int n = q.size();
		for (int i = 0; i<n; ++i){
			TreeNode* front = q.front();
			q.pop();

			if (!front)
				cout << "# ";
			else{
				cout << front->val << " ";
				q.push(front->left);
				q.push(front->right);
			}
		}
		cout << endl;
	}
}
/////////////////////////////////////////
// Given an integer array nums, find the sum of the elements between indices i and j(i ≤ j), inclusive.
// The update(i, val) function modifies nums by updating the element at index i to val.
// Example:
// Given nums = [1, 3, 5]

// sumRange(0, 2) -> 9
// update(1, 2)
// sumRange(0, 2) -> 8

// passed , binary indexted  tree; 
// reference: 
// http://www.hawstein.com/posts/binary-indexed-trees.html#basic
//

class NumArray {
	vector<int> num, bit; 
public:
	NumArray(vector<int> &nums) {
		num.resize(nums.size() + 1); 
		bit.resize(nums.size() + 1); 
		for (int i = 0; i < nums.size(); ++i)
			update(i, nums[i]); 
	}

	void update(int i, int val) {
		int diff = val - num[i + 1]; 
		for (int j = i+1; j < num.size(); j += j&(j ^ (j-1))){ // 也可以写成  j += j^(-j)
			bit[j] += diff; 
		}
		num[i + 1] = val; 
	}

	int sumRange(int i, int j) {
		return sumLeft(j) - sumLeft(i - 1); 
	}

	int sumLeft(int i){
		int res = 0; 
		for (int j = i + 1 ; j > 0; j -= j&(j ^ (j-1))) //  这里终止条件必须是  j>0 , 不能是 j>=0 !!! 因为 0 取 最右边的 1 还是 0， 死循环！
			res += bit[j]; 
		return res; 
	}
};



// pass /////////////////////////
class NumArray2 {
public:
	vector<int> f; 
	vector<int> bit; 

	NumArray2(vector<int> nums) {
		int n = nums.size();
		f = vector<int>(n + 1, 0); 

		bit = vector<int>(n + 1, 0); 
		for (int i = 1; i < f.size(); ++i){
			update(i - 1, nums[i - 1]); 
		}
	}

	void update(int i, int val) {
		int diff = val - f[i + 1]; 
		f[i + 1] = val; 

		for (int j = i + 1; j < bit.size(); j += (j&(-j))){
			bit[j] += diff; 
		}
	}

	int cumsum(int start){
		int res = 0;
		for (int i = start+1; i > 0; i -= (i&(-i))){
			res += bit[i]; 
		}
		return res;
	}

	int sumRange(int i, int j) {
		return cumsum(j) - cumsum(i - 1);
	}
};

/**
* Your NumArray object will be instantiated and called as such:
* NumArray obj = new NumArray(nums);
* obj.update(i,val);
* int param_2 = obj.sumRange(i,j);
*/

class node{
public:
	int start; 
	int end; 
	int sum; 
	node *left, *right;
	node(int a, int b) :start(a), end(b), left(nullptr), right(nullptr){}
	node(int a, int b, int c) :start(a), end(b), sum(c), left(nullptr), right(nullptr){}
};

class NumArray3 {
public:
	node* root; 
	NumArray3(vector<int> nums) {
		root = build(nums, 0, nums.size()-1); 
	}

	node* build(vector<int>& nums, int start, int end){
		if (start > end)
			return nullptr; 
		if (start == end)
			return new node(start, end, nums[start]); 

		int mid = start + (end - start) / 2; 
		node *root = new node(start, end); 
		root->left = build(nums, start, mid); 
		root->right = build(nums, mid+1, end); 
		root->sum = root->left->sum + root->right->sum; 

		return root; 
	}

	void update(int i, int val){
		update(root, i, val); 
	}
	void update(node* n, int i, int val){
		if (i<n->start || i>n->end)
			return; 
		if (i == n->start && i == n->end){
			n->sum = val; 
			return; 
		}

		update(n->left, i, val); 
		update(n->right, i, val); 
		n->sum = n->left->sum + n->right->sum; 
	}

	int sumRange(int i, int j){
		return range(root, i, j); 
	}
	int range(node* n, int i, int j){
		if (i > n->end || j < n->start)
			return 0; 
		if (n->start == i && n->end == j)
			return n->sum; 

		int mid = n->start + (n->end - n->start) / 2; 
		if (j <= mid)
			return range(n->left, i, j);
		else if (i > mid)
			return range(n->right, i, j);
		else
			return range(n->left, i, mid) + range(n->right, mid + 1, j); 
	}
};

class NumArray4 {
public:
	int n; 
	vector<int> copy; 
	vector<int> f; 

	NumArray4(vector<int> nums):n(nums.size()), f(n+1), copy(1) {
		copy.insert(copy.begin() + 1, nums.begin(), nums.end()); 
		for (int i = 0; i < n; ++i){
			add(i, copy[i+1]); 
		}
	}


	void add(int i, int val) {
		for (int j = i+1; j <= n; j += (j&(-j))){
			f[j] += val; 
		}
	}


	void update(int i, int val) {
		int diff = val - copy[i + 1]; 
		add(i, diff); 
		copy[i + 1] += diff; 
	}


	int sum(int i){
		int res = 0; 
		for (; i >0; i -= (i&(-i))){
			res += f[i]; 
		}
		return res; 
	}


	int sumRange(int i, int j) {
		return sum(j + 1) - sum(i); 
	}
}; 


class NumArray5 {
public:
	struct node{
		int sum, l, r; 
		node *left, *right;
		node(int a, int b, int c) :sum(a), l(b), r(c) {}
	};

	node * root;
	NumArray5(vector<int>& data) {
		root = build(data, 0, data.size()); 
	}

	node* build(vector<int>& data, int left, int right){
		if (left >= right)
			return nullptr; 
		if (left + 1 == right)
			return new node(data[left], left, right); 

		int mid = left + (right - left) / 2; 
		node *l = build(data, left, mid),
			*r = build(data, mid, right); 
		node *cur = new node(0, left, right); 
		cur->left = l, cur->right = r; 
		cur->sum = cur->left->sum + cur->right->sum; 

		return cur; 
	}

	void update(int i, int val){
		update(root, i, val);
	}
	void update(node* n, int i, int val){
		if (!n) return; 
		int l = n->l, r = n->r, mid = l + (r - l) / 2; 
		if (i < l || i >= r)
			return; 
		if (l == i && r == l + 1){
			n->sum = val; 
			return; 
		}

		if (i >= mid)
			update(n->right, i, val);
		else if (i < mid)
			update(n->left, i, val); 

		n->sum = n->left->sum + n->right->sum; 
	}

	int rangeSum(int i, int j){
		return rangeSum(root, i, j+1);
	}
	int rangeSum(node* n, int i, int j){
		if (!n)
			return 0; 
		int l = n->l, r = n->r, mid = l + (r - l) / 2; 
		if (l == i && r == j)
			return n->sum; 
		if (i >= r || j <= l)
			return 0; 

		if (j < mid)
			return rangeSum(n->left, i, j);
		else if (i >= mid)
			return rangeSum(n->right, i, j);
		else
			return rangeSum(n->left, i, mid) + rangeSum(n->right, mid, j); 
	}
}; 





int main() { 
	vector<int> b = { 1, 3, 5, 9, 5, 73, 1, 4, 8, 32, 45, 27, 92 };
	NumArray a(b); 
	a.update(3, 12);
	a.update(3, 87);
	cout << a.sumRange(2, 8); 

	NumArray2 c(b); 
	c.update(3, 12);
	c.update(3, 87);
	cout << c.sumRange(2, 8);

	NumArray3 d(b);
	d.update(3, 12);
	d.update(3, 87);
	cout << d.sumRange(2, 8);

	NumArray4 e(b); 
	cout << endl; 
	e.update(3, 12);
	e.update(3, 87);
	for (auto i : e.f)
		cout << i << " "; 
	cout << endl; 
	cout << e.sumRange(2, 8);
}

