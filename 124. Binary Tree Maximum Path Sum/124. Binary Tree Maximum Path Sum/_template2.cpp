// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <iostream>
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
	int maxPathSum(TreeNode* root) {
		int res = root->val; 
		helper(root, res); 
		return res;
	}

	int helper(TreeNode* node, int& maxSum){
		if (!node)
			return 0; 

		int left = helper(node->left, maxSum); 
		int right = helper(node->right, maxSum); 

		int cur = node->val + (left > 0 ? left : 0) + (right > 0 ? right : 0); 
		if (maxSum < cur)
			maxSum = cur; 

		return node->val + (max(left, right)>0 ? max(left, right) : 0); 
	}
};


class Solution2 {
public:
	int maxPathSum(TreeNode* root) {
		int r = INT_MIN; 
		dfs(root, r); 
		return r; 
	}
	int dfs(TreeNode* n, int& r){
		if (!n){
			r = max(r, 0); 
			return 0; 
		}

		int lv = dfs(n->left, r), rv = dfs(n->right, r); 

		r = max(r, lv + rv + n->val); 

		int longestBranch = max(lv, rv); 

		return longestBranch > 0 ? longestBranch + n->val : n->val; 
	}
};


class Solution3 {
public:
	int maxPathSum(TreeNode* root) {
		int res = INT_MIN;
		dfs(root, res);
		return res;
	}
	int dfs(TreeNode* n, int& res){
		if (!n) return 0;
		int l = dfs(n->left, res),
			r = dfs(n->right, res);
		res = max(max(res, n->val), max(l + r + n->val, max(l + n->val, r + n->val)));

		return max(l + n->val, max(r + n->val, n->val));
	}
};



int main(){
	Solution a; 
	Solution3 a2; 

	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(-7),
		new TreeNode(-9)));
	/*      6
		3       8
	1    4   7    9
	*/

	cout << a.maxPathSum(tree) << endl; 
	cout << a2.maxPathSum(tree) << endl; 



	///////////////////////////
	auto start = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout << endl << microseconds << " microseconds elapsed..." << endl;
}

