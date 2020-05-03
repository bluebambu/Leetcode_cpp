// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <iostream>
#include <cassert>
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
		for (int i = 0; i < n; ++i){
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


template <typename C>
void prt1Layer(C v){
	for (auto i : v)
		cout << i << " ";
	cout << endl;
}

template <typename C>
void prt2Layer(C v){
	for (auto i : v){
		for (auto j : i)
			cout << j << " ";
		cout << endl; 
	}
	cout << endl;
}

template <typename C>
void mapprt(C v){
	for (auto i : v)
		cout << i.first << " " << i.second << endl;
	cout << endl;
}
////////////////////////////////////////////////////////////////




class Solution {
public:
	double median(vector<int>& a, vector<int>& b){
		int n = a.size(), m = b.size(); 
		int total = m + n; 

		if (total % 2)
			return findKth(a, -1, b, -1, total / 2 + 1);
		else
			return (findKth(a, -1, b, -1, total / 2) + findKth(a, -1, b, -1, total / 2 + 1)) / 2.0; 
	}

	int findKth(vector<int>& a, int ai, vector<int>& b, int bi, int k){
		if (a.size() - ai > b.size() - bi)
			return findKth(b, bi, a, ai, k); 
		if (ai == a.size() - 1)
			return b[bi + 1]; 
		if (k == 1)
			return min(a[ai + 1], b[bi + 1]); 

		int dist_a = min(k / 2, a.size()-1-ai),
			dist_b = k - dist_a; 

		if (a[ai + dist_a] > b[bi + dist_b])
			return findKth(a, ai, b, bi + dist_b, k - dist_b);
		else
			return findKth(a, ai + dist_a, b, bi, k - dist_a); 
	}
};


class Solution2{
public:
	double median(int a[], int m, int b[], int n){
		int total = m + n; 
		if (total % 2)
			return helper(a, m, b, n, total / 2 + 1);
		else
			return (helper(a, m, b, n, total / 2) + helper(a, m, b, n, total / 2 + 1)) / 2.0; 
	}

	int helper(int a[], int arem, int b[], int brem, int k){
		if (arem > brem)
			return helper(b, brem, a, arem, k); 
		if (arem == 0)
			return b[k - 1]; 
		if (k == 1)
			return min(*a, *b); 

		int dist_a = min(k / 2, arem); 
		int dist_b = k - dist_a; 

		if (a[dist_a - 1] < b[dist_b - 1])
			return helper(a + dist_a, arem - dist_a, b, brem, k - dist_a);
		else
			return helper(a, arem, b + dist_b, brem - dist_b, k - dist_b); 
	}
};

void TEST_median(){
	Solution2 a; 
	int b[] = { 2 , 3, 4, 5};
	int	c[] = {1, 5, 6}; 
	cout << a.median(b, 4,  c, 3) << endl; 
	assert(a.median(b, 4,  c, 3) == 4); 
}




int main(){
	TEST_median(); 


	Solution a; 

	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 


	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
		3       8
	1    4   7    9
	*/



	///////////////////////////
	auto start = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout << endl << microseconds << " microseconds elapsed..." << endl;
}

