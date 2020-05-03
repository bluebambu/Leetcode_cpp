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


// Given a binary tree, find the length of the longest consecutive sequence path.
// 
// The path refers to any sequence of nodes from some starting node to any node in the tree along the parent - child connections.The longest consecutive path need to be from parent to child(cannot be the reverse).
// 
// For example,
// 
// 1
// \
//  3
// / \
// 2   4
// \
// 5
// 
// Longest consecutive sequence path is 3 - 4 - 5, so return 3.
// 
// 2
//  \
//   3
//  /
// 2
// /
// 1
// 
// Longest consecutive sequence path is 2 - 3, not3 - 2 - 1, so return 2.



/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
*/

// passed
class Solution {
public:
	int longestConsecutive(TreeNode* root) {
		if (!root)
			return 0; 
		int res = 1;
		dfs(root, res);
		return res;
	}

	int dfs(TreeNode* node, int& res){
		if (!node)
			return 0;

		int l = dfs(node->left, res),  // 注意这个不能写到下面 left 的判断中去，因为 condition为false的时候， 第一条就不运行了。 
			r = dfs(node->right, res); 

		int left = (node->left && node->val + 1 == node->left->val) ? l : 0,
		right = (node->right && node->val + 1 == node->right->val) ? r : 0;

		if (!left){
			res = max(res, right + 1);
			return right + 1;
		}
		else{
			res = max(res, max(left, right) + 1);
			return max(left, right) + 1;
		}
	}
};


// wrong ans, this is for consecutive sequence, but both decreasing and increasing sequences. 
class Solution2 {
public:
	int longestConsecutive(TreeNode* root) {
		int res = 1; 
		dfs(root, 1, res, 1); 
		dfs(root, 1, res, -1); 
		return res; 
	}

	void dfs(TreeNode *cur, int len, int& res, int sign){
		if (!cur) return; 
		
		if (cur->left && cur->left->val == cur->val + sign){
			res = max(res, len + 1); 
			dfs(cur->left, len + 1, res, sign); 
		}
		else{
			dfs(cur->left, 1, res, 1); 
			dfs(cur->left, 1, res, -1); 
		}

		if (cur->right && cur->right->val == cur->val + sign){
			res = max(res, len + 1); 
			dfs(cur->right, len + 1, res, sign); 
		}
		else{
			dfs(cur->right, 1, res, 1); 
			dfs(cur->right, 1, res, -1); 
		}
	}
};


class Solution3 {
public:
	int longestConsecutive(TreeNode* root) {
		if (!root) return 0; 

		int res = 1; 
		dfs(root, 1, res); 
		return res; 
	}

	void dfs(TreeNode* n, int len, int& res){
		if (!n) return;

		if (n->left && n->left->val == n->val + 1){
			res = max(res, len + 1); 
			dfs(n->left, len + 1, res); 
		}
		else
			dfs(n->left, 1, res); 

		if (n->right && n->right->val == n->val + 1){
			res = max(res, len + 1); 
			dfs(n->right, len + 1, res); 
		}
		else
			dfs(n->right, 1, res); 
	}
};

int main()
{
	Solution a;

	//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
		3       8
	1    4   7    9

	*/

	TreeNode *t2 = new TreeNode(2, nullptr, new TreeNode(3, ))


}

