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
// You are given a binary tree in which each node contains an integer value.

// Find the number of paths that sum to a given value.

// The path does not need to start or end at the root or a leaf, but it must go downwards (traveling only from parent nodes to child nodes).

// The tree has no more than 1,000 nodes and the values are in the range -1,000,000 to 1,000,000.

// Example:

// root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8

//       10
//      /  \
//     5   -3
//    / \    \
//   3   2   11
//  / \   \
// 3  -2   1

// Return 3. The paths that sum to 8 are:

// 1.  5 -> 3
// 2.  5 -> 2 -> 1
// 3. -3 -> 11


class Solution {
public:
	int pathSum(TreeNode* root, int sum) {
		vector<int> lvlSum; 
		int res = 0; 
		helper(root, sum, lvlSum, res); 
		return res; 
	}

	void helper(TreeNode* node, int sum, vector<int> lvlsum, int& res){
		if (!node)
			return; 

		lvlsum.push_back(0); 
		for (int i = 0; i < lvlsum.size(); ++i){
			lvlsum[i] += node->val; 
			if (lvlsum[i] == sum)
				++res; 
		}

		helper(node->left, sum, lvlsum, res); 
		helper(node->right, sum, lvlsum, res); 
	}
};



// pass AC, better solution, but complicated. 
class Solution2 {
public:
	int pathSum(TreeNode* root, int sum) {
		unordered_map<int, int> preSum; 
		preSum[0] = 1; // very important!!!
		return path(root, 0, sum, preSum); 
	}

	int path(TreeNode* node, int sum, int target, unordered_map<int, int>& preSum){
		if (!node)
			return 0; 

		sum += node->val; 
		int res = 0; 
		if (preSum.count(sum - target))
			res += preSum[sum - target]; 
		preSum[sum] += 1; 
		res += path(node->left, sum, target, preSum) +
			path(node->right, sum, target, preSum);
		preSum[sum] -= 1; 
		return res;
	}
};; 

// subarray sum on tree
class Solution3 {
public:
	int pathSum(TreeNode* root, int sum) {
		unordered_map<int, int> m; 
		m[0] = 1; 
		int res = 0; 
		dfs(root, sum, m, 0, res);
		return res; 
	}

	void dfs(TreeNode* node, int target, unordered_map<int, int>& m, int curs, int& res){
		if (!node)
			return; 

		curs += node->val; 
		if (m[curs - target] > 0){
			res += m[curs - target]; 
		}
		m[curs] += 1; 
		dfs(node->left, target, m, curs, res); 
		dfs(node->right, target, m, curs, res);
		m[curs] -= 1; 
	}
}; 

class Solution5 {
public:
	int pathSum(TreeNode* root, int sum) {
		int res = 0; 
		unordered_map<int, int> presum; 
		presum[0] = 1; 
		dfs(root, 0, presum, res, sum); 
		return res; 
	}
	void dfs(TreeNode* cur, int sum, unordered_map<int, int>& presum, int& res, int target){
		if (!cur) return; 

		sum += cur->val; 
		res += presum[sum - target]; 
		presum[sum] += 1; 
		dfs(cur->left, sum, presum, res, target); 
		dfs(cur->right, sum, presum, res, target); 
		presum[sum] -= 1; 
	}
}; 

int main(){
	Solution2 a; 
	Solution5 a2;

	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
		3       8
	1    4   7    9
	*/

	cout << a.pathSum(tree, 4) << endl;
	cout << a2.pathSum(tree, 4) << endl;


	///////////////////////////
	auto start = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout << endl << microseconds << " microseconds elapsed..." << endl;
}

